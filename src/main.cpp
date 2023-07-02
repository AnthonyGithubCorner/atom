// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

#include "common/shader.hpp"
#include "common/resourceManager.hpp"
#include "baseClasses/gameClass.hpp"
#include "common/spriteRenderer.hpp"
#include "UI/dialogue/dialogue.hpp"
#include "UI/dialogue/word_renderer/word_renderer.hpp"
#include "UI/buttons/buttonClass.hpp"
#include "load_asset/loadAsset.hpp"


// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// The Width of the screen
const int SCREEN_WIDTH = 1080;
// The height of the screen
const int SCREEN_HEIGHT = 720;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    // Initialise GLEW
    glewExperimental = true; // Needed for core profile
                             // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music * _gMusic = Mix_LoadMUS(load_asset("/song.mp3").c_str());
//    Mix_PlayMusic(_gMusic, -1);
    SDL_Window *window = SDL_CreateWindow(
        "An SDL2 window",       // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        SCREEN_WIDTH,           // width, in pixels
        SCREEN_HEIGHT,          // height, in pixels
        0                       // flags - see below
    );

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open SDL window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create context
    SDL_GLContext gContext = SDL_GL_CreateContext(window);
    bool success = true;
    if (gContext == NULL)
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
            printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        }

        // Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Color black;
    black.a = 0;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    WordRenderer *basic_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 16, black);
    if(basic_word_renderer == nullptr){
        SDL_Log("Asset didn't load");
        return -1;
    }
    SDL_Color purple;
    purple.a = 0;
    purple.r = 100;
    purple.g = 0;
    purple.b = 100;
    WordRenderer *button_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 16, purple);
    if(button_word_renderer == nullptr){
        SDL_Log("Asset didn't load");
        return -1;
    }
    SDL_Color red;
    red.a = 0;
    red.r = 200;
    red.g = 0;
    red.b = 0;
    WordRenderer *excited_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 36, red);
    if(excited_word_renderer == nullptr){
        SDL_Log("Asset didn't load");
        return -1;
    }


    //move word renderers init to here
    Dialogue *dialogue_test = new Dialogue(load_asset("/dialogue/idea.txt").c_str());
    if(dialogue_test == nullptr){
        SDL_Log("Asset didn't load");
        return -1;
    }
        // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    // initialize game
    // ---------------
    Breakout.Init();

    glClearColor(0.0f, 0.2f, 0.2f, 0.2f);


    SDL_Event e;
    bool quit = false;
    int xpos, ypos;
    int x, y;
    Uint32 buttons;
    gameObject * temp;
    int startPosX, startPosY = 0;
    int deltaPosX, deltaPosY = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            // manage user input
            // -----------------
            // Breakout.ProcessInput(deltaTime);

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if(e.type==SDL_MOUSEMOTION){

                SDL_GetMouseState(&xpos, &ypos);


					temp = ResourceManager::getGameObject("frog");
					float rot = -((xpos / (float) SCREEN_WIDTH) * 180.0f);
					temp->setRotation(rot);

					temp = ResourceManager::getGameObject("bg");
					float xTrans = ((xpos / (float) SCREEN_WIDTH * 0.5f)
							- temp->renderRect.w / 2);
					temp->setX(xTrans);


            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_a:
                    temp = ResourceManager::getGameObject("frog");
                    temp->setRotation(temp->rotation + 20.0f);
                    break;
                case SDLK_d:
                    temp = ResourceManager::getGameObject("frog");
                    temp->setRotation(temp->rotation - 20.0f);
                    break;
                default:
                    break;
                }
                
            }
            buttons = SDL_GetMouseState(&x, &y);
            // SDL_Log("Mouse cursor is at %d, %d", x, y);
            if ((buttons & SDL_BUTTON_LMASK) != 0)
            {
                SDL_Log("Mouse Button 1 (left) is pressed.");
                for (int i = 0; i < infoWindowEvents.size(); i++)
                {
                    infoWindowEvents[i].CheckIfClicked((float)x/SCREEN_WIDTH, (float)y/SCREEN_HEIGHT);
                }
            }

        }

        
        // update game state
        // -----------------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        ResourceManager::getGameObject("bg")->Render();
        // ResourceManager::getGameObject("face")->Render();

//        ResourceManager::getGameObject("frog")->Render();
//        SDL_FRect textRect = {0.1f, 0.4f, 0.8f, 0.7f};
//        dialogue_test->render_dialogue(textRect, Breakout.Renderer,window,basic_word_renderer, button_word_renderer, excited_word_renderer);
//        ResourceManager::getGameObject3D("testModel")->setColor(glm::vec3(0.5f,0.3f,0.2f));
        ResourceManager::getGameObject3D("testModel")->Render();
        // Update screen
        
        
  

        SDL_GL_SwapWindow(window);

        

        SDL_Delay(16);
    }

    // glDeleteTextures(1, &tex);

    // glDeleteProgram(shader.ID);
    ResourceManager::Clear();
    delete button_word_renderer;
    delete basic_word_renderer;
    delete excited_word_renderer;
    delete dialogue_test;
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

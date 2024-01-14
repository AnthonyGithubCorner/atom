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
#include "UI/dialogue/dialogue.hpp"
#include "UI/dialogue/word_renderer.hpp"
#include "UI/buttons/buttonClass.hpp"
#include "load_asset/loadAsset.hpp"
#include "common/Camera.hpp"
#include "interactionFile/stateManager.hpp"
#include "interactionFile/actionLoader.hpp"

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

//includ imgui
//TODO Make this optional
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"


Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);


int main(int argc, char *argv[])
{
    // Initialise GLEW
    glewExperimental = true; // Needed for core profile
                             // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0)
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

//    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Color black;
    black.a = 0;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    // TODO make this optional
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gContext);
    ImGui_ImplOpenGL3_Init();
//
//    WordRenderer *basic_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 16, black);
//    if(basic_word_renderer == nullptr){
//        SDL_Log("Asset didn't load");
//        return -1;
//    }
//    SDL_Color purple;
//    purple.a = 0;
//    purple.r = 100;
//    purple.g = 0;
//    purple.b = 100;
//    WordRenderer *button_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 16, purple);
//    if(button_word_renderer == nullptr){
//        SDL_Log("Asset didn't load");
//        return -1;
//    }
//    SDL_Color red;
//    red.a = 0;
//    red.r = 200;
//    red.g = 0;
//    red.b = 0;
//    WordRenderer *excited_word_renderer = new WordRenderer(load_asset("/andaleAtlas.png").c_str(), 36, red);
//    if(excited_word_renderer == nullptr){
//        SDL_Log("Asset didn't load");
//        return -1;
//    }


    //move word renderers init to here
//    Dialogue *dialogue_test = new Dialogue(load_asset("/dialogue/idea.txt").c_str());
//    if(dialogue_test == nullptr){
//        SDL_Log("Asset didn't load");
//        return -1;
//    }
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
    Camera::setCamera(0.0f, 0.0f);
    while (!quit)
    {
    	// TODO Make optional
    	ImGui_ImplOpenGL3_NewFrame();
    	ImGui_ImplSDL2_NewFrame();
    	ImGui::NewFrame();
    	ImGui::ShowDemoWindow();
        while (SDL_PollEvent(&e))
        {
        	ImGui_ImplSDL2_ProcessEvent(&e); // Forward your event to backend
            // manage user input
            // -----------------
            // Breakout.ProcessInput(deltaTime);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if(e.type==SDL_MOUSEMOTION){

                SDL_GetMouseState(&xpos, &ypos);

//
//					temp = ResourceManager::getGameObject("frogGuy");
//					float rot = -((xpos / (float) SCREEN_WIDTH) * 180.0f);
//					temp->setRotation(rot);

//					temp = ResourceManager::getGameObject("bg");
//					float xTrans = ((xpos / (float) SCREEN_WIDTH * 0.5f)
//							- temp->renderRect.w / 2);
//					temp->setX(xTrans);


            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_a:
                	stateManager::setState("KEYA");
//                    temp = ResourceManager::getGameObject("frogGuy");
//                    temp->setRotation(temp->rotation + 20.0f);
                    break;
                case SDLK_d:
                	stateManager::setState("KEYD");
//                    temp = ResourceManager::getGameObject("frogGuy");
//                    temp->setRotation(temp->rotation - 20.0f);
                    break;
                case SDLK_e:
                	stateManager::setState("KEYE");
                	break;
                case SDLK_r:
                	stateManager::setState("KEYR");
                	break;
                case SDLK_f:
                	stateManager::setState("KEYF");
                	break;
                case SDLK_s:
                	stateManager::setState("KEYS");
                	break;
                case SDLK_w:
                	stateManager::setState("KEYW");
                	break;
                default:
                    break;
                }
                
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_a:
                	stateManager::clearState("KEYA");
                    break;
                case SDLK_d:
                	stateManager::clearState("KEYD");
                    break;
                case SDLK_e:
                	stateManager::clearState("KEYE");
                	break;
                case SDLK_r:
                	stateManager::clearState("KEYR");
                	break;
                case SDLK_f:
                	stateManager::clearState("KEYF");
                    break;
                case SDLK_w:
                	stateManager::clearState("KEYW");
                    break;
                case SDLK_s:
                	stateManager::clearState("KEYS");
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


        for(auto interaction : Breakout.activeInteractions){
        	if(interaction.first->enableActions)
        	{
        		interaction.second->executeFile(interaction.first);
        	}
        }

        for(auto go : Breakout.activeGameObjects){
        	if(go->enableRender)
        	{
        		go->Render();
        	}
        }
//        ResourceManager::getGameObject("bg")->Render();
//        // ResourceManager::getGameObject("face")->Render();
//        ResourceManager::getGameObject("frog")->Render();
//        SDL_FRect textRect = {0.1f, 0.4f, 0.8f, 0.7f};

//        ResourceManager::getGameObject3D("testModel")->setColor(glm::vec3(0.5f,0.3f,0.2f));


//        ResourceManager::getGameObject3D("testModel")->Render();
        // Some Functions that are truely global are best left outside a iFile
        if(stateManager::getState("EXT_FULLSCREEN"))
        {
        	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_GetWindowSize(window,&SCREEN_WIDTH, &SCREEN_HEIGHT);
            glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        else
        {
        	SDL_SetWindowFullscreen(window, 0);
            SDL_GetWindowSize(window,&SCREEN_WIDTH, &SCREEN_HEIGHT);
            glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        // TODO Make optional
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//    	stateManager::clearState("KEYFPRESSED");
//        SDL_Delay(1);

        // Update screen
        
        
  

        SDL_GL_SwapWindow(window);

        
    }

    // glDeleteTextures(1, &tex);

    // glDeleteProgram(shader.ID);
    ResourceManager::Clear();
//    delete button_word_renderer;
//    delete basic_word_renderer;
//    delete excited_word_renderer;
//    delete dialogue_test;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

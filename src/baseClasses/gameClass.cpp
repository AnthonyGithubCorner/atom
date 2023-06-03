#include "gameClass.hpp"
#include "../common/spriteRenderer.hpp"
#include "../common/resourceManager.hpp"
#include "../load_asset/loadAsset.hpp"



Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{
    for(auto o: activeGameObjects){
        delete o;
        o = nullptr;
    }
    activeGameObjects.clear();
    delete Renderer;
}
  
void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader(load_asset("/shaders/vertexshader.vertex").c_str(), load_asset("/shaders/fragmentShader.fragment").c_str(), nullptr, "sprite");
    // configure shaders

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    glm::mat4 projectionMatrix = glm::ortho(0.0f, 1.0f, 
    1.0f, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projectionMatrix);
    // set render-specific controls
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);
    
    // load textures
    ResourceManager::LoadGameObject(Renderer, load_asset("/gameWallpaper1.png").c_str(),false,"bg", {0,0,2.0f,1.2f});
    ResourceManager::LoadGameObject(Renderer,load_asset("/awesomeface.png").c_str(),true,"face", {0.1f,0.1f,0.1f,0.1f});
    ResourceManager::LoadGameObject(Renderer,load_asset("/textBox.png").c_str(),true,"textBox");
    ResourceManager::LoadGameObject(Renderer,load_asset("/frogGuy.png").c_str(),true,"frog", {0.3f,0.1f,0.4f, 0.4f});




}

void Game::Update(float dt)
{
    
}

void Game::ProcessInput(float dt)
{
   
}

void Game::Render()
{
    for(auto o: ResourceManager::gameObjects){
        o.second->Render();
    }
} 

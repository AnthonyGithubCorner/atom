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
    glEnable(GL_DEPTH_TEST);
    // load shaders
    ResourceManager::LoadShader(load_asset("/shaders/sprite/vertexshader.vertex").c_str(), load_asset("/shaders/sprite/fragmentShader.fragment").c_str(), nullptr, "sprite");
    // configure shaders

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    glm::mat4 projectionMatrix = glm::ortho(0.0f, 1.0f, 
    1.0f, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projectionMatrix);
    // set render-specific controls
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);
    
    ResourceManager::LoadShader(load_asset("/shaders/model/vertexshader.vertex").c_str(), load_asset("/shaders/model/fragmentShader.fragment").c_str(), nullptr, "model");
    ResourceManager::GetShader("model").Use().SetInteger("image", 0);
    glm::mat4 proj = glm::ortho(0.0f, 20.0f,
    20.0f, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("model").SetMatrix4("projection", proj);
    myShader = ResourceManager::GetShader("model");
    Renderer3D = new ModelRenderer(myShader);
    glm::vec3 cameraPos = glm::vec3( 0, 0, 5 );
    float horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;
    // Initial Field of View
    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );
    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 up = glm::cross( right, direction );
    glm::mat4 view = glm::lookAt(
    cameraPos,
    cameraPos+direction,
    up);
    ResourceManager::GetShader("model").SetMatrix4("view", view);
    // load textures
    ResourceManager::LoadGameObject(Renderer, load_asset("/gameWallpaper1.png").c_str(),false,"bg", {0,0,2.0f,1.2f});
    ResourceManager::LoadGameObject(Renderer,load_asset("/awesomeface.png").c_str(),true,"face", {0.1f,0.1f,0.1f,0.1f});
    ResourceManager::LoadGameObject(Renderer,load_asset("/textBox.png").c_str(),true,"textBox");
    ResourceManager::LoadGameObject(Renderer,load_asset("/frogGuy.png").c_str(),true,"frog", {0.3f,0.1f,0.4f, 0.4f});

    // load models
    ResourceManager::LoadGameObject3D(Renderer3D, load_asset("/cowboy.png").c_str(), true, "testModel", {1.0f,1.0f,0.3f, 0.3f});


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

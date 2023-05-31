#include "resourceManager.hpp"
#include "gameObject.hpp"
gameObject::gameObject(SpriteRenderer *spriteRender, std::string name, SDL_FRect initRect)
{
    objName = name;
    spriteRenderer = spriteRender;
    renderRect = initRect;
    rotation = 0;
} 
void gameObject::Render()
{
    Texture2D myTex;
    myTex = ResourceManager::GetTexture(objName);
    spriteRenderer->DrawSprite(myTex,glm::vec2(renderRect.x, renderRect.y), glm::vec2(renderRect.w, renderRect.h), rotation, color);
} 

gameObject::~gameObject()
{
} 
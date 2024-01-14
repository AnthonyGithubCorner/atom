#include "gameObject.hpp"

#include "resourceManager.hpp"
#include <SDL.h>

gameObject::gameObject(ModelRenderer *modelRender, std::string name, SDL_FRect initRect, int Level, float IntoScreenStretch)
{
    objName = name;
    currentModelRenderer = modelRender;
    renderRect = initRect;
    rotation = 0;
    if(intoScreenStretch==-1.0f){
    	IntoScreenStretch = initRect.h;
    }
    intoScreenStretch = -0.5;
    level = Level;
    UI = true;

}

gameObject::gameObject(ModelRenderer *modelRender, std::map<std::string, std::vector<ModelRenderer*>> model_animations, std::string name, SDL_FRect initRect, int Level, SDL_FRect initTrigRect, float IntoScreenStretch)
{
    objName = name;
    currentModelRenderer = modelRender;
    renderRect = initRect;
    rotation = 0;
    if(intoScreenStretch==-1.0f){
    	IntoScreenStretch = initRect.h;
    }
    intoScreenStretch = IntoScreenStretch;
    level = Level;
    animations = model_animations;
    frame_index = 0;
    triggerRect = initTrigRect;
    UI = false;

}


void gameObject::Render()
{
    Texture2D myTex;
    myTex = ResourceManager::GetTexture(objName);
    currentModelRenderer->DrawModel(myTex,glm::vec2(renderRect.x, renderRect.y), glm::vec3(renderRect.w, renderRect.h, intoScreenStretch), level, glm::vec3(rotation), color);
}

void gameObject::selectAnim(std::string anim_name)
{
	frame_index = 0;
	cur_animation = animations[anim_name];
	currentModelRenderer = cur_animation[frame_index];
}

void gameObject::nextFrame()
{
	frame_index++;
	if(cur_animation.size() <= frame_index)
	{
		frame_index = 0;
	}
	currentModelRenderer = cur_animation[frame_index];
}

gameObject::~gameObject()
{
}

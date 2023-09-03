#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SDL_rect.h"
#include "modelRenderer.hpp"
#include "shader.hpp"
#include <string>
#include <map>
#include <vector>


class gameObject
{
public:
    // Constructor (inits shaders/shapes)
    gameObject(ModelRenderer *modelRender, std::string name, SDL_FRect initRect = {0.3f,0.3f,0.1f,0.1f}, int Level = 0, float IntoScreenStretch = -1.0f);
    gameObject(ModelRenderer *modelRender, std::map<std::string, std::vector<ModelRenderer*>> model_animations, std::string name, SDL_FRect initRect = {0.3f,0.3f,0.1f,0.1f}, int Level = 0, SDL_FRect triggerRect = {0.0f,0.0f,0.0f,0.0f}, float IntoScreenStretch = -1.0f);
    // Destructor
    ~gameObject();
    void nextFrame();
    // Renders a defined quad textured with given sprite
    void setX(float x) {renderRect.x = x;}
    void setY(float y) {renderRect.y = y;}
    void setW(float w){renderRect.w = w;}
    void setH(float h){renderRect.h = h;}
    void setRect(float x, float y, float w, float h){setX(x);setY(y);setW(w);setH(h);}
    void setRotation(int r){rotation = r;}
    void setColor(glm::vec3 newColour){color = newColour;}
    void Render();
    void selectAnim(std::string anim_name);
    std::string objName;
    SDL_FRect renderRect;
    SDL_FRect triggerRect;
    int rotation;
    float intoScreenStretch;
    uint8_t level;
    ModelRenderer* currentModelRenderer; // Sprite
    std::map<std::string, std::vector<ModelRenderer*>> animations;
	bool enableActions = true;
	bool enableRender = true;
private:
    std::vector<ModelRenderer*> cur_animation;
    int frame_index = 0;
    glm::vec3 color = glm::vec3(1.0f);



};

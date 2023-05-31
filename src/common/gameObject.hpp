/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SDL_rect.h"
#include "spriteRenderer.hpp"
#include "shader.hpp"


class gameObject
{
public:
    // Constructor (inits shaders/shapes)
    gameObject(SpriteRenderer *spriteRender, std::string name, SDL_FRect initRect = {0,0,0.1f,0.1f});
    // Destructor
    ~gameObject();
    // Renders a defined quad textured with given sprite
    void setX(float x) {renderRect.x = x;}
    void setY(float y) {renderRect.y = y;}
    void setW(float w){renderRect.w = w;}
    void setH(float h){renderRect.h = h;}
    void setRect(float x, float y, float w, float h){setX(x);setY(y);setW(w);setH(h);}
    void setRotation(int r){rotation = r;}
    void setColor(glm::vec3 newColour){color = newColour;}
    void Render();
    std::string objName;
    SDL_FRect renderRect;
    int rotation;
private:
    glm::vec3 color = glm::vec3(1.0f);


    SpriteRenderer* spriteRenderer; // Sprite
};

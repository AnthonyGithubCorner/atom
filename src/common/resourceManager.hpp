/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.hpp"
#include "shader.hpp"
#include "gameObject.hpp"
#include "animatedGameObject.hpp"
#include "SDL_surface.h"
#include "gameObject.hpp"
#include "../UI/dialogue/word_renderer/word_renderer.hpp"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
// The Width of the screen
extern int SCREEN_WIDTH;
// The height of the screen
extern int SCREEN_HEIGHT;

class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, ModelRenderer*> ModelRenderers;
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, gameObject*> gameObjects;
    static std::map<std::string, WordRenderer*> WordRenderers;
    static std::map<std::string, std::vector<std::string>> Dialogues;

    static ModelRenderer* LoadModelRenderer(Shader &shader, const char *modelOBJfile, std::string name);
    static ModelRenderer* GetModelRenderer(std::string name);

    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader    GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);

    // Loads the gameobjects
    static gameObject* LoadGameObject(ModelRenderer *modelRender, const char *file, bool alpha, std::string name, SDL_FRect initRect, uint8_t level);
    static gameObject* LoadGameObject(ModelRenderer *modelRender, std::map<std::string, std::vector<ModelRenderer*>> model_animations, const char *file, bool alpha, std::string name, SDL_FRect initRect, uint8_t level, SDL_FRect triggerRect);

    static gameObject* getGameObject(std::string name);

    // Loads the word renderers for dialogue
    static WordRenderer* LoadWordRenderer(ModelRenderer *modelRender, const char *file, bool alpha, std::string name, int font_size, SDL_Color color);
    static WordRenderer* getWordRenderer(std::string name);

    static std::vector<std::string> LoadDialogue(const char *file_path, std::string name);
    static std::vector<std::string> getDialogue(std::string name);

    // properly de-allocates all loaded resources
    static void      Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif

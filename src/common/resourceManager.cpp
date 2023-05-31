/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "resourceManager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/SOIL.h"
#include "../load_asset/loadAsset.hpp"
#include "SDL_surface.h"
#include <SDL_image.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, gameObject*>       ResourceManager::gameObjects;


Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

gameObject* ResourceManager::LoadGameObject(SpriteRenderer *spriteRender, const char *file, bool alpha, std::string name, SDL_FRect initRect)
{
    LoadTexture(file, alpha, name);
    gameObjects[name] = new gameObject(spriteRender, name, initRect);

    return gameObjects[name];
}
gameObject* ResourceManager::getGameObject(std::string name){
    return gameObjects[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
    for (auto iter : gameObjects)
        delete (iter.second);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();


    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    Texture2D texture;
    SDL_Surface* Surface = IMG_Load(file);
    // create texture object
    Uint8 colors = Surface->format->BytesPerPixel;
    if (colors == 4) {   // alpha
                texture.Internal_Format = GL_RGBA;
                texture.Image_Format = GL_RGBA;
        
    }
    else {             // no alpha
            texture.Internal_Format = GL_RGB;
            texture.Image_Format = GL_RGB;
        
    }
    texture.Filter_Max = GL_LINEAR;
    texture.Filter_Min = GL_LINEAR;
    // now generate texture
    texture.Generate(Surface->w, Surface->h, Surface->pixels);
	SDL_FreeSurface(Surface);
	return texture;
}

Texture2D ResourceManager::loadTextureFromSDL2Surface(SDL_Surface* Surface)
{
    // create texture object
    Texture2D texture;
    Uint8 colors = Surface->format->BytesPerPixel;
    if (colors == 4) {   // alpha
                texture.Internal_Format = GL_RGBA;
                texture.Image_Format = GL_RGBA;
        
    }
    else {             // no alpha
            texture.Internal_Format = GL_RGB;
            texture.Image_Format = GL_RGB;
        
    }
    texture.Filter_Max = GL_LINEAR;
    texture.Filter_Min = GL_LINEAR;
    // now generate texture
    texture.Generate(Surface->w, Surface->h, Surface->pixels);
    SDL_FreeSurface(Surface);
    // and finally free image data
    return texture;
}
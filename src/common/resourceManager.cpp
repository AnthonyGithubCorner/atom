#include "resourceManager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include "SOIL.h"
#include "../load_asset/loadAsset.hpp"
#include "SDL_surface.h"
#include <SDL_image.h>

// TODO find a better home
// The Width of the screen
int SCREEN_WIDTH = 1000;
// The height of the screen
int SCREEN_HEIGHT = 500;
// Instantiate static variables
std::map<std::string, ModelRenderer*>    ResourceManager::ModelRenderers;
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Sound*>       ResourceManager::Sounds;
std::map<std::string, Music*>       ResourceManager::Musics;
std::map<std::string, gameObject*>       ResourceManager::gameObjects;
std::map<std::string, WordRenderer*> ResourceManager::WordRenderers;
std::map<std::string, sceneInterpretter*> ResourceManager::scenes;
std::map<std::string, std::vector<std::string>> ResourceManager::Dialogues;
sceneInterpretter* current_scene;

sceneInterpretter* ResourceManager::switch_scene(sceneInterpretter* new_scene)
{
	new_scene.startScene();
}

sceneInterpretter* ResourceManager::LoadSceneInterpretter(const char *file, std::string name)
{
	scenes[name] = new sceneInterpretter(file);
	return scenes[name];
}

sceneInterpretter* ResourceManager::GetSceneInterpretter(std::string name)
{
	return scenes[name];
}

Sound* ResourceManager::LoadSound(const char *file, std::string name)
{
	Sounds[name] = new Sound(file);
	return Sounds[name];
}

Sound* ResourceManager::getSound(std::string name)
{
	return Sounds[name];
}

Music* ResourceManager::LoadMusic(const char *file, std::string name)
{
	Musics[name] = new Music(file);
	return Musics[name];
}

Music* ResourceManager::getMusic(std::string name)
{
	return Musics[name];
}

ModelRenderer* ResourceManager::LoadModelRenderer(Shader &shader, const char *modelOBJfile, std::string name)
{
	ModelRenderers[name] = new ModelRenderer(shader, modelOBJfile);
    return ModelRenderers[name];
}

ModelRenderer* ResourceManager::GetModelRenderer(std::string name)
{
    return ModelRenderers[name];
}

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

gameObject* ResourceManager::LoadGameObject(ModelRenderer *modelRender, const char *file, bool alpha, std::string name, SDL_FRect initRect, uint8_t level)
{
    LoadTexture(file, alpha, name);
    gameObjects[name] = new gameObject(modelRender, name, initRect, level);

    return gameObjects[name];
}


gameObject* ResourceManager::LoadGameObject(ModelRenderer *modelRender, std::map<std::string, std::vector<ModelRenderer*>> model_animations, const char *file, bool alpha, std::string name, SDL_FRect initRect, uint8_t level, SDL_FRect triggerRect)
{
    LoadTexture(file, alpha, name);
    gameObjects[name] = new gameObject(modelRender, model_animations, name, initRect, level, triggerRect);

    return gameObjects[name];
}

gameObject* ResourceManager::getGameObject(std::string name){
    return gameObjects[name];
}

WordRenderer* ResourceManager::LoadWordRenderer(ModelRenderer *modelRender, const char *file, bool alpha, std::string name, int font_size, SDL_Color color)
{
	 LoadTexture(file, alpha, name);
	 WordRenderers[name] = new WordRenderer(modelRender, file, font_size, color);

	 return WordRenderers[name];
}

WordRenderer* ResourceManager::getWordRenderer(std::string name)
{
	 return WordRenderers[name];
}

std::vector<std::string> ResourceManager::LoadDialogue(const char *file_path, std::string name)
{
	std::vector<std::string> _lines;
	std::ifstream file(file_path);
	if(file.fail()){
		SDL_Log("file not found");
	}
	std::string line;
	while (std::getline(file, line))
	{
		_lines.push_back(line);
	}

	 Dialogues[name] = _lines;
	 file.close();


	 return Dialogues[name];
}

std::vector<std::string> ResourceManager::getDialogue(std::string name)
{
	 return Dialogues[name];
}

void ResourceManager::Clear()
{
    for (auto iter : ModelRenderers)
        delete (iter.second);

    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
    for (auto iter : gameObjects)
        delete (iter.second);

    for (auto iter : WordRenderers)
        delete (iter.second);

    for (auto iter : Sounds)
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



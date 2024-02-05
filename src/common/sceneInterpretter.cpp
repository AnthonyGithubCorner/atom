#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <SDL.h>
#include <fstream>
#include "../json/json.hpp"
#include "resourceManager.hpp"
#include "sceneInterpretter.hpp"
using json = nlohmann::json;

sceneInterpretter::sceneInterpretter(const char *scene){
		std::ifstream scene_file(scene);
	    if (scene_file.fail())
	    {
	        SDL_Log("scene data file not found");
	        return;
	    }
        json scene_data = json::parse(scene_file);
	    std::string name = scene_data["name"];

		 SDL_FRect pos ={0.0f};
	    //  std::string type = scene_data["type"];
		 SDL_FRect trigRect = {0.0f};
         for(auto &it : scene_data["objects"])
         {
	    std::string object_name = it["name"];
		 pos.x = it["x"];
		 pos.y = it["y"];
		 pos.w = it["w"];
		 pos.h = it["h"];

		 if(it.contains("trigger"))
				 {
			 trigRect.x = it["trigger"]["x"];
			 trigRect.y = it["trigger"]["y"];
			 trigRect.w = it["trigger"]["w"];
			 trigRect.h = it["trigger"]["h"];
				 }

		 uint8_t level = it["level"];
     	ResourceManager::getGameObject(object_name)->renderRect = pos; 
		ResourceManager::getGameObject(object_name)->triggerRect = trigRect; 
	    ResourceManager::getGameObject(object_name)->enableActions = true;
	   ResourceManager::getGameObject(object_name)->enableRender = true;
         }
         }
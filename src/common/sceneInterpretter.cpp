#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <SDL.h>
#include <fstream>
#include "resourceManager.hpp"
#include "sceneInterpretter.hpp"
using json = nlohmann::json;

sceneInterpretter::sceneInterpretter(const char *scene){
path_file = scene;
         }

#ifdef HOT_RELOAD
bool sceneInterpretter::isModified()
{
	struct stat result;
	if(stat(path_file.c_str(), &result)==0)
	{
    	if(time_last_updated < result.st_mtime)
		{
			time_last_updated = result.st_mtime;
			return true;
		}
		else
		{
			return false;
		}
	}
}
#endif
void sceneInterpretter::startScene()
{

		std::ifstream scene_file(path_file);
	    if (scene_file.fail())
	    {
	        SDL_Log("scene data file not found");
	        return;
	    }
        json scene_data = json::parse(scene_file);
	SDL_Log("EnabSTART");
	 SDL_FRect pos ={0.0f};
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
	SDL_Log("Enabled GO: %s", object_name.c_str());
	   ResourceManager::getGameObject(object_name)->enableRender = true;
         }
}

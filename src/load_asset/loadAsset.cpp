#include <SDL.h>
#include <string>
#include "loadAsset.hpp"

//taken from here https://www.willusher.io/sdl2%20tutorials/2014/06/16/postscript-0-properly-finding-resource-paths


// void init_assets(const char* argv0){
//     PhysFS::init(argv0);
//     PhysFS::mount("/Users/anthony/Documents/Trials of a Shattered Heart/assets/", "", 1);
//     PhysFS::mount("/Users/anthony/Documents/Trials of a Shattered Heart/", "", 1);
// }

std::string load_asset(const char * asset_relative_path){
    #ifdef _WIN32
	const char PATH_SEP = '\\';
	asset_full_path = "God knows";
    #else
	//Assuming MacOS App is Packaged
	const char PATH_SEP = '/';
    static std::string base_dir;
	if (base_dir.empty()){
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *base_path_search = SDL_GetBasePath();
		if (base_path_search){
			base_dir = base_path_search;
			SDL_free(base_path_search);
		}
		else {
			SDL_Log("Error getting asset path");
            return "";
		}
		size_t pos = base_dir.rfind("MacOS");
        SDL_Log(base_dir.c_str());
		base_dir = base_dir.substr(0, pos) + "Resources";
	}

    std::string asset_full_path = base_dir + asset_relative_path;
    SDL_Log(asset_full_path.c_str());
	#endif
    return asset_full_path;
}

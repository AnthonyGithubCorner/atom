#include <SDL.h>
#include <string>
#include "loadAsset.hpp"

//taken from here https://www.willusher.io/sdl2%20tutorials/2014/06/16/postscript-0-properly-finding-resource-paths

std::string resource_path;

std::string load_asset(const char * asset_relative_path){
    #ifdef _WIN32
	const char PATH_SEP = '\\';
	asset_full_path = "God knows";
    #else
	//Assuming MacOS App is Packaged
	const char PATH_SEP = '/';
    static std::string base_dir = resource_path;
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
        SDL_Log(base_dir.c_str());
	}

    std::string asset_full_path = base_dir + asset_relative_path;
    SDL_Log(asset_full_path.c_str());
	#endif
    return asset_full_path;
}

Texture2D loadTextureFromSDL2Surface(SDL_Surface* Surface)
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

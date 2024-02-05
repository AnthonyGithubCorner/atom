#ifndef LOAD_ASSET
#define LOAD_ASSET

#include <string>
#include "../common/texture.hpp"
#include <SDL.h>
std::string load_asset(const char * asset);
extern std::string resource_path;
Texture2D loadTextureFromSDL2Surface(SDL_Surface* Surface);
#endif

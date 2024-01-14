#include <unordered_map>
#include "word_renderer.hpp"
#include <SDL.h>
#include <string>

#include "andaleInfo.hpp"

std::string usedCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'.?,!-";
WordRenderer::WordRenderer(ModelRenderer *modelRender, const char *font_path, int font_size, SDL_Color color){

	modelRenderer = modelRender;
	font = IMG_Load(font_path);

    SDL_Rect charRect = {0};
    fontColor = color;
    font_width = font_size;
    font_heigth = font_size;
        SDL_PixelFormat *format;
    format = font->format;
    // float scale = 0.5;
    for(auto c:rtpDescAtlas){
        SDL_Surface *temp = SDL_CreateRGBSurface( font->flags, charRect.w , charRect.h, format->BitsPerPixel,
                                                    format->Rmask, format->Gmask, format->Bmask, format->Amask );
        charRect.x = c.positionX;
        charRect.y = c.positionY;
        charRect.w = c.sourceWidth + c.charOffsetX; // from looking at font
        charRect.h = c.sourceHeight; // from looking at font
        SDL_BlitSurface(font,
                    &charRect,
                    temp,
                    NULL);
        _font_database[(char)c.charValue] = loadTextureFromSDL2Surface(temp);
    }

    // for(int i=0; i<usedCharacters.length();i++){
    //     temp = usedCharacters[i];
    //     surface = TTF_RenderText_Blended(_font, temp.c_str(), color);
    //     _font_database[usedCharacters[i]] = ResourceManager::loadTextureFromSDL2Surface(surface);
    // }
}

void WordRenderer::render_word(std::string word, SDL_FRect *position){
    for(int i=0; i<word.length();i++){
        if(word[i] != ' '){
        	modelRenderer->DrawModel(_font_database[word[i]], glm::vec2(position->x, position->y), glm::vec3(position->w, position->h, 1.0f), 255, glm::vec3(0), glm::vec3(fontColor.r, fontColor.g,fontColor.b));
        }
        // space them out
        position->x += position->w;
    }
}

WordRenderer::~WordRenderer(){
    // TTF_CloseFont(_font);
}

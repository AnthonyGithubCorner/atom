#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include "../../../common/modelRenderer.hpp"

class WordRenderer{
    public:
    WordRenderer(ModelRenderer *modelRender, const char *font_path, int font_size, SDL_Color color);
    ~WordRenderer();

    void render_word(std::string word, SDL_FRect *position);

    int font_width;
    int font_heigth;
    ModelRenderer *modelRenderer;


    private:
    SDL_Surface * font;
    SDL_Color fontColor;
    std::unordered_map<char, Texture2D> _font_database;
};

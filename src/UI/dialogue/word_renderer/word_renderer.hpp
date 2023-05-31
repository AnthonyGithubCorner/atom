#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "../../../common/resourceManager.hpp"
#include "../../../common/spriteRenderer.hpp"
#include <SDL.h>
#include <SDL_image.h>

class WordRenderer{
    public:
    WordRenderer(const char *font_path, int font_size, SDL_Color color);
    ~WordRenderer();

    void render_word(std::string word, SDL_FRect *position, SpriteRenderer *renderer);

    int font_width;
    int font_heigth;


    private:
    SDL_Surface * font;
    SDL_Color fontColor;
    std::unordered_map<char, Texture2D> _font_database;
};
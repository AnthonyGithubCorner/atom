#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "word_renderer/word_renderer.hpp"
#include "../../common/spriteRenderer.hpp"

class Dialogue{
    public:
    Dialogue(const char *dialogue_path);
    void render_dialogue(SDL_FRect textBox, SpriteRenderer *renderer, SDL_Window *window,WordRenderer *word_renderer, WordRenderer *button_renderer, WordRenderer *excited_renderer);


    private:
    std::vector<std::string> _lines;

};

void rendererUI(SDL_Renderer *renderer, SDL_Window *window,WordRenderer *word_renderer, WordRenderer *button_renderer);
void init_dialogue(const char *dialogue_path);

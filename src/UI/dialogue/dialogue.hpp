#pragma once

#include <string>
#include <vector>
#include "word_renderer.hpp"

void render_dialogue(int height, int width, std::string dialogue_name, std::string word_renderer_name, std::string button_renderer_name, std::string excited_renderer_name);

void rendererUI(SDL_Renderer *renderer, SDL_Window *window,WordRenderer *word_renderer, WordRenderer *button_renderer);
void init_dialogue(const char *dialogue_path);
void _change_line(int line);

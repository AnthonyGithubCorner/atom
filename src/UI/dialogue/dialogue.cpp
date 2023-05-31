#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "dialogue.hpp"
#include "word_renderer/word_renderer.hpp"
#include "../buttons/buttonClass.hpp"

int current_line = 1;
void _change_line(int line){
        current_line = line;
}

Dialogue::Dialogue(const char *dialogue_path){
    //rewrite this some point
    std::ifstream file(dialogue_path);
    if(file.fail()){
        SDL_Log("file not found");
        return;
    }
    std::string line; 
    while (std::getline(file, line))
    {
        _lines.push_back(line);
    }

    //reset Dialogue. Only one dialogue allowed at a time or else they overwrite this variable bad design fix later
    current_line = 1;
    file.close();
}


void Dialogue::render_dialogue(SDL_FRect textBox, SpriteRenderer *renderer, SDL_Window *window,WordRenderer *word_renderer, WordRenderer *button_renderer, WordRenderer *excited_renderer = nullptr)
{
    SDL_Rect currentViewportRect;
    
    ResourceManager::getGameObject("textBox")->renderRect = textBox;
    ResourceManager::getGameObject("textBox")->Render();
    // assign viewport
    float currentx = textBox.x + 0.05f;
    float currenty = textBox.y + 0.15f;
    SDL_GetWindowSize(window,&currentViewportRect.w, &currentViewportRect.h);

    SDL_FRect rect;
    float relativeWidth = (float)word_renderer->font_width/currentViewportRect.w;
    float relativeHeight = (float)word_renderer->font_heigth/currentViewportRect.h;
    // size of each character
    rect.x = currentx;
    rect.y = currenty;
    rect.w = relativeWidth;
    rect.h = relativeHeight;

    bool end = false;

    WordRenderer *current_word_renderer = word_renderer;

    if (current_line != 0)
    {
        std::istringstream iss(_lines[current_line-1]);
        std::string wordToAdd;
        std::string tempWord;
        int next_line;
        while (!iss.eof())
        {
            iss >> wordToAdd;
            if (rect.x + wordToAdd.length() * relativeWidth  > textBox.w + textBox.x)
            {
                rect.x = currentx;
                rect.y += relativeHeight + 0.05f;
            }

            //check for special char
            if(wordToAdd == "D"){
                current_word_renderer = button_renderer;
                iss >> next_line;
                //assume option is not empty
                iss >> wordToAdd;
                iss >> tempWord;
                while(tempWord != "D"){
                    wordToAdd.push_back(' ');
                    wordToAdd.append(tempWord);
                    iss >> tempWord;
                    if(iss.eof()){
                        break;
                    }
                }
                wordToAdd.push_back(' ');
                if (rect.x + wordToAdd.length() * relativeWidth  > textBox.w + textBox.x)
                {
                    rect.x = currentx;
                    rect.y += relativeHeight + 0.05f;
                }
                infoWindowGCButton({rect.x, rect.y, static_cast<float>(rect.w*wordToAdd.length()), rect.h}, _change_line, next_line);
            }
            else if(wordToAdd == "/"){
                wordToAdd = "";
                rect.x = currentx;
                rect.y += relativeHeight + 0.05f;
            }
            else if(wordToAdd == "!"){
                current_word_renderer = excited_renderer;
                iss >> wordToAdd;
                iss >> tempWord;
                while(tempWord != "*"){
                    wordToAdd.push_back(' ');
                    wordToAdd.append(tempWord);
                    iss >> tempWord;
                    if(iss.eof()){
                        break;
                    }
                }
                wordToAdd.push_back(' ');
            }
            else{
                current_word_renderer=word_renderer;
                // add space to end
                wordToAdd.push_back(' ');
                
            }


            current_word_renderer->render_word(wordToAdd, &rect, renderer); // rect.x + rect.w here for some reason
        }
    }

}


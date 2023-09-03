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
#include "../../common/resourceManager.hpp"

int current_line = 1;

void _change_line(int line){
        current_line = line;
}
SDL_FRect textBox = {0.1f, 0.4f, 0.8f, 0.7f};
std::string text_box_name = "textBox";
void render_dialogue(int height, int width, std::string dialogue_name, std::string word_renderer_name, std::string button_renderer_name, std::string excited_renderer_name)
{

    WordRenderer* word_renderer = ResourceManager::getWordRenderer(word_renderer_name);
    WordRenderer* button_renderer = ResourceManager::getWordRenderer(button_renderer_name);
    WordRenderer* excited_renderer = ResourceManager::getWordRenderer(excited_renderer_name);
    std::vector<std::string> _lines = ResourceManager::getDialogue(dialogue_name);

    SDL_Rect currentViewportRect;
    
    ResourceManager::getGameObject(text_box_name)->renderRect = textBox;
    ResourceManager::getGameObject(text_box_name)->Render();
    // assign viewport
    float currentx = textBox.x + 0.05f;
    float currenty = textBox.y + 0.15f;

    SDL_FRect rect;
    float relativeWidth = (float)word_renderer->font_width/width;
    float relativeHeight = (float)word_renderer->font_heigth/height;
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


            current_word_renderer->render_word(wordToAdd, &rect); // rect.x + rect.w here for some reason
        }
    }

}


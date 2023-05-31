#include "buttonClass.hpp"

std::vector<infoWindowGCButton> infoWindowEvents;

void buttonClass::CheckIfClicked(float x, float y){
    if((_rect.x <= x && _rect.x + _rect.w >= x) && (_rect.y <= y && _rect.y + _rect.h >= y)){
        operation();
    }
}

infoWindowGCButton::infoWindowGCButton(SDL_FRect rect, void(*func)(int), int line)
{
    _rect = rect;
    _func = func;
    _line = line;
    infoWindowEvents.push_back(*this);
}

void infoWindowGCButton::operation()
{
    _func(_line);
}
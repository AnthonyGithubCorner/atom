#ifndef buttonClass_H // include guard
#define buttonClass_H
#include <SDL.h>
#include <vector>

//Abstract Class
class buttonClass
{
protected:
    SDL_FRect _rect;

public:
    virtual void operation() = 0;
    void CheckIfClicked(float x, float y);
};


//For UI
class infoWindowGCButton : public buttonClass
{
private:
    int _line;
    void(*_func)(int);
public:
    infoWindowGCButton(SDL_FRect rect, void(*func)(int), int line);
    void operation();
    
};

extern std::vector<infoWindowGCButton> infoWindowEvents;
#endif



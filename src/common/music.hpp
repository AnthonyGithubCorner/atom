#ifndef MUSIC_H
#define MUSIC_H
#include <SDL_mixer.h>
#include <SDL.h>
class Music
{
public:
    // constructor
	Music(const char *musicSource);
    ~Music();
    // play sound effect (that loops (loopNum) amount of times by default only once)
    void play();

private:
    Mix_Music * sound;
};

#endif

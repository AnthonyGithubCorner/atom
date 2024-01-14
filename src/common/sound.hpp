#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>
#include <SDL.h>
class Sound
{
public:
    // constructor
    Sound(const char *soundSource);
    ~Sound();
    // play sound effect (that loops (loopNum) amount of times by default only once)
    void play(int loopNum = 0);

private:
	Mix_Chunk * sound;
};

#endif

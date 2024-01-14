/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <iostream>

#include "sound.hpp"

Sound::~Sound()
{
	delete sound;
}
Sound::Sound(const char *soundSource)
{
	sound = Mix_LoadWAV(soundSource);
}

void Sound::play(int loopNum)
{
	Mix_PlayChannel( -1, sound, 0 );
}

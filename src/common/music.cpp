/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <iostream>

#include "music.hpp"

Music::~Music()
{
	delete sound;
}
Music::Music(const char *musicSource)
{
	sound = Mix_LoadMUS(musicSource);
}

void Music::play()
{
    Mix_HaltMusic();
	Mix_PlayMusic(sound, -1);
}

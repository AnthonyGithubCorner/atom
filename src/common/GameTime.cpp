/*
 * GameTime.cpp
 *
 *  Created on: Aug. 28, 2023
 *      Author: anthony
 */

#include "GameTime.hpp"
#include <SDL.h>

std::map<int, timer> GameTime::Timers;
int GameTime::TimerIDIndex = 0;

int GameTime::startTime()
{
	timer new_timer = {SDL_GetTicks64()};
	Timers[TimerIDIndex] = new_timer;
	TimerIDIndex++;
	return TimerIDIndex;
}

unsigned long long GameTime::getTime(int timerID)
{
	unsigned long long delta_time = 0;

	delta_time = SDL_GetTicks64() - Timers[timerID].startTime;

//	Timers.erase(timerID);
	return delta_time;
}

void GameTime::restartTime(int timerID)
{
	Timers[timerID].startTime = SDL_GetTicks64();

//	Timers.erase(timerID);
	return;
}

void GameTime::stopTime(int timerID)
{
	Timers.erase(timerID);
	return;
}


/*
 * GameTime.h
 *
 *  Created on: Aug. 28, 2023
 *      Author: anthony
 */

#ifndef SRC_COMMON_GAMETIME_HPP_
#define SRC_COMMON_GAMETIME_HPP_

#include <map>
#include <string>

struct timer
{
	unsigned long long startTime;
};

class GameTime
{
public:

	 static int startTime();
	 static unsigned long long getTime(int timerID);
	 static void restartTime(int timerID);
	 static void stopTime(int timerID);
private:
	 GameTime() {};
	 static std::map<int, timer> Timers;
	 static int TimerIDIndex;
};

#endif /* SRC_COMMON_GAMETIME_HPP_ */

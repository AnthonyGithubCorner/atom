/*
 * stateManager.hpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#ifndef SRC_INTERACTIONFILE_STATEMANAGER_HPP_
#define SRC_INTERACTIONFILE_STATEMANAGER_HPP_

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <SDL_stdinc.h>

class stateManager
{
public:
	static std::map<std::string, bool>       globalStates;
	static Uint32 setState(Uint32 x, void * state);
	static Uint32 setState(std::string state);
	static Uint32 clearState(Uint32 x, void * state);
	static Uint32 clearState(std::string state);
	static bool getState(std::string state);


private:
	stateManager() {};
};

#endif /* SRC_INTERACTIONFILE_STATEMANAGER_HPP_ */

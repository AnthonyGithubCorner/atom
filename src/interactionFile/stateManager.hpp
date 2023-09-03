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
class stateManager
{
public:
	static std::map<std::string, bool>       globalStates;
	static void setState(std::string state);
	static bool getState(std::string state);
	static void clearState(std::string state);

private:
	stateManager() {};
};

#endif /* SRC_INTERACTIONFILE_STATEMANAGER_HPP_ */

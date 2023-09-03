/*
 * stateManager.cpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#include "stateManager.hpp"

std::map<std::string, bool>       stateManager::globalStates;

 void stateManager::setState(std::string state)
 {
	 globalStates[state] = true;
 }
 bool stateManager::getState(std::string state)
 {
	 bool returnValue;

	 if (globalStates.find(state)==globalStates.end())
	 {
		 returnValue = false;
	 }
	 else
	 {
		 returnValue = globalStates[state];
	 }

	 if (globalStates.find(state.substr(1))==globalStates.end() && state[0] == '!')
	 {
		 returnValue = true;
	 }
	 else
	 {
		 if(state[0] == '!')
		 {
			 returnValue = !globalStates[state.substr(1)];
		 }
	 }
	 return returnValue;
 }
 void stateManager::clearState(std::string state)
 {
	 globalStates[state] = false;
 }


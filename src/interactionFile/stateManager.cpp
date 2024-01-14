/*
 * stateManager.cpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#include "stateManager.hpp"

std::map<std::string, bool>       stateManager::globalStates;


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
 Uint32 stateManager::setState(Uint32 x, void * state)
  {
	 char *s = static_cast<char *>(state);
	 std::string str(s);
 	 globalStates[str] = true;
  }
 Uint32 stateManager::setState(std::string state)
  {
 	 globalStates[state] = true;
  }

 Uint32 stateManager::clearState(Uint32 x, void * state)
  {
	 char *s = static_cast<char *>(state);
	 std::string str(s);
 	 globalStates[str] = false;
  }
 Uint32 stateManager::clearState(std::string state)
 {
	 globalStates[state] = false;
 }


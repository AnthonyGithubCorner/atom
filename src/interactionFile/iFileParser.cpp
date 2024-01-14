/*
 * iFileParser.cpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#include "iFileParser.hpp"

#include "actionLoader.hpp"
#include "stateManager.hpp"




int constantTime(int prev_delay)
{
	return prev_delay;
}

int setUpTime(int prev_delay, int step_up)
{
	return prev_delay + step_up;
}

std::vector<std::string> delay_words;

iFileParser::iFileParser(const char *iFile_path)
{
	//rewrite this some point
	std::ifstream file(iFile_path);
	if (file.fail())
	{
		SDL_Log("file not found");
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		_lines.push_back(line);
	}

	file.close();
	setLocalState("START");
//	registerAllActions();  // make this static
}

iFileParser::~iFileParser()
{
	// TODO Auto-generated destructor stub
}

Uint32 iFileParser::setLocalState(std::string state)
{
	localStates[state] = true;
	return 0;
}
bool iFileParser::getLocalAndGlobalState(std::string state)
{
	 bool returnValue;

	 // check localVars than return globals
	 bool found = false;

	 if (localStates.find(state)==localStates.end())
	 {
		 returnValue = false;
	 }
	 else
	 {
		 found = true;
		 returnValue = localStates[state];
	 }

	 if (localStates.find(state.substr(1))==localStates.end() && state[0] == '!')
	 {
		 returnValue = true;
	 }
	 else
	 {
		 if(state[0] == '!')
		 {
			 found = true;
			 returnValue = !localStates[state.substr(1)];
		 }
	 }
	 if(!found)
	 {
		 returnValue = stateManager::getState(state);
	 }
	 return returnValue;
}
void iFileParser::clearLocalState(std::string state)
{
	localStates[state] = false;
}

void iFileParser::executeFile(gameObject *object)
{
	int current_line = 0;
	int current_func_exc = 0;
    std::string nextWord;
    std::string skipLines;

    std::string parameter;

	while (current_line < _lines.size())
	{

		if(_lines[current_line].empty()){
			current_line++;
			continue;
		}

		std::istringstream iss(_lines[current_line]);

		iss >> nextWord;
			//check for special char
			if (nextWord == "IF")
			{
				bool skip = false;
				iss >> nextWord;
				if(nextWord.back() == '(')
				{
					std::getline( iss, parameter, ')' );

					nextWord.erase(nextWord.end() - 1);
					parameter.erase(parameter.end() - 1);
					parameter.erase(parameter.begin());
					if(!actionLoader::conds[nextWord](object, parameter))
					{
						skip = true;
					}
				}
				else if(!getLocalAndGlobalState(nextWord))
				{
					skip = true;
				}
				iss >> nextWord;
				while(nextWord == "AND")
				{
					iss >> nextWord;
					if(nextWord.back() == '(')
					{
						std::getline( iss, parameter, ')' );

						nextWord.erase(nextWord.end() - 1);
						parameter.erase(parameter.end() - 1);
						parameter.erase(parameter.begin());
						if(!actionLoader::conds[nextWord](object, parameter))
						{
							skip = true;
						}
					}
					else if(!getLocalAndGlobalState(nextWord))
					{
						skip = true;
					}
					iss >> nextWord;
				}
				if(skip)
				{
					int nestLevel = 1;
//					if(nextWord == "OR")
//					{
//						iss >> nextWord;
//						if(nextWord.back() == '(')
//						{
//							std::getline( iss, parameter, ')' );
//							SDL_Log("Here is: %s", parameter.c_str());
//
//							nextWord.erase(nextWord.end() - 1);
//							parameter.erase(parameter.end() - 1);
//							parameter.erase(parameter.begin());
//							if(actionLoader::actions[nextWord](object, parameter))
//							{
//								break;
//							}
//						}
//						if(getLocalAndGlobalState(nextWord))
//						{
//							break;
//						}
//					}
					do
					{
						current_line++;
						skipLines = _lines[current_line];
						if(skipLines.substr(0, 2) == "IF" )
						{
							nestLevel++;
						}
						if(skipLines == "ENDIF" )
						{
							nestLevel--;
							if(nestLevel==0)
							{
								break;
							}
						}

					}
					while((skipLines != "ELSE"));
				}

			}
			else if (nextWord == "ELSE")
			{
				int nestLevel = 1;
				do
				{
					current_line++;
					skipLines = _lines[current_line];
					if(skipLines.substr(0, 2) == "IF" )
					{
						nestLevel++;
					}
					if(skipLines == "ENDIF" )
					{
						nestLevel--;
						if(nestLevel==0)
						{
							break;
						}
					}
				}
				while(nestLevel > 0);
			}
			else if (nextWord == "FUNC")
			{
				iss >> nextWord;
				current_line++;
				funcLoader[nextWord] = current_line;
				do
				{
					skipLines = _lines[current_line];
					current_line++;
				}
				while((skipLines != "ENDFUNC"));
			}
			else if (nextWord == "ENDFUNC")
			{
				current_line = _lines.size();

				// decrease func count
				funcsToExc[current_func_exc].number_to_repeat--;

				// go to next func
				current_func_exc++;
			}
			else if (nextWord == "QUITFUNC")
			{
				current_line = _lines.size();

				// dexecut one last time
				funcsToExc[current_func_exc].number_to_repeat = 0;

				// go to next func
				current_func_exc++;
			}
			else if (nextWord == "SET")
			{
				iss >> nextWord;

					setLocalState(nextWord);

			}
			else if (nextWord == "CLEAR")
			{
				iss >> nextWord;
				clearLocalState(nextWord);


			}
			else if (nextWord == "SETG")
			{
				iss >> nextWord;
				if(nextWord == "DELAY"){
					iss >> nextWord;
					Uint32 Delay = std::stoi(nextWord);
					iss >> nextWord;
					delay_words.push_back(nextWord);
					SDL_AddTimer(Delay, &stateManager::setState, const_cast<char *>(delay_words.back().c_str()));
					delay_words.pop_back();
				}
				else{
					stateManager::setState(nextWord);
				}

			}
			else if (nextWord == "CLEARG")
			{
				iss >> nextWord;
				if(nextWord == "DELAY"){
					iss >> nextWord;
					Uint32 Delay = std::stoi(nextWord);
					iss >> nextWord;
					delay_words.push_back(nextWord);
					SDL_AddTimer(Delay, &stateManager::clearState, const_cast<char *>(delay_words.back().c_str()));
					delay_words.pop_back();
				}
				else{
					stateManager::clearState(nextWord);
				}

			}
			else if (nextWord == "EXCIN")
			{
				iss >> nextWord;
				repetablefunc new_exc_func = {};
				new_exc_func.func_line = funcLoader[nextWord];
				iss >> nextWord;

				if( nextWord == "constant")
				{
					new_exc_func.delayFunc = constantTime;
					new_exc_func.ready = true;
				}

				iss >> nextWord;
				new_exc_func.number_to_repeat = std::stoi(nextWord);

				iss >> nextWord;
				new_exc_func.delay = std::stoi(nextWord);

				// func line is unique use that has timerID
				new_exc_func.funcID = GameTime::startTime();


				funcsToExc.push_back(new_exc_func);
//				current_line = funcLoader[nextWord];
//				if(nextWord.back() == '(')
//				{
//					std::getline( iss, parameter, ')' );
//				}

			}
//			else if (nextWord == "" || nextWord.empty())
//			{
//					break;
//			}
//			else if(nextWord == "ENDIF")
//			{
//				continue; //a END that doesn't matter
//			}
			else if(nextWord == "ONQUIT")
			{
				// execute on last run
				if(funcsToExc[current_func_exc].number_to_repeat != 1)
				{
					do
					{
						current_line++;
						skipLines = _lines[current_line];

					}
					while((skipLines != "ENDONQUIT"));
				}
			}
//			else if(nextWord == "ENDCOND")
//			{
//				continue; //a END that doesn't matter
//			}
			else
			{
				if(nextWord.back() == '(')
				{
					std::getline( iss, parameter, ')' );

					nextWord.erase(nextWord.end() - 1);
					parameter.erase(parameter.end() - 1);
					parameter.erase(parameter.begin());
					actionLoader::actions[nextWord](object, parameter);
				}

//				object->setX();

			}
		current_line++;

		// If reached the end execute functions
		if(current_line >= _lines.size())
		{
			if(funcsToExc.size() > current_func_exc)
			{
				// check that count isn't finished if so delete it only checks if equal to 0 if starts at -1 will repeat forever
				if(funcsToExc[current_func_exc].number_to_repeat == 0)
				{
					GameTime::stopTime(funcsToExc[current_func_exc].funcID);
					funcsToExc.erase(funcsToExc.begin()+current_func_exc);
				}
				else if(funcsToExc.size() > current_func_exc)
					{
						if(GameTime::getTime(funcsToExc[current_func_exc].funcID) > funcsToExc[current_func_exc].delay )
						{
							funcsToExc[current_func_exc].ready = true;
							GameTime::restartTime(funcsToExc[current_func_exc].funcID);
						}

						if(funcsToExc[current_func_exc].ready)
						{
							current_line = funcsToExc[current_func_exc].func_line;
							funcsToExc[current_func_exc].delay = funcsToExc[current_func_exc].delayFunc(funcsToExc[current_func_exc].delay);
							funcsToExc[current_func_exc].ready = false;
						}
					}
			}
			else
			{
				//end
				break;
			}
		}

	}

}


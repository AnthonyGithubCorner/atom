/*
 * iFileParser.hpp
 *
 *  Created on: Jul. 5, 2023
 *      Author: anthony
 */

#ifndef SRC_INTERACTIONFILE_IFILEPARSER_HPP_
#define SRC_INTERACTIONFILE_IFILEPARSER_HPP_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <vector>
#include <map>
#include "../common/gameObject.hpp"
#include "../common/GameTime.hpp"


struct repetablefunc
{
	// TODO eventually get to recycling func id's right now very lazy
	int funcID;
	int func_line;
	int number_to_repeat;
	int delay;
	std::string parameter;
	bool ready;
	int (*delayFunc)(int);
};

class iFileParser
{
public:
 	std::map<std::string, bool>       localStates;
	iFileParser(const char *iFile_path);
	void loadFile();
	bool isModified();
	void executeFile(gameObject* object);
	virtual ~iFileParser();
	Uint32 setLocalState(gameObject *object, std::string state);
	Uint32 setLocalState(std::string state);
	 bool getLocalAndGlobalState(gameObject *object, std::string state);
	 void clearLocalState(gameObject *object, std::string state);
	 void clearLocalState(std::string state);
	 bool active = 0;
	std::string path_file;
private:
	std::vector<std::string> _lines;
	std::map<std::string, int> funcLoader;
	std::vector<repetablefunc> funcsToExc;
	int func_exc_index = 0;
	int funcIDIndex = 0;
	time_t time_last_updated = 0;


};

#endif /* SRC_INTERACTIONFILE_IFILEPARSER_HPP_ */

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once

#include <map>
#include <string>
#include "../common/gameObject.hpp"

class actionLoader
{
public:
    static std::map<std::string, void(*)(gameObject*, std::string)> actions;
    static std::map<std::string, bool(*)(gameObject*, std::string)> conds;
    // resource storage
	static void registerFunc(std::string name, void(*func)(gameObject*, std::string));

	static void registerCond(std::string name, bool(*func)(gameObject*, std::string));

	static void registerAllActions();

private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    actionLoader() { }
    // loads and generates a shader from file

};

#define _CRT_SECURE_NO_WARNINGS  // required to use strcpy within VS2022.  Arduino doesn't have this issue

#include "ERacerCommandProcessor.h"
#include <stdio.h>
#include <string>

#include <sstream>
#include <vector>
#include <iterator>

template <typename Out>
void split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

ERacerCommandProcessor::ERacerCommandProcessor()
{
	
} // constructor

ERacerCommandDataType ERacerCommandProcessor::parseCommandLine(std::string input)
{

    std::vector<std::string> x = split(input, ':');

	struct ERacerCommandDataType result {};

    if (x.size() >= 1) {
        result.cmdName = x.at(0);
    }
    else {
        result.cmdName = "";
    }

    if (x.size() >= 2)
    {
        result.param1 = std::stoi(x.at(1));
    }
    else {
        result.param1 = 0;
    }

    if (x.size() >= 3)
    {
        result.param2 = std::stoi(x.at(2));
    }
    else {
        result.param2 = 0;
    }

	return result;
} // method::parseCommandLine


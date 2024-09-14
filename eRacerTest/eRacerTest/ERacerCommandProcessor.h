#include <string>

#ifndef ERacerCommandProcessor_h
#define ERacerCommandProcessor_h

struct ERacerCommandDataType {
	std::string cmdName;
	int param1;
	int param2;
};


class ERacerCommandProcessor
{
public:
	ERacerCommandProcessor();

	ERacerCommandDataType parseCommandLine(std::string input);

};


#endif
// eRacerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Arduino.h"
#include "ERacerControl.h"
#include "ERacerCommandProcessor.h"



int main()
{
    ERacerControl erc(_PIN_D6, _PIN_D7, _PIN_D8, _PIN_D5, _PIN_D4, _PIN_D3);
    ERacerCommandProcessor inputHandler;
    ERacerCommandDataType cmd;

    erc.begin();

    //char *cmdToProcess = new char[50]; // allow up to 50 characters to be entered.
    std::string cmdToProcess;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Ready for command: ";

        std::cin >> cmdToProcess;

        cmd = inputHandler.parseCommandLine(cmdToProcess);

        std::cout << "The command sent: " << cmdToProcess << '\n';

        erc.runCommand(cmd.cmdName, cmd.param1, cmd.param2);

    } // for loop

}

#include "Arduino.h"
#include "Arduino.h"
#include <Windows.h>
#include <iostream>
/******************************
 *  Testing library for Arduino.
 * These methods are strictly for setting up a testing platform for Arduino code
***************************** */

void pinMode(int pin, int mode)
{
    std::cout << "Pin Mode (" << pin << ") to " << mode << '\n';
} // Library

void digitalWrite(int pin, int value) 
{
    std::cout << "Digital Write (" << pin << ") to " << value << '\n';
}

void delay(int seconds)
{
    std::cout << "Sleeping for " << seconds << " seconds" << '\n';
    Sleep(seconds * 1000);
    std::cout << "Awake" << '\n';
}

void analogWrite(int pin, int value)
{
    std::cout << "Analog Write (" << pin << ") to " << value << '\n';
}


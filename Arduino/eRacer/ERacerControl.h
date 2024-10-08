#ifndef ERacerControl_h
#define ERacerControl_h

#include "Arduino.h"
#include <string>
#include <PCF8575.h>
#include <Wire.h>

/*
A 3 letter command, followed by values that are in the parameters.  examples include:
	FWD 3, 10	<- go forward at speed 3 for 10 seconds
	RVS 5, 2	<- go reverse at speed 5 for 2 seconds
	RGT 30		<- Turn right 30 degrees?
	LFT 80		<- Turn left 80 degress?
*/

class ERacerControl
{
  public:
    ERacerControl(int motorAThrottlePin, 
                  int motorAPin1,
                  int motorAPin2,
                  int motorBThrottlePin,
                  int motorBPin1,
                  int motorBPin2);
    void begin();
    void runCommand(std::string cmd, int param1, int param2);

  private:
    int _motorAThrottlePin;
    int _motorAPin1;
    int _motorAPin2;

    int _motorBThrottlePin;
    int _motorBPin1;
    int _motorBPin2;

		PCF8575 *expando;

    void engage(int speedA, int speedB);
		void moveForward(int speed, int seconds);
    void moveBackward(int speed, int seconds);
    void turnRight(int speed, int seconds);
    void turnLeft(int speed, int seconds);

		void setAllPinsTo(uint16_t setTo);
};

#endif
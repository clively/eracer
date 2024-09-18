#ifndef ERacerControl_h
#define ERacerControl_h

#include "Arduino.h"
#include <string>

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

    void engage(int speed);
    void moveForward(int speed, int seconds);
    void moveBackward(int speed, int seconds);
    void turnRight(int degrees);
    void turnLeft(int degrees);

    int calculateTimeFromDegress(int degrees, int speed);

};

#endif
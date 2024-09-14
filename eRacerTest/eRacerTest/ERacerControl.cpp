#include "Arduino.h"
#include "ERacerControl.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>


ERacerControl::ERacerControl(int motorAThrottlePin, 
                  int motorAPin1,
                  int motorAPin2,
                  int motorBThrottlePin,
                  int motorBPin1,
                  int motorBPin2)
{
  _motorAThrottlePin = motorAThrottlePin;
  _motorAPin1 = motorAPin1;
  _motorAPin2 = motorAPin2;

  _motorBThrottlePin = motorBThrottlePin;
  _motorBPin1 = motorBPin1;
  _motorBPin2 = motorBPin2;


} // constructor

void ERacerControl::begin()
{
  // establish pin communication
  pinMode(_motorAThrottlePin, OUTPUT);
  pinMode(_motorAPin1, OUTPUT);
  pinMode(_motorAPin2, OUTPUT);

  pinMode(_motorBThrottlePin, OUTPUT);
  pinMode(_motorBPin1, OUTPUT);
  pinMode(_motorBPin2, OUTPUT);

} // method::begin

void ERacerControl::runCommand(std::string cmd, int param1, int param2)
{
   // needs to parse the cmd string, determine which thing to do, and then to do it :)

	if (cmd == "FWD")
	{
		moveForward(param1, param2);
	}

	if (cmd == "RVS") 
	{
		moveBackward(param1, param2);
	}

	if (cmd == "RGT")
	{
		turnRight(param1);
	}

	if (cmd == "LFT")
	{
		turnLeft(param1);
	}


} // method::runCommand
/**************************
  private methods
**************************/
void ERacerControl::engage(int speed) 
{
  analogWrite(_motorAThrottlePin, speed);
  analogWrite(_motorBThrottlePin, speed);
}

void ERacerControl::moveForward(int speed, int seconds)
{

  digitalWrite(_motorAPin1, HIGH);
  digitalWrite(_motorAPin2, LOW);

  digitalWrite(_motorBPin1, HIGH);
  digitalWrite(_motorBPin2, LOW);

  engage(speed);

  delay(seconds);

  engage(0);
     
} // method::moveForward

void ERacerControl::moveBackward(int speed, int seconds)
{
  digitalWrite(_motorAPin1, LOW);
  digitalWrite(_motorAPin2, HIGH);

  digitalWrite(_motorBPin1, LOW);
  digitalWrite(_motorBPin2, HIGH);

  engage(speed);

  delay(seconds);

  engage(0);
} // method::moveBackward

void ERacerControl::turnRight(int degrees)
{
  digitalWrite(_motorAPin1, LOW);
  digitalWrite(_motorAPin2, HIGH);

  digitalWrite(_motorBPin1, HIGH);
  digitalWrite(_motorBPin2, LOW);

  engage(100);

  delay(calculateTimeFromDegress(degrees, 100)); // this will need to be tuned

  engage(0);
} // method::turnRight

void ERacerControl::turnLeft(int degrees)
{
  digitalWrite(_motorAPin1, HIGH);
  digitalWrite(_motorAPin2, LOW);

  digitalWrite(_motorBPin1, LOW);
  digitalWrite(_motorBPin2, HIGH);

  engage(100);

  delay(calculateTimeFromDegress(degrees, 100)); // this will need to be tuned

  engage(0);
} // method::turnLeft

int ERacerControl::calculateTimeFromDegress(int degrees, int speed)
{
  // hand wavy magic to be put in here.

  return 2;
}












#include "Arduino.h"
#include "ERacerControl.h"

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
    turnRight(param1, param2);
	}

	if (cmd == "LFT")
	{
    turnLeft(param1, param2);
	}


} // method::runCommand
/**************************
  private methods
**************************/
void ERacerControl::engage(int speedA, int speedB) 
{
  Serial.print("ENG: [");
  Serial.print(speedA);
  Serial.print(",");
  Serial.print(speedB);
  Serial.print("]: ");
  Serial.print(_motorAThrottlePin);
  Serial.print(":");
  Serial.println(_motorBThrottlePin);

  analogWrite(_motorAThrottlePin, speedA);
  analogWrite(_motorBThrottlePin, speedB);
}

void ERacerControl::moveForward(int speed, int seconds)
{
  Serial.print("DW: ");
  Serial.print(_motorAPin1);
  Serial.print(":");
  Serial.println(_motorAPin2);

  digitalWrite(_motorAPin1, HIGH);
  digitalWrite(_motorAPin2, LOW);

  Serial.print("DWB: ");
  Serial.print(_motorBPin1);
  Serial.print(":");
  Serial.println(_motorBPin2);

  digitalWrite(_motorBPin1, HIGH);
  digitalWrite(_motorBPin2, LOW);

  Serial.print("moving forward: ");
  Serial.print(speed);
  Serial.print(":");
  Serial.println(seconds);

  engage(speed, speed);

  delay(seconds * 1000); 

  Serial.println("Full stop");

  engage(0, 0);

     
} // method::moveForward

void ERacerControl::moveBackward(int speed, int seconds)
{
  digitalWrite(_motorAPin1, LOW);
  digitalWrite(_motorAPin2, HIGH);

  digitalWrite(_motorBPin1, LOW);
  digitalWrite(_motorBPin2, HIGH);

  engage(speed, speed);

  delay(seconds * 1000); 

  engage(0, 0);
} // method::moveBackward

void ERacerControl::turnRight(int speed, int seconds)
{
  digitalWrite(_motorAPin1, LOW);
  digitalWrite(_motorAPin2, HIGH);

  digitalWrite(_motorBPin1, HIGH);
  digitalWrite(_motorBPin2, LOW);

  engage(speed, speed);

  delay(seconds * 1000); 

  engage(0, 0);
} // method::turnRight

void ERacerControl::turnLeft(int speed, int seconds)
{
  digitalWrite(_motorAPin1, HIGH);
  digitalWrite(_motorAPin2, LOW);

  digitalWrite(_motorBPin1, LOW);
  digitalWrite(_motorBPin2, HIGH);

  engage(speed, speed);
	
  delay(seconds * 1000); 

  engage(0, 0);
} // method::turnLeft














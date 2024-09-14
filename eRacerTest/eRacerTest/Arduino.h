#ifndef Arduino_h
#define Arduino_h


#define OUTPUT 0x03

#define HIGH 0x1
#define LOW 0x0

// I'm using _PIN_ before each of the pin constants because of a collision in the winnt.h file on pins D8 through D12
// It's something that is easy to do a find/replace on before compiling for Arduino

#define _PIN_D1 0x1
#define _PIN_D2 0x2
#define _PIN_D3 0x3
#define _PIN_D4 0x4
#define _PIN_D5 0x5
#define _PIN_D6 0x6
#define _PIN_D7 0x7

#define _PIN_D8 0x8
#define _PIN_D9 0x9
#define _PIN_D10 0x10
#define _PIN_D11 0x11
#define _PIN_D12 0x12


void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
void analogWrite(int pin, int value);
void delay(int seconds);

#endif
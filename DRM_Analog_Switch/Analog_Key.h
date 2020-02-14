/***************************************************************************************************************************/
/*

  Draft 2.0 - 8th October 2019. David Mottram

  A simple library that provides the ESP8266 with a number of push button switches using the A/D input.
  The Analog range of the ESP8266 is 0-1V with a bit range of 0-1023 (10 bit).
  The push buttons are all commoned on one side with a 100K to ground, this is then connected to the ESP8266 A/D input.
  A simple resistor divider network is made with several resistors (1K) and a single resistor at the top (22K) so that the
  junction between the 1K resistor network and the 22K is at around 0.822V.
  Each switch then taps a resistor junction and when pressed presents that voltage to the A/D,
  the range being 0V (no switch pressed) to 0.822V with the top switch pressed.
  These voltages are all very approximate and the software allows for this.

  GND - 1K  - 1K  - 1K  - 1K  - 1K  - 1K  - 1K  - 1K  - 22K - 3V3
      SW1   SW2   SW3   SW4   Sw5   SW6   SW7   SW8
      0.1V  0.2V  0.3V  0.4V  0.5V  0.6V  0.7V  0.8V
      - - - - - - - - - - - - - - - - - - - - - - -
      |
      | - - ESP8266 A/D input
      |
      100K
      |
      GND

  With the above schematic there are 8 push buttons and each tap on the resistor divider network is approximately 0.1V (ish!)

*/
/***************************************************************************************************************************/

// check that the library has not yet been called
#ifndef Analog_Switch
#define Analog_Switch

// check of legacy IDE
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


/***************************************************************************************************************************/
/*
  class for push buttons
*/
/***************************************************************************************************************************/
class Analog_Push
{

  public:

    // Add a constructor
    Analog_Push(int Number_Buttons, int Top_Switch, int Debounce_Period);

    // function
    int Switch_Status();  // switch status, pressed?
    int Switch_Value(int Update_Delay, int Update_Report);  // switch A/D value report
    int Switch_Event(); // switch event, cleared by Switch_Reset
    void Switch_Reset(); // clears switch event register

  private:

    int _Number_Buttons = 0;
    int _Top_Switch = 0;
    uint8_t  _Switch_Now = 0;
    uint8_t  _Switch_Was = 0;
    uint8_t  _Switch_Memory = 0;

    // switch scan
    long _Switch_Scan = 0;
    #define _Switch_Scan_Period 10

    // switch debounce
    long _Debounce = 0;
    int _Debounce_Period;

    // switch report
    long _Switch_Update_Timer = 0;
    int _Switch_Update_Period;

};
#endif

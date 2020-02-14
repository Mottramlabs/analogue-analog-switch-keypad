#include "Arduino.h"
#include "Analog_Key.h"


// constructor
// number of switches, the A/D value for the top switch in the array and the switch debounce period
Analog_Push::Analog_Push(int Number_Buttons, int Top_Switch, int Debounce_Period) {

  _Number_Buttons = Number_Buttons;

  _Top_Switch = Top_Switch;
  _Debounce_Period = Debounce_Period;

} // end of function


// report the A/D input from the switch array, then wait a period.
// Update_Delay is the dealy period in mS (0-1000)
// Update_Report if not 0 will report the A/D value via the serial port
int Analog_Push::Switch_Value(int Update_Delay, int Update_Report) {

  // range checks
  if (Update_Delay > 1000 || Update_Delay < 0) {
    Update_Delay = 1000;
  } // end range check

  _Switch_Update_Period = Update_Delay;
  _Switch_Update_Timer = millis();

  // read A/D
  int Switch_Value = analogRead(A0);

  // report?
  if (Update_Report != 0) {
    Serial.print("Switch Input A/D Value: "); Serial.println(Switch_Value);
  } // end of report

  // wait here until timer completed
  while (millis() - _Switch_Update_Timer < _Switch_Update_Period) {
    yield();
  }

  return Switch_Value;

} // end of function


// read switch input status (read time) with a A/D scan delay and a debounce delay
int Analog_Push::Switch_Status(void) {

  // switch scan period timer
  if (millis() - _Switch_Scan > _Switch_Scan_Period) {
    _Switch_Scan = millis();

    // read A/D and store current switch value
    _Switch_Now = analogRead(A0) / (_Top_Switch / _Number_Buttons);

    // run switch debounce timer if switch status has changed
    if (_Switch_Now != _Switch_Was) {

      // switch value has changed, run the debounce timer
      if (millis() - _Debounce > _Debounce_Period) {
        // debounce period completed

        // if a new switch is pressed
        if (_Switch_Now > 0 && _Switch_Was == 0) {

          // has the last event been cleared
          if (_Switch_Memory == 0) {
            _Switch_Memory = _Switch_Now;
          } // end

        } // end switch test

        _Switch_Was = _Switch_Now;

      } // end of timer

    } // end of switch test

    // switch is the same so reset debounce timer
    else {
      _Debounce = millis();
    }

  } // end of A/D scan period

  return _Switch_Was;

} // end of function


// report switch event, 0 = no switch pressed event
int Analog_Push::Switch_Event() {

  Switch_Status();
  return _Switch_Memory;

} // end of function


// clear switch memory
void Analog_Push::Switch_Reset() {

  _Switch_Memory = 0;

} // end of function

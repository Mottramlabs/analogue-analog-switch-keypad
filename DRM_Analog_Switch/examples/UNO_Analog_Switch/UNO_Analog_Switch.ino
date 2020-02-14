/*
      Analog switch demo - UNO version
      Input from switch panel is on A0 (High output from switch panel, VCC to switch is 5V
      13th February 2020
*/

#define Number_Number_Buttons 8
#define Top_Switch_Value 855
#define Debounce 50

#include <Analog_Key.h>
Analog_Push My_Buttons(Number_Number_Buttons, Top_Switch_Value, Debounce); // make an instance of the library. Number of switches, top switch value (A/D count), debounce delay (mS)

void setup(void) {

  Serial.begin(115200);
  Serial.println(""); Serial.println("Hello to analog switch test");

} // End of setup

void loop() {

  // get the push buttons current status, if pressed will report the switch number else 0 for no switch
  // Serial.println(My_Buttons.Switch_Status()); // report switch status, return switch number if pressed and 0 if none pressed

  // test the switch memory, 0 = no switch pressed event. Reports the switch event number (switch value) and is cleared by Switch_Reset()
  int Button = My_Buttons.Switch_Event();
  if (Button != 0) {
    My_Buttons.Switch_Reset(); // clear memory flag
    Serial.print("Switch Pressed: "); Serial.println(Button);
  }

  // real time report of the A/D values. Switch_Value(mS delay between reads, 1=print report)
  //My_Buttons.Switch_Value(100, 1) ;

} // end of loop

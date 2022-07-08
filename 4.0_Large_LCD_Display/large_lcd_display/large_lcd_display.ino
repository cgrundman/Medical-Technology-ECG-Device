/*
  Large LCD Display

  Contains all final commands to operate LCD Screen
  
  Arduino code for the LCD touchscreen. This code displays 
  the elapsed time being counted by the arduino. Code 
  requires only the Aruino MEGA and TFT 3.5" LCD screen.
*/

// Include Needed Libraries
#include "display.h"

// Initialize Constants
long elap_time = 0;

void setup() {

  // Display Initial String
  DisplaySetup();
  show_string("Current time:", 230, 70, 2, BLACK, LIGHTGREY, 1);
  Serial.begin(9600);
  
}

void loop() {

  // Update the elapsed time
  elap_time = millis();
  Serial.println(elap_time);
  show_num(elap_time, 300, 160, 4, BLACK,  LIGHTGREY, 1);
  delay(100);
  
}

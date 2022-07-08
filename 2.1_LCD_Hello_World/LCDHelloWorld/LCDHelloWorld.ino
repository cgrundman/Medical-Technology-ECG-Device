/*
  LCD Hello World

  Displays "Hello World" and a counter on a 16x2 LCD screen

  Arduino Code for displaying to a simple 16x2 LCD display.
  The code is used as a base for future code using this 
  display.
*/

// Include Needed Libraries
#include <LiquidCrystal.h>

// Initialize Constants
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6; // Pins for LCD

// Input pins for LCD use
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  // Set up the LCD's size:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
}

void loop() {
  
  // Set cursor to row 2
  lcd.setCursor(0, 1);
  
  // Print the number of seconds since reset:
  lcd.print(millis() / 1000);
  
}

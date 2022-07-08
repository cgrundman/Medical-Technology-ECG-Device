/*
  Button Interface

  Displays text in responce to button presses

  Arduino Code for using two buttons to display to an LCD
  Interface. Button 1 is programmed as a simple press-
  button. Button 2 is programmed as a press-on/press-off 
  button.
*/

// Include Needed Libraries
#include <LiquidCrystal.h>

// Initialize Constants
byte lastButtonState1 = LOW;
byte lastButtonState2 = LOW;
byte displayState = LOW;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6; // pins for lcd display
const int buttonPin1 = 22;     // the number of the pushbutton1 pin
const int buttonPin2 = 26;     // the number of the pushbotton2 pin

// Input pins for LCD use
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  // Initialize LCD with "Hello World" message
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  delay(1000);

  // Display "Initializing..." message
  lcd.setCursor(0,1);
  lcd.println("Initializing... ");
  delay(1000);

  // Clear screen
  lcd.clear();

  // Print initial button states
  lcd.setCursor(0,0);
  lcd.print("B1: unpressed");
  lcd.setCursor(0,1);
  lcd.print("B2: inactive");
  
  // Initialize the pushbutton pins as an input
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  
}

void loop() {

  // Read current button states
  byte buttonState1 = digitalRead(buttonPin1);
  byte buttonState2 = digitalRead(buttonPin2);

  // Display for button one (press-button)
  lcd.setCursor(0,0);
  if (buttonState1 == LOW) {
    lcd.print("B1: unpressed");
    }
  else if (buttonState1 == HIGH) {
    lcd.print("B1: pressed  ");
    }

  // Display for button two (press-on/press-off)
  lcd.setCursor(0,1);
  if (lastButtonState2 == LOW && buttonState2 == HIGH)
  {
    if (displayState == LOW) {
      displayState = HIGH;
      lcd.print("B2: active  ");
      }
    else {
      displayState = LOW;
      lcd.print("B2: inactive");
      }
  }
  lastButtonState2 = buttonState2;

  // Pause for 50 ms
  delay(50);
      
}

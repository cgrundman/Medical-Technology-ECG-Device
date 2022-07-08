/*
  Ring Filter LCD

  Displays ring filtered temperature data to 16x2 LCD Screen

  Arduino Code for displaying temperature to a simple 16x2 
  LCD display. This temperature data has been filtered by 
  the ring filter.
*/

// Include Needed Libraries
#include <LiquidCrystal.h>

// Initialize Global Variables
#define VCC 5
#define REF 4.83 // we use the internal reference voltage of 1.1V
#define RESISTOR 220 // the resistor in series with the pt100 was chosen to be 220 ohms. This to make sure voltage Umess is between 0 and reference voltage.

// Initialize Constants
const int analogInPin = A0; // Input pin for temperature
double Temp = 0.0; // Instant temperature
double tempAvgRing = 0.0; // Average temperature
double ges = 0.0; // Temporary sum of temperatures
int sensorValue = 0; // Array for average temperature calculation, change the number here for more or less values
double Umess = 0.0;             
double Rt = 0.0; // Resistance of pt100
double ratio = REF / 1024.0; // Ratio to convert the sensorvalue to a voltage value
double digitalStorageRing[100];
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6; // Pins for LCD

// Input pins for LCD use
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  // Set the bitrate for serial communication
  Serial.begin(9600);

  // Set up the LCD's size:
  lcd.begin(16, 2);

  // Clear Screen
  lcd.clear();

  // Set built in LED to output
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {

  // Read the PT100 sensor value, bit to temp conversion
  sensorValue = analogRead(analogInPin); // read the value from the analog input pin
  Umess = sensorValue * ratio; // Calculate the voltage drop between the pins of the pt100
  Rt = (RESISTOR * Umess) / (5 - Umess); // RESISTOR is the value of the resistor in ohms, change this if you change the resistor
  Temp = (Rt - 100.0) * 2.85; // instant readout of temperature

  // Store temperature values
  for (int i = 0; i < 100; i++) { //write new entry into storage ring; and move the indexes
    if (i == 99) {
      digitalStorageRing[99] = Temp;
    }
    else {
      digitalStorageRing[i] = digitalStorageRing[i + 1];
    }
  }

  // Sum up all temperature values
  for (int i = 0; i < 100; i++) {
    ges += digitalStorageRing[i];
  }

  // Calculate the average
  tempAvgRing = ges / 100;
  ges = 0.0; // reset the sum to 0 for the next cycle

  // Thresholds for onboard LED
  if (tempAvgRing > 20.0) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (tempAvgRing < 20.0) {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Print to LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(tempAvgRing);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("save quit");

  // Pause for 200 ms
  delay(200);
  
}

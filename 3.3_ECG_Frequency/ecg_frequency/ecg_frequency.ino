/*
  ECG Frequency

  Plot the BPM on the LCD

  Arduino Code for displaying collected ECG signal to
  an LCD 16x2 screen. This code uses  a simple threshold 
  to trigger heartbeat. The frequency is displayed in 
  beats per minute. This code requires a simulated
  signal, without noise.
*/

// Include Needed Libraries
#include <LiquidCrystal.h>

// Initialize Constants
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6; // pins for lcd display
int threshold = 550; // Set threshold
int LED = 13; // Built-in LED pin
int ecg = A3; // Signal input pin
int previousSensorValue = 0;
int sensorValue;
unsigned long current_beat;
unsigned long bpm; // Frequency variable
float previous_beat = 0;

// Input pins for LCD use
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  // Initialize Serial communication rate
  Serial.begin(9600);

  // Set pin modes
  pinMode(LED, OUTPUT);
  pinMode(ecg, INPUT);

  // Write initial time
  previous_beat = millis();
  
  // Initialize LCD
  lcd.begin(16, 1);
  lcd.print("Booting up...");
  delay(1000);
  lcd.clear();
  
}

void loop() {
  
  // Reset previous sensor value, read signal
  previousSensorValue = sensorValue;
  sensorValue = analogRead(ecg);
  float heartbeat = sensorValue; 

  // If threshold larger than 600 then pulse the led on the arduino
  if (heartbeat > threshold && previousSensorValue < threshold) {
    digitalWrite(LED, HIGH); // turn on LED

    // Calculate Frequency
    current_beat = millis();
    bpm = 60*(1/(current_beat - previous_beat))*1000;
    Serial.println(bpm);
    previous_beat = current_beat;

    // Print to LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.setCursor(0, 1);
    lcd.print(bpm);

  } else {
    digitalWrite(LED, LOW); // Turn off LED
  } 
  
}

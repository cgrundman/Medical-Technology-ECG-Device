/*
  ECG Large LCD Interface

  Contains all final commands for ECG device
  
  Arduino code for the LCD touchscreen, collection of 
  ECG data from the analog circuit, and outputs buzzer 
  sound. This code displays the heartbeat calculated by 
  threshold from the ECG. Code requires the Aruino 
  MEGA, TFT 3.5" LCD screen, analog circuit, buzzer 
  actuator, sensor, and circuitboard connecting all of 
  these components.
*/

// Include Relevent Libraries
#include "display.h"
#include "buzzer.h"

// Initialize Constants
const int ecg = A9; // Input pin for the ECG signal from the analog device
int previousSensorValue = 0; // Stores previous sensor value
int LED = 13;
int sensorValue = 0;
int threshold = 500;
long time_curr = 0;
float previous_beat = 0;
unsigned long current_beat;
unsigned long bpm;
unsigned long previous_bpm;

void setup() {

  // Initialize all input and output signals
  Serial.begin(9600);
  pinMode(22, OUTPUT);
  pinMode(ecg, INPUT);
  digitalWrite(22,HIGH);
  previous_beat = millis();

  // Initialize Screen
  DisplaySetup();
  show_string("Heartbeat (bpm):", 180, 10, 3, BLACK, LIGHTGREY, 1);
  
}

void loop() {

  // Read the signal value from the sensor, storing old value
  previous_bpm = bpm;
  previousSensorValue = sensorValue;
  sensorValue = analogRead(ecg);
  Serial.println(sensorValue);
  float heartbeat = sensorValue;

  // Trigger a current_beat when threshold is crossed
  if (heartbeat < threshold && previousSensorValue > threshold) {
    digitalWrite(LED, HIGH);
    current_beat = millis();
    // Time duration in [bpm] between heart beats
    bpm = 60*(1/(current_beat - previous_beat))*1000;
    previous_beat = current_beat;
  }

  // Display when heartrate is too high
  if (bpm > 150 && previous_bpm != bpm) {
    show_bpm(bpm, 180, 80, 8, RED, LIGHTGREY, 1);
    show_high_bpm("HIGH HR!", 15, 200, 3, RED, LIGHTGREY, 1);
    show_low_bpm("", 15, 275, 3, BLUE, LIGHTGREY, 1);
    pulse();
  }

  // Display if heartrate is too low
  else if (bpm < 30 && previous_bpm != bpm) {
    show_bpm(bpm, 180, 80, 8, BLUE, LIGHTGREY, 1);
    show_high_bpm("", 15, 200, 3, RED, LIGHTGREY, 1);
    show_low_bpm("LOW HR!", 15, 275, 3, BLUE, LIGHTGREY, 1);
    pulse();
  }
  
  // Only update display if heartbeat changes 
  else if (bpm < 150 && previous_bpm != bpm) {
    show_bpm(bpm, 180, 80, 8, BLACK, LIGHTGREY, 1);
    show_high_bpm("", 15, 200, 3, RED, LIGHTGREY, 1);
    show_low_bpm("", 15, 275, 3, BLUE, LIGHTGREY, 1);
    pulse();
  }
  
}

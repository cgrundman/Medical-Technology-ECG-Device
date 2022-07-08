/*
  Moving Average

  Displays filtered and unfiltered temperature data from PT100

  Temperature sensing can be conducted with realitvely simple
  sensors. This code was written for a PT100 sensor, so named
  because of having 100ohm resistance at 0C. The moving
  average filter averages the most recent values (the amount
  set by WINDOW_SIZE) and finds the average.
*/

// Include needed libraries
#include <movingAvg.h>

// Define Global Variables
#define VCC 5.00
#define T_OFF 10.0
#define WINDOW_SIZE 5

// Define variables
const int analogInPin = A0; // Input pin for PT100
double temp = 0.0; // Base temperature
double unfilteredTemp = 0.0; // Unfiltered temperature
double filteredTemp = 0.0; // Filtered temperature
double sensorValue = 0; // Sensor value
double UMess = 0.0; // Voltage drop across PT100
double Rt = 0.0; // Resistance of PT100
double ratio = VCC / 1024.0; // Conversion from 1024 to 5V
int readings[WINDOW_SIZE]; // Group of readings for average

movingAvg avgTemp(10);

void setup() {

  // Initialize serial to baud rate of 9600
  Serial.begin(9600);

  // Initialize avgTemp
  avgTemp.begin();

  // Labels for Unfiltered and Filtered Temperature
  Serial.println("Unfiltered_Temp,Moving_Avg_Temp");
}

void loop() {

  // Read the PT100 sensor value
  int sensorValue = analogRead(analogInPin);

  // Moving Average
  int sensorMovingAvg = avgTemp.reading(sensorValue);

  // Bit to Temperature Conversion for Unfiltered Temperature
  UMess = sensorValue * ratio;
  Rt = (220 * UMess) / (VCC - UMess);
  temp = (Rt - 100) * 2.52;
  unfilteredTemp = temp - T_OFF;

  // Bit to Temperature Conversion for Moving Avg
  UMess = sensorMovingAvg * ratio;
  Rt = (220 * UMess) / (VCC - UMess);
  temp = (Rt - 100) * 2.52;
  filteredTemp = temp - T_OFF;

  // Plot both values to Serial plotter  
  Serial.print(unfilteredTemp);
  Serial.print("\t");
  Serial.println(filteredTemp);
  
}

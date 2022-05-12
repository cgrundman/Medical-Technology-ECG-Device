// Moving Average for PT100 Temperature Sensor

//Include needed libraries
#include <movingAvg.h>

//Define constants
#define VCC 5.00
#define T_OFF 10.0
#define WindowSize 5

//Define variables
const int analogInPin = A0;
double Temp = 0.0;
double unfilteredTemp = 0.0;
double filteredTemp = 0.0;
double sensorValue = 0;
double Umess = 0.0;
double Rt = 0.0;
double ratio = VCC / 1024.0;
int index = 0;
int sum = 0;
int readings[WindowSize];
double mov_average = 0;
double fix_average = 0;
int filter_length = 100;
int index_av = 0;
int sum_av = 0;
movingAvg avgTemp(10);

void setup() {
  Serial.begin(9600);
  avgTemp.begin();
  Serial.println("Sensor_Value,Sensor_Moving_Avg");
}

void loop() {

  // Read the PT100 sensor value
  int sensorValue = analogRead(analogInPin);

  // Moving Average
  int sensorMovingAvg = avgTemp.reading(sensorValue);

  // Bit to Temperature Conversion for Sensor
  Umess = sensorValue * ratio;
  Rt = (220 * Umess) / (VCC - Umess);
  Temp = (Rt - 100) * 2.52;
  unfilteredTemp = Temp - T_OFF;

  Serial.print(unfilteredTemp);
  Serial.print("\t");

  // Bit to Temperature Conversion for Moving Avg
  Umess = sensorMovingAvg * ratio;
  Rt = (220 * Umess) / (VCC - Umess);
  Temp = (Rt - 100) * 2.52;
  filteredTemp = Temp - T_OFF;

  Serial.println(filteredTemp);
}

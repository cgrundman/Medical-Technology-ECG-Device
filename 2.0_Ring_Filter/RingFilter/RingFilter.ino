/* 
  Ring Filter

  Displays filtered and unfiltered temperature data from PT100
  
  Arduino Code for Temperature Readout of PT100 Sensor
  This code was adapted from professor Urban's code in Lernraum
  ring filtering is done here
*/

// Define Global Variables
#define VCC 5
#define REF 4.83 // Reference voltage
#define RESISTOR 220 // Resistor value of resistor set in series with PT100

// Define Constants
const int analogInPin = A0; // input pin for temperature
double Temp = 0.0; // Instant temperature
double tempAvgRing = 0.0; // Average temperature
double digitalStorageRing[100]; // Array for average temperature calculation, change the number here for more or less values
double ges = 0.0; // Temporary sum of temperatures
int sensorValue = 0;
double Umess = 0.0; // Voltage drop between pt100
double Rt = 0.0; // Resistance of pt100
float ratio = REF / 1024.0; // ratio to convert the sensorvalue to a voltage value

void setup() {

  // Set the bitrate for serial communication
  Serial.begin(9600);

  // Plot titles
  Serial.println("Temp_Value,Temp_Value_Ring_Avg");
  
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
  
  // Final Solution
  Serial.print(Temp);
  Serial.print("\t");
  Serial.println(tempAvgRing);
  
}

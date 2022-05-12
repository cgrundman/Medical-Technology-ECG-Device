//// Arduino Code for Temperature Readout of PT100 Sensor
//// This code was adapted from professor Urban's code in Lernraum
//// ring filtering is done here

// define the input voltage and the reference voltage N.B. THE TWO VOLTAGES ARE NOT GENERALLY THE SAME
#define VCC 7
#define T_OFF 10.0
#define REF 1.1 // we use the internal reference voltage of 1.1V
#define RESISTOR 674 // the resistor in series with the pt100 was chosen to be 674 ohms. This to make sure voltage Umess is between 0 and reference voltage.

const int analogInPin = A0;     // input pin for temperature
double Temp = 0.0;              // Instant temperature
double Tempavg_ring = 0.0;      // Average temperature
double digitalstoragering[100]; // Array for average temperature calculation, change the number here for more or less values
double ges = 0.0;               // temporary sum of temperatures
int sensorValue = 0;
double Umess = 0.0;             // Voltage drop between pt100
double Rt = 0.0; // Resistance of pt100
double ratio = REF / 1024.0; // ratio to convert the sensorvalue to a voltage value


void setup() {
  Serial.begin(9600); // choose the bitrate for serial communication
}

void loop() {
  analogReference(INTERNAL); // choose the internal reference voltage of 1.1V

  sensorValue = analogRead(analogInPin); // read the value from the analog input pin

  //Serial.print("Unitvalue:");
  //Serial.println(sensorValue);
  //Serial.print("avg Value:");
  //Serial.print("sensorValue: ");
  //Serial.println(sensorValue);

  Umess = sensorValue * ratio; // Calculate the voltage drop between the pins of the pt100
  //Serial.print("U_mess:");
  //Serial.println(Umess);


  Rt = (RESISTOR * Umess) / (VCC - Umess); // RESISTOR is the value of the resistor in ohms, change this if you change the resistor
  //Serial.print("R_T:");
  //Serial.println(Rt);


  Temp = (Rt - 100.0) * 2.85; // instant readout of temperature
  //Tempavg_library = (Rtavg-100.0)*1.85; //slope differs from pt100 to pt 100
  //Temp = Temp-T_OFF;


  //moving average by ring:
  for (int i = 0; i < 100; i++) { //write new entry into storage ring; and move the indexes
    if (i == 99) {
      digitalstoragering[99] = Temp;
    }

    else {

      digitalstoragering[i] = digitalstoragering[i + 1];

    }
  }


  //sum up all the values
  for (int i = 0; i < 100; i++) {

    ges += digitalstoragering[i];

  }
  //calculate the average
  Tempavg_ring = ges / 100;
  ges = 0.0; // reset the sum to 0 for the next cycle

  //Serial.print("TempValue:");
  //Serial.println(Tempavg_library);
  Serial.println(Tempavg_ring);
  //Serial.println();
}

/*
  Dual Plot

  Plots two plots to the serial plotter.

  Many data collection and display systems, with for example filtered
  data, require displaying multiple data sources. This code is used
  as a baseline for later coding milestones.
*/

void setup() {

  // Initialize serial connection, set baud rate to 9600
  Serial.begin(9600);

  // Label the two plotted data series
  Serial.println("data1,data2");
  
}
void loop() {

  // Initialize and populate both data series
  int data1, data2;
  data1 = random(1000,6000); // random number between 1000 and 6000
  data2 = random(0,3000); // random number between 0 and 3000

  // Printing data to the serial port
  Serial.print(data1);
  Serial.print("\t");
  Serial.println(data2);

  // Pause for 100 ms
  delay(100);
  
}

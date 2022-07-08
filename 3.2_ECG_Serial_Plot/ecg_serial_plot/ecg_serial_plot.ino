/*
  ECG Serial Plot

  Plot the EC signal on the serial monitor

  Arduino Code for displaying collected ECG signal to
  the Serial output. This code uses  a simple threshold 
  to trigger heartbeat. This code requires a simulated
  signal, without noise.
*/

// Initialize Constants
int threshold = 550; // threshold value, tune for performance
int LED = 13; // Builtin LED pin 
int ecg = A3; // Input pin for ECG Signal
int sensorValue; // Current sensor value
unsigned long start; // Start in millis()
unsigned long finish; // Finish in millis()

void setup() {

  // Initialize Serial communication rate
  Serial.begin(9600);

  // Set pin modes for LED and Analog signal
  pinMode(LED, OUTPUT);
  pinMode(ecg, INPUT);
  
}

void loop() {
  
  // Plot ECG Signal to Serial
  sensorValue = analogRead(ecg);
  float heartbeat = sensorValue;
  Serial.print(heartbeat);  

  // If heartbeat larger than threshold, initiate beat, record time
  if (heartbeat > threshold) {
    digitalWrite(LED, HIGH); // Turn LED on
    start = millis();
    Serial.println(start);

  // When below threshold, turn light off, record time
  } else {
    digitalWrite(LED, LOW); // Turn LED off
    finish = millis(); // Finish
    Serial.println(finish);
  }
}

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  These Arduinos have an on-board LED that it is attached to digital 
  pin 13. LED_BUILTIN is set to the correct LED pin independent of 
  pin number. This code was used to test connectivity of the board.
*/

void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  
}

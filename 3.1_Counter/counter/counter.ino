/*
  Counter

  Counts Elapsed Time

  Arduino Code counting time durations using the millis()
  function. Should display a consistent set time interval.
*/

// Initialize Constants
unsigned long currentMillis; // current millis marker
float previousMillis = 0; // previous millis marker
float duration; // duration variable
const unsigned long period = 1000;  //the value is a number of milliseconds

void setup()
{

  // Initialize Serial connection rate
  Serial.begin(9600);

  // Initiallize state time
  previousMillis = millis();
  
}

void loop()
{

  // Acquire current time and calculate duration
  currentMillis = millis();  //get the current "time"
  duration = currentMillis - previousMillis; // caluculate duration

  // Display elapsed time
  Serial.println(duration);

  // Update previous time
  previousMillis = currentMillis;

  // Pause for set time period
  delay(period);
  
}

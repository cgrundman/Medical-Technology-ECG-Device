/*
  Library File for Buzzer

  Contains custom commands to implement the buzzer.
*/

// Initialize Constants
int buzzer = 51; //the pin of the active buzzer
int power = 53; // pin of 5v power supply
int sound_len = 37;

void pulse()
{

  // Set output pins
  pinMode(buzzer,OUTPUT); // initialize the buzzer pin as an output
  pinMode(power,OUTPUT); // initialize the power pin as an output
  digitalWrite(power,HIGH);
  
  // High Pitch Sound for 74 ms
  unsigned char counter;
  for(counter = 0; counter < sound_len; counter++)
  {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
  }

} 

/*
  Buzzer

  Operates Buzzer to make an alarm sound
  
  Arduino code for the buzzer. Buzzer works with a on/off
  frequency. This code uses 2ms frequency to make the sound.
*/

// Initialize Constants
int buzzer = 12; //the pin of the active buzzer
int sound_len = 74; // duration of 

void setup() {

  // Define output pin
  pinMode(buzzer,OUTPUT); // Initialize the buzzer pin as an output

}

void loop()
{
  
  // High Pitch Sound for 74 ms and pause for delay time
  unsigned char counter;
  for(counter = 0; counter < sound_len; counter++)
  {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
  }
  delay(1500);

} 

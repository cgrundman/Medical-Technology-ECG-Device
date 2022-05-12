#define Vcc 4.8
#include <LiquidCrystal.h>
double digitalstoragering[100];
LiquidCrystal lcd(11, 12, 2, 3, 4, 5);
const int analogInPin = A0;
int sensorValue = 0;
double Umess = 0.0;
double Rt = 0.0;
double ratio = Vcc / 1024.0;
unsigned long timea;
const int analogPin = A2;
int val;

double ges = 0.0;
double avgtemp;
double Temp = 0.0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //meassuring Temperature:
  sensorValue = analogRead(analogInPin);
  //Serial.print("Unitvalue:");
  //Serial.println(sensorValue);
  Umess = sensorValue * ratio;
  //Serial.println(Umess);
  Rt = (330 * Umess) / (Vcc - Umess);

  //Serial.print("Time: ");
  //timea = micros();
  //Serial.println(timea);

  Temp = (Rt - 100.0) * 2.2;
  //Temp=Temp-5.0;
  //Serial.print("TempValue:");
  //Serial.println(Temp);



  //moving average:
  for (int i = 0; i < 100; i++) { //write new entry into storage ring; and move the indexes
    if (i == 99) {
      digitalstoragering[99] = Temp;
    }

    else {

      digitalstoragering[i] = digitalstoragering[i + 1];

    }
  }



  for (int i = 0; i < 100; i++) { //sum up all the values

    ges += digitalstoragering[i];

  }

  avgtemp = ges / 100; //calculate the average
  ges = 0.0;

  //Serial.print("TempValue:");
  //Serial.println(Temp);
  Serial.print("Averagetemp:");
  Serial.println(avgtemp);
  if (avgtemp > 26.0) {
    digitalWrite(7, HIGH);
  }

  if (avgtemp < 23.0) {
    digitalWrite(7, LOW);
  }

  //lcd.clear();
  //lcd.print("Temp:");

  //lcd.print(Temp);
  //lcd.print("C");
  //lcd.setCursor(0, 1);
  //lcd.print("save quit");
}

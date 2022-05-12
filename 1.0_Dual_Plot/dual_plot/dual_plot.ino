void setup() {
  Serial.begin(9600);
}
void loop() {
  int value1, value2;
  value1 = random(1000,6000);
  Serial.print(value1);
  Serial.print(",");
  value2 = random(0,3000);
  Serial.println(value2);
  delay(100);
}

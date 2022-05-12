void setup() {
  Serial.begin(9600);
}

void loop() {
  ADMUX |= B01000000;
  ADMUX |= _BV(MUX0);
  ADCSRA |= _BV(ADPS2) | _BV(ADSP1) | _BV(ADSP0);
  ADCSRA |= _BV(ADEN) | _BV(ADSC);

  while (bit_is_set(ADCSRA, ADSC));
  int value = ADCL | (ADCH << 8);
//  value = value * 5.7;

  Serial.println(value);
//  Serial.println();
}

int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  delay(1000); // Display value every 1 second.
  Serial.print("Current temperature is: ");  
  Serial.print(readVcc()*sensorValue*100.0/1024); // Analog resolution is 1024.
  Serial.print(" Degrees celsius"); 
  Serial.println("");
}
long readVcc() { // Arduino has integrated voltage monitoring. For more accurate temp
  long result;   // readings real voltage is used instead of 5.0V.
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result;
  result = result / 1000; // Back-calculate AVcc in mV
  return result;
}


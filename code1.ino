int sensorPin = A0;
int min;
int max;

void setup() {
  
  Serial.begin(9600);
}

void loop() {

  // read and print values
  int sensorVal = analogRead(sensorPin);
  Serial.println(sensorVal);
  delay(50);

}

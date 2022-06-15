int sensorPin = A1;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

}

void loop() {
  int val = analogRead(sensorPin);
  Serial.println(val);
  delay(100);

}

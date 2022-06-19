int sensorPin = A3;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

}
//buffer
// less than 987 = none 
// more than 988 = white
// less than 500 = black

void loop() {
  //gripper
  //more than 700 = white
  //less than 100 = black
  //100 < x < 700 = nothing
  int val = analogRead(sensorPin);
  Serial.println(val);
  delay(100);

}

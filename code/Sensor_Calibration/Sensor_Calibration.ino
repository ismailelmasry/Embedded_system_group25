// Pusher = A1
// Gripper = A2
// Buffer = A3
int sensorPin = A3;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

}

//Buffer
// less than 987 = none 
// more than 988 = white
// less than 500 = black

//Gripper
//more than 700 = white
//less than 100 = black
//100 < x < 700 = nothing

//Pusher
//more than ? = white
//less than ? = black
//? < x < ? = nothing


void loop() {

  int val = analogRead(sensorPin);
  Serial.println(val);
  delay(100);

}

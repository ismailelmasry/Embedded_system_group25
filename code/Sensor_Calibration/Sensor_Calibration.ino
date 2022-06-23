// Pusher = A1
// Gripper = A2
// Buffer = A3
// Swtich = A4
int sensorPin = A1;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

}

//Buffer
// more than 983 = none 
// more than 993 = white
// less than 700 = black

//Gripper
//more than 900 = white
//less than 100 = black
//100 < x < 900 = nothing

//Pusher
//more than ? = white
//less than ? = black
//? < x < ? = nothing


void loop() {

  int val = analogRead(sensorPin);
  Serial.println(val);
  delay(100);

}

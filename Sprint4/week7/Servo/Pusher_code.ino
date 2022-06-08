/*

*/

#define pin_sensor1 1 //for the pin of the first optical sensor before the pusher
#define pin_motor1 2 //for the pin of the motor for the pusher
#define pin_motor1_in1 3
#define pin_motor1_in2 4 
bool platform = 0; // boolean to keep track if the platform has a disk. 0 mean no disk;
int disk_white=0;
int disk_black=0;
int disk_not_used=0;
int speed =126; //set speed of motor 0 to 255
void pusher(void){
  delay(2000); // waits for the disk to go in front of the pusher
  analogWrite(pin_motor1,speed); //sets speed of motor
  digitalWrite(pin_motor1_in_1,HIGH);//sets motor to push(clockwise)
  digitalWrite(pin_motor1_in_2,LOW);
  delay(2000); // time it needs to push
  digitalWrite(pin_motor1_in_1,LOW); //sets the motor to pull(anticlockwise)
  digitalWrite(pin_motor1_in_2,HIGH);
  delay(2000); //time it needs to pull back. same as pushing time
  digitalWrite(pin_motor1_in_1,HIGH);
  digitalWrite(pin_motor1_in_2,HIGH);
  platform=1; // platform is set to 0 again in the pick and drop function of the robot arm.
}

void setup() {
  pinMode(pin_sensor1, INPUT); 
  pinMode(pin_motor1, OUTPUT); 
  pinMode(pin_motor1_in, OUTPUT); //logic pin of the H-bridge
  pinMode(pin_motor1_out, OUTPUT); //logic pin of the H-bridge
}

void loop() {
  if (!digitalRead(pin_sensor1) && !platform){ //for when the sensor detects something and the platform doesnt have a disk
    pusher(); 
  }
  else if(!digitalRead(pin_sensor1) && platform){ //for when the sensor detects something and the platform has a disk
    disk_not_used++;
  }
}

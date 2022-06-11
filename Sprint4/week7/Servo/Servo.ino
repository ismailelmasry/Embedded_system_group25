#include <Servo.h>

Servo servoBase;
Servo servoArmY;

const int sensor1Pin = A1;
const int sensor2Pin = A2;
const int sensor3Pin = A3;
const int baseSwitch = A4;

//those value need to be filled 
int bufferBaseAngle = 30;
int sliderBaseAngle = 120;
int pickUpArmYAngle = 0;
int dropArmYAngle = 0;

bool controlVal = true;

void setup() {
  Serial.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(baseSwitch, INPUT);
  servoBase.attach(7);
  servoArmY.attach(8);
  MoveToDefaultPosition();

}

void loop() {
  int sensorPusher = analogRead(sensor1Pin); //value from the optical sensor
  int baseStopper = analogRead(baseSwitch);

}

void moveServo(Servo servo, int val, int servoPin){
  servo.attach(servoPin);
  servo.write(val);
  delay(1000);
  servo.detach();
  delay(500);
  }

  void switchServo(){
  if(controlVal == true){
    val = analogRead(baseSwitch);
    }
  Serial.println(val);
  delay(50);
  if(val > 5){
    servoBase.writeMicroseconds(1500);
    controlVal = false;
  }else if (val == 0){
    servoBase.writeMicroseconds(2000);
    delay(50);
    switchServo();
  } 
  }

void moveBaseServo(int howLong, String where){
  if(where == "clockwise"){
    servoBase.writeMicroseconds(2000);
    delay(howLong);
    servoBase.writeMicroseconds(1500);
    delay(500);
  } else if(where == "counter-clockwise"){
    servoBase.writeMicroseconds(1000);
    delay(howLong);
    servoBase.writeMicroseconds(1500);
    delay(500);
    }
  
  }

void MoveToDefaultPosition(){
  
  moveBaseServo(1000, "counter-clockwise");
  delay(300);
  moveServo(servoArmY, 0, 8);
  delay(300);
  }

void PickUpAndDropDisk(){
  //Picks up the disk from buffer zone
  servoGripper.write(gripperOpenAngle);
  delay(300);
  
  for(int i = 0; i < 1000; i++){ // when baseStopper sensor is detected the mark, the base will stop there
    servoBase.writeMicroseconds(2000); //run
    delay(50);
    if(baseSwitch > 0){
      servoBase.writeMicroseconds(1000); //stop
      break;
    }
  }
  
  delay(500);
  for(int i = 0; i <= pickUpArmYAngle; i++) // puts the arm down
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(500);
  
  servoGripper.write(gripperCloseAngle); // closes the gripper
  
  for(int i = pickUpArmYAngle; i >= 0; i--) // puts the arm up
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(500);
  
  //Drops the disk to slider
  moveBaseServo(1000, "clockwise"); // rotates to slider
  delay(500);
  
  for(int i = 0; i >= dropArmYAngle; i++) // puts the arm down
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(300);
  servoGripper.write(gripperOpenAngle); // opens the gripper and drops the disk
  delay(300);
  
  MoveToDefaultPosition();
  
  }


  

#include <Servo.h>

Servo servoBase;
Servo servoArmY;
Servo servoGripper;

const int sensor1Pin = A1;
const int sensor2Pin = A2;
const int sensor3Pin = A3;

//those value need to be filled 
int bufferBaseAngle = 30;
int sliderBaseAngle = 120;
int pickUpArmYAngle = 0;
int dropArmYAngle = 0;
int gripperCloseAngle = 0;
int gripperOpenAngle = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  servoBase.attach(7);
  servoArmY.attach(8);
  servoGripper.attach(9);
  MoveToDefaultPosition();

}

void loop() {
  int sensorPusher = analogRead(sensor1Pin); //value from the optical sensor
  PickUpAndDropDisk();

}

void MoveToDefaultPosition(){
  servoBase.write(0);
  delay(300);
  servoArmY.write(0);
  delay(300);
  servoGripper.write(0);
  delay(300);
  }

void PickUpAndDropDisk(){
  //Picks up the disk from buffer zone
  servoGripper.write(gripperOpenAngle);
  delay(300);
  servoBase.write(bufferBaseAngle);
  delay(500);
  for(int i = 0; i <= pickUpArmYAngle; i++)
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(500);
  servoGripper.write(gripperCloseAngle);
  for(int i = pickUpArmYAngle; i >= 0; i--)
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(500);
  
  //Drops the disk to slider
  servoBase.write(sliderBaseAngle);
  delay(500);
  for(int i = 0; i >= dropArmYAngle; i++)
  {
    servoArmY.write(i);
    delay(30);
  }
  delay(300);
  servoGripper.write(gripperOpenAngle);
  delay(300);
  MoveToDefaultPosition();
  
  }


  

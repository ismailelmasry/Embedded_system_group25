#include <Servo.h>
#include <AFMotor.h>

Servo servoBase;
Servo servoArmY;
AF_DCMotor motor(4);
bool gripped = false;

const int sensor1Pin = A1; // pusher
const int sensor2Pin = A2; // gripper
const int sensor3Pin = A3; // ??
const int baseSwitch = A4;

//those value need to be filled 
int baseBufferToSlideDelay = 3000;
int ArmUpAngle = 180;
int ArmDownAngle = 0;

bool controlVal = true;
int valSwitch;
int colorValueOfTheDisk = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(baseSwitch, INPUT);
  servoBase.attach(10);
  servoArmY.attach(9);
  servoArmY.write(ArmUpAngle);
  motor.setSpeed(200);
  motor.run(RELEASE);
  valSwitch = analogRead(baseSwitch);

}

void loop() {
  servoArmY.write(0);
  delay(1000);
  servoArmY.write(180);
  delay(1000);
  //PickUpAndDropDisk();
  /*if(colorValueOfTheDisk != 0){
    if(colorValueOfTheDisk < 200){
      Serial.println("white");
    } else{
      Serial.println("black");  
    }
  }*/
  
  //exit(0);

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void closeGripper(){
  motor.run(BACKWARD);
  delay(1130);
  motor.run(RELEASE);
  }

void openGripper(){
  motor.run(FORWARD);
  delay(1000);
  motor.run(RELEASE);
  }
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void moveServo(Servo servo, int val, int servoPin){ // backup plan if servos keep getting bugged
  servo.attach(servoPin);
  servo.write(val);
  delay(1000);
  servo.detach();
  delay(500);
  }
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void moveBaseServo(int howLong, String where){
  if(where == "clockwise"){
    servoBase.writeMicroseconds(1750);
    delay(howLong);
    servoBase.writeMicroseconds(1500);
    delay(100);
  } else if(where == "counter-clockwise"){
    servoBase.writeMicroseconds(1250);
    delay(howLong);
    servoBase.writeMicroseconds(1500);
    delay(100);
    }
  
  }
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void findAndStopAtBufferZone(){
  
  if(controlVal == true){
    valSwitch = analogRead(baseSwitch);
    }
  Serial.println(valSwitch);
  delay(50);
  if(valSwitch > 50){
    servoBase.writeMicroseconds(1500);
    controlVal = false;
    return;
  }else if (valSwitch <= 50){
    servoBase.writeMicroseconds(1750);
    delay(50);
    findAndStopAtBufferZone();
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void MoveToDefaultPosition(){
  servoArmY.write(ArmUpAngle);
  delay(300);
  findAndStopAtBufferZone();
  delay(300);
  
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void PickUpAndDropDisk(){
  MoveToDefaultPosition(); // base towards buffer zone and arm up 
  //Picks up the disk from buffer zone
  openGripper();
  delay(1000);
  servoArmY.write(ArmDownAngle);
  delay(1000);
  closeGripper();
  delay(1000);
  colorValueOfTheDisk = analogRead(sensor2Pin);
  servoArmY.write(ArmUpAngle);
  delay(300);
  Serial.println("go to slide");
  moveBaseServo(baseBufferToSlideDelay, "clockwise");
  delay(300);
  servoArmY.write(ArmDownAngle);
  delay(300);
  openGripper();
  delay(500);
  controlVal = true;
  //MoveToDefaultPosition();  
}

void test(){
  MoveToDefaultPosition();
  }

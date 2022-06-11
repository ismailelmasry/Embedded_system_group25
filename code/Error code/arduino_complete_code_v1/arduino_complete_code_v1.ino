
#include <Servo.h>

const int ledPin = 10; // TODO change values of pins
const int buzzerPin = 11; 

// for Servo
const int sensor1Pin = A1; // 
const int sensor2Pin = A2; // 
const int sensor3Pin = A3; //

Servo servoBase;
Servo servoArmY;
Servo servoGripper;

//those value need to be filled  
int bufferBaseAngle = 30;
int sliderBaseAngle = 120;
int pickUpArmYAngle = 0;
int dropArmYAngle = 0;
int gripperCloseAngle = 0;
int gripperOpenAngle = 0;

// for Pusher
#define pin_sensor1 1 //for the pin of the first optical sensor before the pusher
#define pin_motor1 2 //for the pin of the motor for the pusher
#define pin_motor1_in1 3
#define pin_motor1_in2 4 
bool platform = 0; // boolean to keep track if the platform has a disk. 0 mean no disk;
int disk_white=0;
int disk_black=0;
int disk_not_used=0;
int speed =126; //set speed of motor 0 to 255


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // no disk so led is on

  // for servo motor
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  servoBase.attach(7);
  servoArmY.attach(8);
  servoGripper.attach(9);
  MoveToDefaultPosition();

  // for pusher
  pinMode(pin_sensor1, INPUT); 
  pinMode(pin_motor1, OUTPUT); 
  pinMode(pin_motor1_in, OUTPUT); //logic pin of the H-bridge
  pinMode(pin_motor1_out, OUTPUT); //logic pin of the H-bridge

}

void loop() {

  int sensorPusher = analogRead(sensor1Pin); //value from the optical sensor
  PickUpAndDropDisk();

  if (!digitalRead(sensor1Pin) && !platform){ //for when the sensor detects something and the platform doesnt have a disk
    pusher(); 
  }
  else if(!digitalRead(sensor1Pin) && platform){ //for when the sensor detects something and the platform has a disk
    disk_not_used++;
  }

  // for melody
    int decimal = BinaryToDecimal("101");
   if((decimal % 3) == 0){
    PlayMelody1();
   }else if((decimal % 3) == 1){
    PlayMelody2();
   }else if((decimal % 3) == 2){
    PlayMelody3();
   }

  // for error handling
  int e; // error case
  String diskColor;

  // detect disk color
  int diskColorCode = readLight(sensor1Pin);
  if(diskColorCode == 1){
    diskColor = "Black"; 
  }
  if(diskColorCode==0){
    diskColor = "White";
  }
  else{
    e = 2; // color not detected
  }

}

int BinaryToDecimal(char *binary) {
  int result = 0;
  while(*binary) {
    result <<= 1;
    if(*binary++ == '1') result |= 1;
  }
  return result;
}

// make the set led blink on a set delay period
void blinkLed(int delayP, int pinLed){
  digitalWrite(pinLed, HIGH);
  delay(delayP);
  digitalWrite(pinLed, LOW);
  delay(delayP);
}

// to detect the color of the disk.
int readLight(int lightPin){
  int light = analogRead(lightPin);
  int diskColor;
  
  if(light<200){ // it is dark
    diskColor = 1; // "Black"
  }
  if(light>1000){
    diskColor = 0; // "White"
  }
  else{
    handleError(2);
    diskColor = 10; // "Color does not fall into other catogories"
  }
  return diskColor;
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


void handleError(int e){
 switch (e) {
  case 1:
    printf("No disk detected");
    pinMode(ledPin, HIGH);
    break;

  case 2:
    printf("No color detected");
    //led blinks fast 3 times
    for(int i= 0; i<3;i++){
      blinkLed(250, ledPin);
    }
    break;

  case 3:
    printf("Sensors blocked");
    //led stays on
    pinMode(ledPin, HIGH);
    //fast sirene goes on
    for (int i = 220; i <= 800; i++) {
      tone(buzzerPin, i);
      delay(5);
    }
    break;

  case 4:
    printf("Pusher is stuck");
    //led blinks slow 5 times
    for ( int t = 1; t <= 6; t++) {
      blinkLed(1000, ledPin);
    }
    //fast sirene goes on
    for (int i = 220; i <= 800; i++) {
      tone(buzzerPin, i);
      delay(5);
    }
    break;

  case 5:
    printf("Grabber is stuck");
    //led blinks fast 5 times
    for ( int t = 1; t <= 6; t++) {
      blinkLed(100, ledPin);
    }
    //fast sirene goes on
    for (int i = 220; i <= 800; i++) {
      tone(buzzerPin, i);
      delay(5);
    }
    break;

  case 6:
    printf("The buffer zone is full");
    //led blinks very fast 10 times
    for ( int t = 1; t <= 11; t++) {
      blinkLed(50, ledPin);
    }
    //slow sirene goes on
    for (int i = 220; i <= 800; i++) {
      tone(buzzerPin, i);
      delay(50);
    }
    break;

  default:
    printf("No current error detected");
    //if led was on led goes out
    pinMode(ledPin, LOW);
    break;
  }
}

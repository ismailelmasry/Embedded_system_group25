#include <Servo.h>
#include <AFMotor.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

Servo servoBase;
Servo servoArmY;
AF_DCMotor motor(4); // Gripper
bool gripped = false;

const int sensor1Pin = A1; // Pusher
const int sensor2Pin = A2; // Gripper
const int sensor3Pin = A3; // Buffer
const int baseSwitch = A4;
const int buzzer = 11;
String binaryPattern = "";

//those value need to be filled 
int baseBufferToSlideDelay = 3500;
int ArmUpAngle = 0;
int ArmDownAngle = 80;

bool controlVal = true;
int valSwitch;
int colorValueOfTheDiskGripper = 0;
int colorValueOfTheDiskBuffer = 0;
String response;
int counter = 0;

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
  delay(2000);
  colorValueOfTheDiskBuffer = analogRead(sensor3Pin);
  Serial.println(colorValueOfTheDiskBuffer);
  delay(100);
  if(colorValueOfTheDiskBuffer <= 987 && colorValueOfTheDiskBuffer > 500){
    Serial.println("There is no disk in the buffer!");
    counter++;
  }else {
    PickUpAndDropDisk();
    if(colorValueOfTheDiskGripper < 100){
      Serial.println("black");
      counter = 0;
      binaryPattern = binaryPattern + "1";
    } else if (colorValueOfTheDiskGripper > 700){
      Serial.println("white");
      counter = 0;
      binaryPattern = binaryPattern + "0";
    } else{
      Serial.println("none");  
    }
  }
  if(binaryPattern.length() == 8 || counter == 10){ // if slider is full or if there is no disk in the buffer for 30 secs
    if(binaryPattern != ""){
    char binary[binaryPattern.length() + 1];
    binaryPattern.toCharArray(binary, binaryPattern.length() + 1);
    int decimal = BinaryToDecimal(binary);
    if((decimal % 3) == 0){
    Serial.println("melody1");
    //PlayMelody1();
    delay(3000);
    exit(0);
    }else if((decimal % 3) == 1){
    Serial.println("melody2");
    //PlayMelody2();
    delay(3000);
    exit(0);
    }else if((decimal % 3) == 2){
    Serial.println("melody3");
    //PlayMelody3();
    delay(3000);
    exit(0);
    }
    }else {
      Serial.println("There was no input at all so no melody to you!");
      delay(3000);
      exit(0);
    }
    
  }
  
  
  //exit(0);

}

int BinaryToDecimal(char *binary) {
  int result = 0;
  while(*binary) {
    result <<= 1;
    if(*binary++ == '1') result |= 1;
  }
  return result;
}

void testArmServo(){
  servoArmY.write(ArmUpAngle);
  delay(2000);
  servoArmY.write(ArmDownAngle);
  delay(2000);
  }
  
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void closeGripper(){
  motor.run(FORWARD);
  delay(1100);
  motor.run(RELEASE);
  }

void openGripper(){
  motor.run(BACKWARD);
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
  delay(100);
  if(valSwitch > 100){
    servoBase.writeMicroseconds(1500);
    controlVal = false;
    return;
  }else if (valSwitch <= 100){
    servoBase.writeMicroseconds(1350);
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
  servoArmY.write(ArmUpAngle);
  delay(300);
  Serial.println("go to slide");
  moveBaseServo(baseBufferToSlideDelay, "clockwise");
  colorValueOfTheDiskGripper = analogRead(sensor2Pin);
  if(colorValueOfTheDiskGripper > 100 && colorValueOfTheDiskGripper < 700){
    Serial.println("The gripper couldn't get the disk! Retrying...");
    controlVal = true;
    return;
  }
  delay(300);
  openGripper();
  delay(500);
  closeGripper();
  controlVal = true;
  
}

void fixWire(){
  servoBase.writeMicroseconds(2000);
  }

void PlayMelody1(){
  const float songSpeed = 1.0;
// Do not touch
int PoCnotes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0};

int PoCdurations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125};

    
  const int totalNotes = sizeof(PoCnotes) / sizeof(int);
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = PoCnotes[i];
    float wait = PoCdurations[i] / songSpeed;
    if (currentNote != 0)
    {
      tone(buzzer, PoCnotes[i], wait);
    }
    else
    {
      noTone(buzzer);
    }
    delay(wait);
  }
  }

  void PlayMelody2(){
    
 const float songSpeed = 1.0;
// Do not touch
int PoCnotes[] = {

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4};

int PoCdurations[] = {

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125};

    
  const int totalNotes = sizeof(PoCnotes) / sizeof(int);
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = PoCnotes[i];
    float wait = PoCdurations[i] / songSpeed;
    if (currentNote != 0)
    {
      tone(buzzer, PoCnotes[i], wait);
    }
    else
    {
      noTone(buzzer);
    }
    delay(wait);
  }
  
  }

void PlayMelody3(){

 const float songSpeed = 1.0;
// Do not touch
int PoCnotes[] = {

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4};

int PoCdurations[] = {

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500};

    
  const int totalNotes = sizeof(PoCnotes) / sizeof(int);
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = PoCnotes[i];
    float wait = PoCdurations[i] / songSpeed;
    if (currentNote != 0)
    {
      tone(buzzer, PoCnotes[i], wait);
    }
    else
    {
      noTone(buzzer);
    }
    delay(wait);
  }
  }

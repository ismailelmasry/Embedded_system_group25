#include <Servo.h>
#define Servo_PWM 10
Servo servo;
int val;
bool controlVal = true;
void setup() {
  servo.attach(Servo_PWM);
  Serial.begin(9600);
  pinMode(A4, INPUT);
  
  
}

void loop() {
  switchServo();
  if(controlVal == false){
    servo.writeMicroseconds(1750);
  delay(5000);
  servo.writeMicroseconds(1500);
  exit(0);
    }
  
}

void switchServo(){
  if(controlVal == true){
    val = analogRead(A4);
    }
    Serial.println(val);
    delay(100);
    if(val > 50){
    servo.writeMicroseconds(1500);
    controlVal = false;
    }else if (val == 0){
    servo.writeMicroseconds(1750);
    switchServo();
  } 
  
  }

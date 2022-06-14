#include <Servo.h> // include servo library to use its related functions
#define Servo_PWM 9 // A descriptive name for D6 pin of Arduino to provide PWM signal
Servo servo;  // Define an instance of of Servo with the name of "MG995_Servo"
  

void setup() {
  servo.attach(Servo_PWM);  // Connect D6 of Arduino with PWM signal pin of servo motor
}

void loop() {
  /*servo.write(0); //Turn clockwise at high speed
  delay(3000);
  servo.detach();//Stop. You can use deatch function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
  delay(2000);
  servo.attach(Servo_PWM);//Always use attach function after detach to re-connect your servo with the board
  servo.write(-90);
  delay(3000);
  servo.detach();//Stop
  delay(2000);
  servo.attach(Servo_PWM);*/

  servo.writeMicroseconds(1000);            
  delay(2000);
  servo.writeMicroseconds(1500); 
  delay(1000);
  servo.writeMicroseconds(2000);             
  delay(2000);
  servo.writeMicroseconds(1500); 
  delay(1000);

      
}

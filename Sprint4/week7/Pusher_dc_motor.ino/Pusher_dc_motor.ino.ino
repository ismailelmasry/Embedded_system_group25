#include <AFMotor.h>

AF_DCMotor motor(4);
bool gripped = false;

void setup() 
{
  //Set initial speed of the motor & stop
  motor.setSpeed(200);
  motor.run(RELEASE);
}

void loop() {
  uint8_t i;

  // Turn on motor
  motor.run(FORWARD);
  
    // Accelerate from zero to maximum speed
  if(gripped== false){
    for(int i = 0; i<100; i++){
    motor.setSpeed(200);  
      delay(10);
    }
    gripped = true;
  }



  if(gripped==true){
      // stop for few sec
    for(int i = 0; i<50; i++){
      motor.setSpeed(0);  
        delay(5);
    }
    motor.run(BACKWARD);
      // Accelerate from zero to maximum speed
    for(int i = 0; i<100; i++){
      motor.setSpeed(200);  
        delay(10);
    }
    gripped==false;
  }


  // Now turn off motor
  motor.run(RELEASE);
  delay(1000);
}

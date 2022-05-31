//possible errors
//detecting no disk e=1
//detecting no color e=2
//sensors blocked e=3
//pusher stuck e=4
//grapper stuck e=5
//buffer full e=6

//after connecting buzzer and led to arduino ennter pins here
int buzzerPin = ; //buzzerpin here 
int LED = ; //pin led is connected to here
int e //error type
/*
 //sirene
  for(int i=220; i<=800;i++){
    tone(buzzerPin, i);
    delay(5)
  }

  //blinking led 5 times
  for( int a=1 ; a<= 6; a++){
  digitalWrite(LED, HIGH);
  delay(100)
  digitalWrite(LED, LOW);
  delay(100)
  }
 */
void setup() {
  pinMode (buzzerPin, OUTPUT); // declaring buzzer as an output here
  pinMode(LED, OUTPUT); // declaring led as an output here

}

void loop() {

  switch(e){
    case 1:
      printf("No disk detected");
      pinMode(LED, HIGH);
    break;
    
    case 2:
      printf("No color detected");
      //led blinks fast 3 times
      for( int t=1; t<= 4; t++){
        pinMode(LED,HIGH);
        delay(100)
        pinMode(LED, LOW);
        delay (100) 
      }
    break;
    
    case 3:
      printf("Sensors blocked");
      //led stays on
      pinMode(LED,HIGH);
      //sirene goes on
      for(int i=220; i<=800;i++){
      tone(buzzerPin, i);
      delay(5)
      }
      break;
    
    case 4:
      printf("Pusher is stuck");
        //led blinks slow 5 times
        for( int t=1; t<= 6; t++){
        pinMode(LED,HIGH);
        delay(1000)
        pinMode(LED, LOW);
        delay (1000) 
        }
        //fast sirene goes on
        for(int i=220; i<=800;i++){
        tone(buzzerPin, i);
        delay(5)
        }
    break; 
    
    case 5:
      printf("Grabber is stuck");
        //led blinks fast 5 times
        for( int t=1; t<= 6; t++){
        pinMode(LED,HIGH);
        delay(100)
        pinMode(LED, LOW);
        delay (100) 
        }
        //fast sirene goes on
        for(int i=220; i<=800;i++){
        tone(buzzerPin, i);
        delay(5)
        }      
    break;
    
    case 6:
      printf("The buffer zone is full");
        //led blinks very fast 10 times
        for( int t=1; t<= 11; t++){
        pinMode(LED,HIGH);
        delay(10)
        pinMode(LED, LOW);
        delay (10) 
        }
        //slow sirene goes on
        for(int i=220; i<=800;i++){
        tone(buzzerPin, i);
        delay(50)
        }      
    break;
    
    default:
      printf("No current error detected");
      //if led was on led goes out
      pinMode(LED, LOW);
    break;
  }
  

}

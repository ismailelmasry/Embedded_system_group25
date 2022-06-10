const int ledPin = 10; // TODO change values of pins
const int buzzerPin = 11; 
const int lightPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightPin, INPUT);
  digitalWrite(ledPin, HIGH); // no disk so led is on
}

void loop() {
  int e; // error case
  String diskColor;

  // detect disk color
  int diskColorCode = readLight(lightPin);
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

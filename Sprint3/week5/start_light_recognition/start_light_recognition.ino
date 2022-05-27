int light;

void setup() {
  Serial.begin(9600);
}

void loop() {
  light = analogRead(A0); // A0 or something else which pin the LDR is connected to
  
  if(light<200){ //it is dark aka black
  }

  else{
  }
  }
  
  Serial.println(light);
  delay(100);
}

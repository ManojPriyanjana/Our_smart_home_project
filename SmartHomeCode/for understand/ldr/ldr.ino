
void setup() {
  
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT);
}

void loop() {
  
  int sensorVal = digitalRead(2);
 
  Serial.println(sensorVal);

 
  if (sensorVal == LOW) {
    digitalWrite(10, LOW);
  } else {
    digitalWrite(10, HIGH);
  }
}

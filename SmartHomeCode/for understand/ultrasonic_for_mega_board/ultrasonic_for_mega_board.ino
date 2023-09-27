
int trig=2;
int echo=4;

int led =8;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  long t = pulseIn(echo,HIGH);

  long inches = t / 74 / 2;
  long cm= t / 29 / 2;

  Serial.print(inches);
  Serial.print("in \t");
  Serial.print(cm);
  Serial.println("cm \t");

  if(cm<30)
  {
    digitalWrite(led,HIGH);
  }else{
    digitalWrite(led,LOW);
  }

}

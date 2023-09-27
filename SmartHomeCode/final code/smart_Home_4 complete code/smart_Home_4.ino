
#include <Arduino.h>

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6ihGM4IDQ"
#define BLYNK_TEMPLATE_NAME "Connected"
#define BLYNK_AUTH_TOKEN "iaKeiUWc1Bt-BgMQFUrQyNgoKjVHHvvY"

#define BLYNK_PRINT Serial
//----------------------
int N3 =D5; // for moter
int N4 =D6; //for moter

//----------------------
unsigned long prevTime = millis();
//----------------------
int trigPin=D4;
int echoPin=D2;
long duration;
int distance;
//----------------------

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "ManojPriyanjana";
char pass[] = "C1b08ac3";

BlynkTimer timer;

int value;
int valueMoter; // moter
int led;// led

int PushButtonPin = D7;



BLYNK_WRITE(V0)
{
  value = param.asInt();
  // Blynk.virtualWrite(V1, value);
}

BLYNK_WRITE(V1) // for moter
{
  valueMoter = param.asInt();
  // Blynk.virtualWrite(V1, value);
}
BLYNK_WRITE(V5) // for moter
{
  led = param.asInt();
  
}

void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

 
  pinMode(D0, OUTPUT); // for LED

  pinMode(N3, OUTPUT); //for moter
  pinMode(D4, OUTPUT); //for moter

  pinMode(trigPin,OUTPUT);// for ultrasonic
  pinMode(echoPin,INPUT);// for ultrasonic
  //pinMode(PushButtonPin,INPUT);// push button

  pinMode(D1, INPUT_PULLUP);

  //attachInterrupt(digitalPinToInterrupt(led),light,CHANGE);//pin,funcnction,mode

 



}

unsigned long prevTime2 = millis();
void loop()
{
  unsigned long currentTime = millis();
  int sensorVal = digitalRead(1);

  // if (sensorVal == LOW) {
  //   digitalWrite(D0, LOW);
  // } else {
  //   digitalWrite(D0, HIGH);
  // }
   
  //----------------button----------
  // int button = digitalRead(PushButtonPin);
  // Serial.println(button);
  // if(button == 1)
  // {
  //     digitalWrite(D0,HIGH);
  // }else{
  //   digitalWrite(D0,LOW);
  // }
  //---------------------------
  Blynk.run();
  timer.run();
  //--
  int a=0;
  // for door onpen and close menuwal
  // if (value==1 && valueMoter==0 ) {
  //     //digitalWrite(D0,HIGH);
  //     analogWrite(N3,170);
  //     digitalWrite(N4,LOW);
  //   }else if(value==0 && valueMoter==1 ){
  //     analogWrite(N4,170);
  //     digitalWrite(N3,LOW);
  //   }else{
  //     digitalWrite(N3,LOW);
  //     digitalWrite(N4,LOW);
  //     //digitalWrite(D0,LOW);
  //     }

  // for automate
  if (led==1){
        digitalWrite(D0,HIGH);
        delay(2000);
        
      }else{
        digitalWrite(D0,LOW);
        delay(2000);
        
      }
 ultrasonic();

    if(distance<30){
      open();
      delay(2500);
      stop();
      delay(5000);
      close();
      delay(1050);
      stop();
    }



   
  //  if (led==1){
  //       digitalWrite(D0,HIGH);
  //       Blynk.logEvent("gate_info");
  //       Blynk.virtualWrite(V7,"Gate is Open");
  //     }else{
  //       digitalWrite(D0,LOW);
  //       Blynk.virtualWrite(V7,"Gate is Close");
  //     }
 /// time functins
      
      // if (currentTime-prevTime > 2000){
      // Serial.println(currentTime-prevTime);
      // digitalWrite(N3,!digitalRead(N3));//LOW
      // digitalWrite(N4,digitalRead(N4));//LOW
      // prevTime = currentTime;
      // }

  ///  end of time functins
 

}

void ultrasonic(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration * 0.034/2; //formula for calculate the distance for ultrasonic sensor
  Blynk.virtualWrite(V6,distance);
    
}
void light(){
   
}


void close(){
        analogWrite(N4,90);
        analogWrite(N3,LOW);
        Blynk.virtualWrite(V7,"Gate is Close");
       
}

void open(){
        analogWrite(N3,90);
        analogWrite(N4,LOW);
        Blynk.logEvent("gate_info");
        Blynk.virtualWrite(V7,"Gate is Open");
     
  }

void stop(){
  analogWrite(N3,LOW);
  analogWrite(N4,LOW);
}

      

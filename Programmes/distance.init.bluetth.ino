
#include<SoftwareSerial.h>
#define RX 8
#define TX 9
SoftwareSerial BlueT(RX,TX);
const int echo=5;
const int trig=3;
char Data;
int d; // distance à laquelle l'utilisateur se trouve du réveil, on va devoir la faire changer avec le telephone 


void setup() {
  Serial.begin(9600);
  BlueT.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  
  int d= 100.0;
  digitalWrite(trig,HIGH); //generation de l'impulsion trig de 10 microsecondes
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);

  float duree=pulseIn(echo,HIGH,500000);
  float distance = duree*0.034/2;
 // Serial.println("Distance : ");
 // Serial.println(distance);
 // Serial.println("cm");
 


if (BlueT.available()){
//Serial.println("le bluetooth est connecté");
Data= BlueT.read();


if (Data=='A') { 
    //Serial.println(Data);
     // Serial.println(a);
      d=BlueT.parseInt();
      Serial.print("distance initialisée:");
      Serial.println(d);
      } 
      
}


if (distance <=d){
  Serial.println("tu es tjrs dans ton lit ");
 }
else{ 
  Serial.println("il est levé ");
}

 delay(5000);
}

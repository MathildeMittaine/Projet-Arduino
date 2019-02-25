#include <SoftwareSerial.h>
#define ARDUINO_RX 3//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 4//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0} ;
#define RX 8
#define TX 9
SoftwareSerial BlueT(RX,TX);
const int echo=5;
const int trig=6;
char Data;
int d; // distance à laquelle l'utilisateur se trouve du réveil, on va devoir la faire changer avec le telephone 






#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01

void setup() 
{
    mySerial.begin(9600);
          Serial.begin(9600);
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
      delay(200);//wait for 200ms
      sendCommand(CMD_PLAY_W_VOL, 0X1E01);//play the first song with volume 30 class

      Serial.begin(9600);
  BlueT.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}
String str;






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
  
  sendCommand(CMD_PLAY, 0X0D);//play it again 
Serial.println("Play");
delay(1000);

 }
else{ 
  Serial.println("il est levé ");
  delay(1000);
  sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
  Serial.println("Pause");

}

 delay(5000);





/////////////////////////////////////////////////////////////////////////
  
if(Serial.available())
{
str = Serial.readStringUntil('\n');

if(str == "2")
{
sendCommand(CMD_PLAY_W_VOL, 0X0F02);//play the second track with volume 30 class
Serial.println("Second sound track.");
}
if(str == "3")
{
sendCommand(CMD_PLAY_W_VOL, 0X0F03);//play the third track with volume 30 class
Serial.println("Third sound track.");
}
if(str == "4")
{
sendCommand(CMD_PLAY_W_VOL, 0X0F04);//play the forth track with volume 30 class
Serial.println("Forth sound track.");
}


sendCommand(CMD_PLAY, 0X0D);//play it again 
Serial.println("Play");

if(str == "pr")
{
sendCommand(CMD_PREVIOUS, 0X02);//play previous track
Serial.println("Playing previous track.");
}
if(str == "nx")
{
sendCommand(CMD_NEXT, 0X01);//play next track
Serial.println("Playing next track.");
}
 }
}







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]) ;
  }
}

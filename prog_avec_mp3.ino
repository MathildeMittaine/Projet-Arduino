#include <SoftwareSerial.h>
#define ARDUINO_RX 15//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 16//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0} ;

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01


#include <string.h>
#include <DS1302.h>
#include <LiquidCrystal.h>

#include <stdio.h> 
#include <string.h> 
// Init DS1302
DS1302 rtc(2, 3, 4);
LiquidCrystal lcd(5, 6, 7, 8, 9, 10); // initialise les commandes avec les n° de broches
// Init structure Time-data
Time t;

int heure;
int minutes;

//Programa voz
String mensaje;
#include<SoftwareSerial.h>
#define RX 12
#define TX 13
SoftwareSerial BlueT(RX,TX);


void setup() 
{
  
  Serial.begin(9600);




//programa voz
Serial.begin(9600);
  pinMode(14,OUTPUT);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);
}
String str;

void loop()
{

 
   //programa voz y programa la hora del despertador
   while(BlueT.available()){
    
    delay(10);
    char c=BlueT.read();
    Serial.println(char(c));
    if (c=='A') {
       
       digitalWrite(14,LOW);
    }
    if (c=='B') {
      Serial.println("ww");
      digitalWrite(14,HIGH);
    
    }

    if (c=='Q') {
      heure=BlueT.parseInt();
    }

    if (c=='W'){
      minutes=BlueT.parseInt();
    }
   // Serial.println(heure);
   // Serial.println(minutes);

     
   
  }

   t = rtc.getTime();
  if (heure==t.hour and minutes==t.min){
      mySerial.begin(9600);
      Serial.begin(9600);
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
      delay(200);//wait for 200ms
      sendCommand(CMD_PLAY_W_VOL, 0X1E01);//play the first song with volume 30 class


  }
  
}

void sendCommand(int8_t command, int16_t dat)
{
  //delay(20);
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

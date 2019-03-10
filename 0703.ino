//hello on va essayer de faire un programme correct stp mati

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
//Init DS1302
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

///////////////////////////////////MATI////////////////////////////////////////

#include <SoftwareSerial.h>
#define ARDUINO_RX 3//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 4//connect to RX of the module
#define RX 8
#define TX 9
const int echo=17;
const int trig=18;
int d; // distance à laquelle l'utilisateur se trouve du réveil, on va devoir la faire changer avec le telephone 

////////////////////////////////FIN MATI///////////////////////////////////////






void setup() //////////////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////////////////////
{
///////////////////////////////////MATI//////////////////////////////

mySerial.begin(9600);
          Serial.begin(9600);
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
      delay(200);//wait for 200ms
      //sendCommand(CMD_PLAY_W_VOL, 0X1E01);//play the first song with volume 30 class

      Serial.begin(9600);
  BlueT.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

/////////////////////////////FIN MATI///////////////////////////////////////


  
    // Positionnement horloge a run-mode et desactive protection en ecriture
  rtc.halt(false);
  rtc.writeProtect(false);
  
  Serial.begin(9600);

  //lcd
lcd.begin(16,2);




//programa voz
Serial.begin(9600);
  pinMode(14,OUTPUT);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);
}/////////////////////////////////////////////////////////////////////////////////////FIN SETUP//////////////////////////////////////////////////////////////////////////////////////////
String str;






//////////////////////////////////////////////////////////////////////////////////////////LOOP////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{

//////////////MATI//////////////////////////////////////////////

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
Serial.println("le bluetooth est connecté");
char c=BlueT.read();


if (c=='D') { 
    //Serial.println(c);
     // Serial.println(a);
      d=BlueT.parseInt();
      Serial.print("distance initialisée:");
      Serial.println(d);
      } 
      
}





/////////////////////////////FIN MATI////////////////////////////////////////////
  
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



if(str == "pr")
{
sendCommand(CMD_PREVIOUS, 0X02);//play previous track
Serial.println("Playing previous track.");
}
if(str == "nx")
{
//sendCommand(CMD_NEXT, 0X01);//play next track
Serial.println("Playing next track.");
}
 }


//////////////////////////////////////////////////////////////////////////
 
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

    if (c=='C'){
        sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
        delay(100000);
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
      Serial.println("C'est l'heure");
      
      if (distance <=d){
       char c=BlueT.read();
       Serial.println("tu es tjrs dans ton lit ");
  
        //sendCommand(CMD_PLAY, 0X0D);//play 
       Serial.println("Continu de Play");
        delay(500);
 // if( c=='C'){
    //sendCommand(CMD_PAUSE, 0X0E);                                               A VOIRRRRRRRRRRRRRRRRR
    //delay(10000);
  //}


     }
      else{ 
  Serial.println("il est levé ");
  delay(500);
  sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
  Serial.println("Pause");

}

 delay(5000);


  }

   // Ecriture date sur console serie
  lcd.setCursor(0, 0);
  lcd.print(t.date, DEC);
  lcd.print(" ");
  lcd.print(rtc.getMonthStr());
  lcd.print(" ");
  lcd.println(t.year, DEC);
 
  
  // Ecriture heure sur console serie
 lcd.setCursor(3, 1); 
  lcd.print(t.hour, DEC);
  lcd.print(":");
 lcd.print(t.min, DEC);
 lcd.print(":");
 lcd.print(t.sec, DEC);
 //lcd.println(":");

  
  // Attente d une seconde avant lecture suivante :)
  delay (1000);
  
}///////////////////////////////////////////////////////////////////FIN LOOP/////////////////////////////////////////////////////////////////////////////////////////////////////////




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

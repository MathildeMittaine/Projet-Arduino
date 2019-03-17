//hello on va essayer de faire un programme correct stp mati
#include <Adafruit_NeoPixel.h>
#define PIN 11
#define NUM_LEDS 18
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

////////////////////////////////////

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


#include <string.h>
#include <DS1302.h>
#include <LiquidCrystal.h>

#include <stdio.h> 
//Init DS1302
DS1302 rtc(2, 3, 4);
LiquidCrystal lcd(5, 6, 7, 8, 9, 10); // initialise les commandes avec les n° de broches
// Init structure Time-data
Time t;

int heure;
int minutes;

//Programa voz
String mensaje;
#define RX 12
#define TX 13
SoftwareSerial BlueT(RX,TX);

///////////////////////////////////MATI////////////////////////////////////////

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
      
      Serial.begin(9600);
  BlueT.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

/////////////////////////////FIN MATI///////////////////////////////////////


  
    // Positionnement horloge a run-mode et desactive protection en ecriture
  rtc.halt(false);
  rtc.writeProtect(false);
  //lcd
lcd.begin(16,2);




//programa voz
  pinMode(14,OUTPUT);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);

   strip.begin();
  strip.show(); // Initialize all pixels to 'off'
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


if (BlueT.available()){
  Serial.println("le bluetooth est connecté");
  char c=BlueT.read();
  

if (c=='X') { 
      d=BlueT.parseInt();
      Serial.print("distance initialisée:");
      Serial.println(d);
      } 
      
}





 delay(5000);


/////////////////////////////FIN MATI////////////////////////////////////////////
  

 
   //programa voz y programa la hora del despertador
   while(BlueT.available()){
    
    delay(100);
    char c=BlueT.read();
    Serial.println(char(c));
    if (c=='A') {
       
       rainbowCycle(20);
       Serial.println("allumer");
    }
    if (c=='B') {
      Serial.println("éteindre");
      setAll(0,0,0);
      
    
    }

    if (c=='Q') {
      heure=BlueT.parseInt();
    }

    if (c=='W'){
      minutes=BlueT.parseInt();
    }   
  }

t = rtc.getTime();
  if (heure==t.hour and minutes==t.min){
      mySerial.begin(9600);
      Serial.begin(9600);
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
      delay(200);//wait for 200ms
      sendCommand(CMD_PLAY_W_VOL, 0X1E01);//play the first song with volume 30 class
      rainbowCycle(20);
      Serial.println("C'est l'heure");
      char c=BlueT.read();
      if (c=='C' ){
        sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
        delay(1000);
        Serial.println("on éteint avec bluetooth");
    }

    while (distance >= d){
       Serial.println("pause");
       Serial.println("levé");
       sendCommand(CMD_PAUSE, 0X0E);//pause the playing track
       setAll(0,0,0);
        delay(1000);
     }
Serial.println("dans son lit");      
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


void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}


void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

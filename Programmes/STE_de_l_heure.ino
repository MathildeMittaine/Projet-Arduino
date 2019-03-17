

#include <DS1302.h>
#include <LiquidCrystal.h>
// Init DS1302
DS1302 rtc(2, 3, 4);
LiquidCrystal lcd(5, 6, 7, 8, 9, 10); // initialise les commandes avec les n° de broches
// Init structure Time-data
Time t;




void setup()
{
  // Positionnement horloge a run-mode et desactive protection en ecriture
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Init connection serie
  Serial.begin(9600);

  // Initialisation de l'horloge
  // A mettre a jour avec les bones valeurs pour initialiser l horloge RTC DS1302
  rtc.setDOW(FRIDAY);        // Jour a FRIDAY
  rtc.setTime(17, 31, 00);    // Heure a 19:10:00 (format sur 24 heure)
  rtc.setDate(21, 12, 2019);   // Date  au 3 juin 2016
//lcd
lcd.begin(16,2);


}

void loop()
{
  // recup donnees DS1302
  t = rtc.getTime();
  
  // Ecriture date sur console serie
  lcd.setCursor(0, 0);
  lcd.print(t.date, DEC);
  lcd.print(" ");
  lcd.print(rtc.getMonthStr());
  lcd.print(" ");
  lcd.println(t.year, DEC);
 
  
  // Ecriture heure sur console serie
 lcd.setCursor(4, 1); 
  lcd.print(t.hour, DEC);
  lcd.print(":");
 lcd.print(t.min, DEC);
 lcd.print(":");
 lcd.print(t.sec, DEC);
 lcd.println(":");

  
  // Attente d une seconde avant lecture suivante :)
  delay (1000);
}

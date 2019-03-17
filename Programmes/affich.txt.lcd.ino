// affichage d'un texte sur un LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // initialise les commandes avec les n° de broches


void setup() {
Serial.begin(9600);
lcd.begin(16, 2); // initialiser le nombre de colonnes et de lignes
lcd.print("Bonjour");
lcd.setCursor(0, 1); //le curseur se positionne à la 1ère colonne, 2ième ligne
lcd.print("je suis en PeiP2");
}



void loop() {
}

// ok il marche
// faire attention la plaque d'elena est divisée en 2

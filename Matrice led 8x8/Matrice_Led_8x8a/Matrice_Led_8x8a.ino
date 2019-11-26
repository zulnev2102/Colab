//librairie a importer
#include "LedControl.h"

/*
  Ref: Max7219
  LedControl(12,11,10,1);
  Pin 12 => DataIn
  Pin 11 => CLK
  Pin 10 => LOAD
*/

LedControl lc= LedControl(12, 10, 11, 1);
LedControl lc1= LedControl(15, 14, 13, 2);

/* Tempo afficheur */
unsigned long delaytime = 1000;

void setup() {
  lc.shutdown(0, false);
  //Set brightness
  lc.setIntensity(0, 8);
  // clear display
  lc.clearDisplay(0);
}

void writeArduinoOnMatrix() {

  //8 Byte 8 bits/Byte (8x8=64)
  byte t[8] = {B00000000, B11111111, B11111111, B00011000, B00011000, B00011000, B00011000, B00011000};
  byte Data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  byte DataShif[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  byte XData[8] = {B10111101, B11000011, B10011001, B10011001, B01000010, B01111110, B10011001, B10011001};
  byte EM[8] = {B11110001, B11000011, B10100101, B10011001, B11111001, B10000001, B10000001, B11110001};

  // Affichage du caractère T colonne par colonne (8écritures)
  for (int i = 0; i < 8; i++)
  {
    // Afficher la ligne t[i] à la position de la colonne i
    lc1.setColumn(0, i, t[i]);
    delay(delaytime);
  }
  lc1.clearDisplay(0);

  delay(1000);

  /* Affichage du caractère T ligne par ligne (Rotation 90° par rapport
    à la fonction setColumn ((8 écritures)*/
  for (int i = 0; i < 8; i++)
  {
    // Afficher la colonne t[i] à la position de la ligne i
    lc.setRow(0, i, t[i]);
    delay(delaytime);
  }
  lc1.clearDisplay(0);
  delay(1000);

  // Ecriture pixel par pixel (8x8 écritures)
  for (int k = 0; k < 8; k++)
  {

    {
      // Conversion Byte DataShif sur 8 bits
      int2BitArray( DataShif[i], 8, Data );
      for (int j = 0; j < 8; j++)
      {
        // Affichage Bit Data matrice (8x8)
        lc1.setLed(0, i, j, Data[j]);
        //delay(1);
      }
    }
    delay(1000);
    lc1.clearDisplay(0);
  }

}

void int2BitArray (unsigned char dataIn, unsigned char taille, byte *dataArray)
{
  int i=0;

  for (i=0;i<taille;i++)
    dataArray[taille - i - 1] = (dataIn >> i) & 0x01;
}

}

void loop() {
  writeArduinoOnMatrix();
}

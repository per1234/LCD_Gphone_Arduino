//This is an Arduino library for the LCD GRAPHIC 12864 SPI GPHONE (ZTE)
//Author=Le Hung
//https://mculearning.wordpress.com
//11/12/1016
//    +----------------------------------------------------+
//    |                                                    |
//    |  +----------------------------------------------+  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  |                                              |  |
//    |  +----------------------------------------------+  |
//    |                              10                  1 |
//    +------------------------------+---+--+--+--+--+---+-+
//                                   |   |  |  |  |  |   |
//                                   +   +  +  +  +  +   +
//  1->GND  2->RST  3->SCK  4->DC 5->LED+ 6->LED- 7->SDA  8->CS 9->3.3v 10->GND

#include <SPI.h>
#include "G_LCD.h"

#define CS_PIN   10
#define DC_PIN   9
#define RST_PIN  8

//default PIN SPI Hardware
//  SDA=PIN 11    (MOSI)
//  SCK= PIN 13   (SCLK)



G_LCD lcd(CS_PIN, DC_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.print("Sunday");
  lcd.gotoxy(5, 1);
  lcd.print("Good morning");
  lcd.image24x24(8, 0, 5);
  lcd.line(20, 1, 0, 2);  //write line by row
  lcd.line(8, 0, 4, 2);   //write line by col
  //lcd.setfont(0);   //Basic font
  lcd.setfont(1);     //blod font

  lcd.gotoxy(5, 5);
  lcd.print("11/12/2016");

  lcd.gotoxy(5, 7);
  lcd.print("10:52:56 AM");
}
void loop() {
  // put your main code here, to run repeatedly:
  
}

#include "font.c"
#include "G_LCD.h"


G_LCD::G_LCD(uint8_t cs, uint8_t dc, uint8_t rst) {
  _CS = cs;
  _DC = dc;
  _RST= rst;
}

void G_LCD::lcd_write(unsigned char cd, unsigned char data) {
  digitalWrite(_CS, LOW);
  if (cd)
    digitalWrite(_DC, HIGH);
  else
    digitalWrite(_DC, LOW);

  SPI.transfer(data);
  digitalWrite(_DC, LOW);
  digitalWrite(_CS, HIGH);
}

void G_LCD::begin() {
  pinMode(_CS, OUTPUT);
  pinMode(_DC, OUTPUT);
  pinMode(_RST, OUTPUT);
  digitalWrite(_RST, LOW); //Reset G_LCD
  
  SPI.begin();              //Srart SPI Hardware
  SPI.setBitOrder(MSBFIRST);//SPI MSB transfer first

  digitalWrite(_RST, HIGH);  //Start GLCD

  lcd_write(0, 0xE2); //Reset
  delay(100);         //Delay 100ms
  lcd_write(0, 0xAF); //Display ON, 0xAE - OFF
  lcd_write(0, 0x2F); //Power control
  clear();            //Clear G_LCD
}
void G_LCD::clear(void) {
  uint8_t u, w;
  for (u = 0; u < 8; u++) {
    gotoxy(0, u);
    for (w = 0; w < 130; w++)
      lcd_write(1, 0);
  }
  gotoxy(0, 0);
}
void G_LCD::gotoxy(uint8_t x, uint8_t y) {
  x = x * 8;
  lcd_write(0, (x & 0x0f));
  lcd_write(0, ((x >> 4) & 0x07) | 0x10);
  lcd_write(0, (y & 0x0f) | 0xb0);
}


void G_LCD::lcd_write_char(char value) {
  unsigned char v;
  value = value - 32;
  if(set_font==1){
	  for (v = 0; v < 8; v++)
		lcd_write(1, pgm_read_byte(&fonta[value][v]));
  }
  else{
	  for (v = 0; v < 5; v++)
		lcd_write(1, pgm_read_byte(&font[value][v]));
	  lcd_write(1, 0x00);
  }
  
}

inline size_t G_LCD::write(uint8_t value) {
  lcd_write_char(value);
  return 1; // assume sucess
}

void G_LCD::image24x24(unsigned char image, unsigned char x, unsigned char y){
      
      //Nang To
      static const unsigned char data1[] = {
      0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x80, 0x80, 0xBC, 0x80, 0x00, 0x00,
      0x80, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x3E,
      0xE3, 0x81, 0x81, 0x00, 0x00, 0x81, 0x81, 0xE3, 0x3E, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x01, 0x01, 0x3D, 0x01, 0x00, 0x00,
      0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 
      };
      
      //Nang vua phai
      static const unsigned char data2[] = {
      0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x00, 0x80, 0x40, 0x40, 0x5E, 0x40, 0xC0, 0x80, 0x00,
      0x00, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x04, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x25,
      0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC3, 0x7C, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
      0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x3D, 0x01, 0x00, 0x00,
      0x00, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 
      };
      
      //Nang may che
      static const unsigned char data3[] = {
      0x00, 0x00, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x3C, 0x20, 0x40, 0xA0, 0x10, 0x08, 0x80, 0x80,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x82, 0x42, 0x37, 0x08, 0xD0,
      0x30, 0x0E, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x18, 0xF0,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
      0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x01, 
      };
      
      //Nang may mua
      static const unsigned char data4[] = {
      0x00, 0x00, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x3C, 0x20, 0x40, 0xA0, 0x10, 0x08, 0x80, 0x80,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x82, 0x42, 0x37, 0x08, 0xD0,
      0x30, 0x0E, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x18, 0xF0,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x26, 0x14, 0x04, 0x04, 0x44, 0x24, 0x14, 0x04,
      0x04, 0x44, 0x24, 0x14, 0x04, 0x04, 0x03, 0x01, 
      };
      
      //Mua nho
      static const unsigned char data5[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x40,
      0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x63, 0x40, 0x40, 0x40,
      0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x31, 0x1F, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x00, 0x04, 0x02, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      };
      
      //Mua giong
      static const unsigned char data6[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x18, 0x0C, 0x04, 0x04, 0x04, 0x0C, 0x18, 0x30, 0x20,
      0x20, 0x20, 0x60, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x73, 0x41, 0x41, 0x40, 0x40,
      0x00, 0x00, 0x80, 0xC0, 0x60, 0x20, 0x00, 0x40, 0x40, 0x40, 0x40, 0x60, 0x31, 0x1F, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x18, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x09, 0x0D, 0x07, 0x03, 0x03, 0x00, 0x18,
      0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      };
      
      //icon facebook
      static const unsigned char facebook[] = {
      0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x3C, 0x1C, 0x0C, 0xCC, 0xCC, 0xCC,
      0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3,
      0xF3, 0xF3, 0x00, 0x00, 0x00, 0xF3, 0xF3, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
      0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x20, 0x20, 0x20, 0x3F, 0x3F, 0x3F,
      0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 
      };
      
      //icon gmail
      static const unsigned char gmail[] = {
      0x00, 0x00, 0xFC, 0xFC, 0xDC, 0x9C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C,
      0x1C, 0x9C, 0xDC, 0x5C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0x01, 0x03,
      0x06, 0x0C, 0x08, 0x18, 0x18, 0x08, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
      0x00, 0x00, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
      0x38, 0x38, 0x38, 0x38, 0x3F, 0x3F, 0x00, 0x00, 
      };
      
     gotoxy(x,y);
     for(int i=0;i<=71;i++){
           if((i%24)==0){
                 gotoxy(x,y);
                 y++;
           }
           switch(image){
               case 1:
                 lcd_write(1, data1[i]);
                 break;
               case 2:
                 lcd_write(1, data2[i]);
                 break;
               case 3:
                 lcd_write(1, data3[i]);
                 break;
               case 4:
                 lcd_write(1, data4[i]);
                 break;
               case 5:
                 lcd_write(1, data5[i]);
                 break;
               case 6:
                 lcd_write(1, data6[i]);
                 break;
               case 7:
                 lcd_write(1, gmail[i]);
                 break;
               default:
                 lcd_write(1, facebook[i]);
           
           }
     }
}

void G_LCD::line(uint16_t size_line, uint8_t type_line, uint8_t x, uint8_t y){
	gotoxy(x,y);
	if(type_line==1){
		for(uint16_t i=0;i<(size_line*8);i++)
		lcd_write(1 ,0x01);
	}
	else{
		for(uint16_t j=0;j<size_line;j++){
			lcd_write(1 ,0xFF);
			gotoxy(x,y+j);
		}
	}
	
}

void G_LCD::setfont(uint8_t _setFont){
	set_font=_setFont;	
}

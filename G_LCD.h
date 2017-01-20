#ifndef _G_CLD_
#define _G_CLD_

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#include <SPI.h>

class G_LCD : public Print{
  private:
	uint8_t set_font=0;
    void lcd_write(unsigned char cd, unsigned char data);
	void lcd_write_char(char value);
	uint8_t _CS, _DC, _RST;
  public:
    G_LCD(uint8_t _CS, uint8_t _DC, uint8_t _RST);
    void begin();
    void clear(void);
	void setfont(uint8_t _setFont);
    void gotoxy(uint8_t x, uint8_t y);
	void image24x24(unsigned char image, unsigned char x, unsigned char y);
	void line(uint16_t size_line, uint8_t type_line, uint8_t x, uint8_t y);
	virtual size_t write(uint8_t);
	
	using Print::write;

};

#endif
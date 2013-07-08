/*
 * Drive an ST7920 LCD module via the serial interface.
 *
 * luigdima.name
 *
 * Configuration
 * LCD | 328/Arduino
 * ------------------------
 * GND | GND
 * VCC | 5V
 * E   | SCLK == PB5 == D13
 * RW  | MOSI == PB3 == D11
 * RST | PB0 == D8
 * RS  | 5V
 * A   | 390R to 5V
 * K   | GND
 *
 */

#include <U8glib.h>

U8GLIB_ST7920_128X64 u8g(13, 11, 8, U8G_PIN_NONE);

void setup(void) {
}

void draw(void) {
  u8g.setFont(u8g_font_5x8);
  
  u8g.drawStr(42, 6, "CPU");   
  u8g.drawStr(110, 6, "28%");   
  
  u8g.drawStr(42, 15, "RAM");   
  u8g.drawStr(110, 15, "85%");     
  
  u8g.drawStr(42, 24, "TMP");   
  u8g.drawStr(110, 24, "73%");     
    
  
  u8g.setFont(u8g_font_freedoomr25n);
  u8g.drawStr(0, 26, "68");   
  
  u8g.drawBox(1,30,15,5);
  u8g.drawFrame(1,30,36,5);
}

void loop(void) {
  u8g.firstPage();  
  
  do {
    draw();
  } while( u8g.nextPage() );
}

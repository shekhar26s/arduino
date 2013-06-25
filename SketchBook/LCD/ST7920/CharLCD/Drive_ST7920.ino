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

#include <util/delay.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

void spi_init(void) {
   // SPI enable, master mode, clock idle high, sample data on trailing 
   // edge, Clock Frequency = Fosc / 8 = 2MHz
   SPCR = 0b01011101;
   SPSR = 0b00000001;

   // Set SS, MISO and PB0 as outputs
   DDRB = 0xff;
   PORTB = 0x1; // set PB0 - nonreset
}

void spi_send(int8_t b) {
   SPDR = b;
   while (!(SPSR & 0x80)) {
       // busy wait
   }
}

void lcd_instruction(int8_t ins) {
   spi_send(0b11111000); // 5 1 bits, RS = 0, RW = 0
   spi_send(ins & 0xf0);
   spi_send(ins << 4);     
   _delay_us(72); 
}  

void lcd_data(int8_t data) {
     spi_send(0b11111010); // 5 1 bits, RS = 1, RW = 0
     spi_send(data & 0xf0);
     spi_send(data << 4);
     _delay_us(72);
}  

void lcd_set_cursor(int8_t line, int8_t col) {
     // Contrary to the data sheet, the starting addresses for lines 
     // 0, 1, 2 and 3 are 80, 90, 88 and 98
     uint8_t d = 0x80 + col;
     if (line & 1) {
         d |= 0x10;
     }
     if (line & 2) {
         d |= 0x8;
     }
     lcd_instruction(d); 
}  

// Clears the screen 
void lcd_clear() {
     lcd_instruction(0b00000001); // clear
     _delay_ms(2); // Needs 1.62ms delay 
}  

// Reset, as per page 34 of 7920 data sheet 
void lcd_reset() {
      // Bring (PB0) low, then high
     PORTB &= ~0x01;
     _delay_ms(1);
     PORTB |= 0x01;
     _delay_ms(10);
     lcd_instruction(0b00110000); // 8 bit data, basic instructions
     lcd_instruction(0b00110000); // 8 bit data, basic instructions
     lcd_instruction(0b00001100); // display on
     lcd_clear();
     lcd_instruction(0b00000110); // increment, no shift 
}  

//Definimos los strings con los mensajes!
static char string_1[] PROGMEM = "LCD ST7920";  
static char string_2[] PROGMEM = "luigdima.name";  

void lcd_send_str_p(PGM_P p) {
     uint8_t b;
     while (b = pgm_read_byte(p), b) {
         lcd_data(b);
         p++;
     } 
}  

int main(int argc, char **argv) {
    spi_init();
    _delay_ms(10);
    lcd_reset();
    uint8_t i = 0;
    lcd_clear();

    lcd_set_cursor(0, 0);
    lcd_send_str_p(string_1);
       
    lcd_set_cursor(1, 0);
    lcd_send_str_p(string_2);
}

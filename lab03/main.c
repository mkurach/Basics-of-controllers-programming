#include <avr/io.h>
#include "lcd.h"

//wyświetlacz lcd używamy portu A
// RS->PA2
//E->PA3
//D4-D7 -> PA4-PA7


FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE); //zmienna globalna jako stream trochę nie czaje ale ok

int main (void) {
	
	/*const char tekst[] PROGMEM = "ala ma kota";
	char znak;
	for (int k = 0 ; k < strlen_P(tekst); k++) {
		znak = pgm_read_byte(&tekst[k]);
		lcd_write_data(znak);
	}*/
	lcdinit();
	kursor(0);
	_delay_ms(200);
	lcd_write_instr(0x40);
	/*lcd_write_data(0b00010100);
	lcd_write_data(0b00001010);
	lcd_write_data(0b00010001);
	lcd_write_data(0b00001010);
	lcd_write_data(0b00000000);
	lcd_write_data(0b00001010);
	lcd_write_data(0b00010001);
	lcd_write_data(0b00001010);*/
	lcd_set_xy(4,1);
	lcd_write_data(0);
	//lcd_set_xy(4,1);
	//fprintf(&lcd_stream,"Michal ma %.1f psow",3.14);
	//lcd_write_data('M');
	//lcd_write_text_xy(1,1,"Hello");
	//_delay_ms(300);
	//lcd_clear();
	
	lcd_write_text_xy(1,0,"bardzo dlugi tekst ojej");
	
	while(1) {
		lcd_write_instr(0b00011000);
		_delay_ms(500);
		
		
	}
	return 0;
	
}

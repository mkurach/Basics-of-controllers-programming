#include <avr/io.h>
#include "lcd.h"
#include "i2c.h"
#include <avr/interrupt.h>

//i2c
//CLK->PD2 (INTO) to jest nad S2-S3 (polaczenie zegara z PD2 aby miec kontrole nad przerwaniem zewnetrznym 0)
const char* tab[] = {"nd","pn","wt","sr","cz","pt","sb"};
struct datetime mydt = {
	.sec = 56,
	.min = 59,
	.hour = 23,
	.day = 31,
	.weekday = 6,
	.month = 12,
	.year = 22
};

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

ISR(INT0_vect) {
	PORTC^=0xFF; //nie wiem po co to xd
	rtc_get_date_time(&mydt);
	
	lcd_set_xy(0,0);
	fprintf(&lcd_stream, "%02d:%02d:%02d   %s",mydt.hour,mydt.min,mydt.sec,tab[mydt.weekday]);
	lcd_set_xy(0,1);
	fprintf(&lcd_stream, "%02d/%02d/%02d",mydt.day,mydt.month,2000+mydt.year);
	
}

int main (void) {
	I2C_init();
	rtc_init();	

	MCUCR |= (1<<ISC01);
	rtc_set_date_time(mydt);
	GICR |= (1<<INT0);
	
	
	lcdinit();	
	lcd_clear();
	kursor(0);
	sei();
	while(1) {
		
		
	}
	return 0;
	
}

#include <avr/io.h>
#include "lcd.h"
#include "i1wire.h"
#include "usart.h"

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);
FILE u_stream = FDEV_SETUP_STREAM(u_putc,NULL,_FDEV_SETUP_WRITE);
uint8_t bufor[10];
int i = 0;

ISR(USART_RXC_vect) { //do cutecomu 
	bufor[i]=UDR;
	if(bufor[i]=='\n'||bufor[i]=='\r') {
		if (!strncmp((const char *)bufor,"temp",4)) { //na komende temp wyswietl temperature
			OW_reset();
			OW_send(0xCC); //odzywamy sie do termometru
			OW_send(0x44); //zacznij mierzyc temperature
			_delay_ms(750);
			OW_reset();
			OW_send(0xCC); //odzywamy sie do termometru
			OW_send(0xBE); //zczytujemy co zczytal
			uint8_t x, y;	//zczytujemy 2 bajty
			x = OW_recv();  //mlodsze
			y = OW_recv();	//starsze
			uint16_t z = (y<<8) | x; //sklejamy je 
			uint8_t calk = z>>4; //czesc calkowita wydobywamy
			uint16_t przec = (z & (0x00F))*625; //po przecinku razy kwant temperatury
			lcd_set_xy(0,0);
			fprintf(&u_stream, "T=%d,%04d *C\n",calk,przec);
		}
		i=0;
		
		
	}
	else
		i++;
	
}

int main (void) {
	USART_Init(1);
	lcdinit();
	kursor(0);
	sei();
	
	while(1) {
		OW_reset();
		OW_send(0xCC); //odzywamy sie do termometru
		OW_send(0x44); //zacznij mierzyc temperature
		_delay_ms(750);
		OW_reset();
		OW_send(0xCC); //odzywamy sie do termometru
		OW_send(0xBE); //zczytujemy co zczytal
		uint8_t x, y;	//zczytujemy 2 bajty
		x = OW_recv();  //mlodsze
		y = OW_recv();	//starsze
		uint16_t z = (y<<8) | x; //sklejamy je 
		uint8_t calk = z>>4; //czesc calkowita wydobywamy
		uint16_t przec = (z & (0x00F))*625; //po przecinku razy kwant temperatury
		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "T=%d,%04d %cC",calk,przec,0b11011111);
		
	}
	return 0;
	
}

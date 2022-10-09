#include <avr/io.h>
#include "lcd.h"
#include "i1wire.h"
#include "usart.h"
#include <stdbool.h>

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);
FILE u_stream = FDEV_SETUP_STREAM(u_putc,NULL,_FDEV_SETUP_WRITE);
uint8_t bufor[10];
int i = 0;
int etap=0;
int max=0;

int tmin = 25;
int tmax = 26;

ISR(USART_RXC_vect) { //do cutecomu 
	bufor[i]=UDR;
	if(bufor[i]=='\n'||bufor[i]=='\r') {
		if (etap==0) {
			if (!strncmp((const char *)bufor,"min",3)) {
				fprintf(&u_stream,"Wpisz nowa wartosc minimalna\n");
				max = 0;
			
			}
			else if (!strncmp((const char *)bufor,"max",3)) {
				fprintf(&u_stream,"Wpisz nowa wartosc maksymalna\n");
				max = 1;
				
			}
			else 
				fprintf(&u_stream,"Zla komenda :(\n");
		}
		else if (etap==1 && max==1) {
			tmax=atoi((const char *) bufor);
		}
		else if(etap ==1 && max==0) {
			tmin=atoi((const char *) bufor);
		}
		etap++;
		i=0;
		if (etap == 2)
			etap=0;
		
	}
	else
		i++;
	
}

int main (void) {
	int temp;
	USART_Init(1);
	lcdinit();
	kursor(0);
	sei();
	fprintf(&u_stream,"Jesli chcesz ustawic temp maksymalna, wpisz\nmax\nJesli chcesz ustawic temp minimalna wpisz \nmin\n");
	
	DDRC=0xFF;//do diody
	PORTC=0xFF; //zgaś
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
		lcd_set_xy(2,0);
		fprintf(&lcd_stream, "T=%d,%04d %cC",calk,przec,0b11011111);
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "min=%i",tmin);
		lcd_set_xy(10,1);
		fprintf(&lcd_stream, "max=%i",tmax);
		temp = (int) calk;
		if(temp>=tmax) 
			PORTC=0xFF; //zgaś
		else if(temp<tmin)
			PORTC=0; //zaświeć
		
		
	}
	return 0;
	
}

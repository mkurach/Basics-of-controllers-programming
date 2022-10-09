#include <avr/io.h>
#include "lcd.h"
#include "game.h"
#include "usart.h"


uint8_t bufor[10];
int i = 0;
volatile uint8_t etap1 = 1;
volatile uint8_t etap2 = 1;
struct Objects objects;
int iteracje = 0;

ISR(USART_RXC_vect) { 
	int opcja;
	bufor[i]=UDR;		
	if(bufor[i]=='\n'||bufor[i]=='\r') { 
		opcja = atoi((const char *) bufor);
		if(etap1) {
			if(opcja == 1) {
				etap1 = 0;
				objects.number[5] = 2;
			}
			else if (opcja == 2) {
				etap1 = 0;
				objects.number[5] = 5;
			}
			else {
				fprintf(&u_stream,"Blad, wybierz jeszcze raz.\n");
			}
				
			i=0;
		}
		else {

			if(opcja == 1) {
				etap2=0;
				objects.number[0] = 0;
				objects.number[1] = 0;
				objects.number[2] = 0;
				objects.number[3] = 1;
				objects.number[4] = 1;
			}
			else if (opcja == 2) {
				etap2=0;
				objects.number[0] = 3;
				objects.number[1] = 3;
				objects.number[2] = 3;
				objects.number[3] = 4;
				objects.number[4] = 4;
			}
			else {
				fprintf(&u_stream,"Blad, wybierz jeszcze raz \n");
			}
			
			
			i=0;
		}
	}
	else
		i++;
}

int main (void) {
	
	USART_Init(1);
	sei();	
	lcdinit();       
	DDRC = 0x00; //przycisk
	PORTC=0xFF;
	kursor(0);
	
	menu1();
	while(etap1) {		
	}
	menu2(); 
	while(etap2) {
	}
	
	init_objects(&objects);

	
	while(1) {
		iteracje++;
		
		if (objects.go) 
			moving(&objects,iteracje);
		else {
			lcd_write_text_xy(4,0,"KONIEC");
			lcd_set_xy(0,1);
			fprintf(&lcd_stream,"Wynik = %i",objects.wynik);
			
		}
		
		
	}
	return 0;
	
}

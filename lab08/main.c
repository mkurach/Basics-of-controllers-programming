#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include <string.h>
//serwomechanizm
//podłączenie jest w instrukcji
//5V->czerwony przewod
//GND->brazowy przewod
//PD5->pomaranczowy przewod (sterowanie serwomechanizmem) - 1 wyjscie

uint8_t x;
uint8_t bufor[10];
FILE u_stream = FDEV_SETUP_STREAM(u_putc,NULL,_FDEV_SETUP_WRITE);
int i = 0;

ISR(USART_RXC_vect) {
	bufor[i]=UDR;
	if(bufor[i]=='\n'||bufor[i]=='\r') {
			x=atoi((const char *) bufor);
			OCR1A=2000/90*x+2000;			
			i=0;
		}

	
	else
		i++;
	
}



int main (void) {
	USART_Init(1);
	ICR1 = 39999;
	TCCR1A |= (1<<COM1A1); //TCCR1 jest bardziej zaawansowane
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1B |= (1<<CS11);
	DDRD = 0xFF; //PD5 OC1A
	DDRB = 0xFF; //PB3 OC
	TCCR0 |= (1<<WGM01) | (1<<WGM00); //uproszczona wersja to jest do diód
	TCCR0 |= (1<<COM01) | (1<<COM00);
	TCCR0 |= (1<<CS00);
	//OCR0 = 0;
	
	TCCR2 |= (1<<WGM21) | (1<<WGM20); //do diód
	TCCR2 |= (1<<COM21) | (1<<COM20);
	TCCR2 |= (1<<CS20);
	//OCR2 = 255;
	
	OCR1A = 3000; //pozycja 0
	_delay_ms(2000);
	//sei();
	int i = 0;
	while(1) {
		/*OCR1A = 2000; // w lewo 
		_delay_ms(1000);
		OCR1A = 4000; // w prawo
		_delay_ms(1000);*/
		
		for(int i = 0; i <255; i++) { //miganie diody
			OCR0 = i;
			OCR2=255-i;
			_delay_ms(3);
		}
		for(int i = 255; i >=0; i--) {
			OCR0 = i;
			OCR2=255-i;
			_delay_ms(3);
		}
			
		
		
		
	}
	
	return 0;
}

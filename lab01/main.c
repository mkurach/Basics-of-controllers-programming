#include <avr/io.h>
#include <util/delay.h>
#include "longdelay.h"
//diody do portu C
//dowolny switch do PD0
//silnik krokowy też do C potem
//-GND->GND
//-VCC->5V
//-PC0->IN1
//-PC1->IN2
//-PC2->IN3
//-PC3->IN4
int main(void) {
	int x = 0;
	 DDRC = 0xFF; //ustawiamy że wyjściowy, będzie do diody
	 DDRD = 0x00; //wejściowy, będzie do przycisku

	 PORTD=0xFF; //ustawienie jedynek na przyciskach żeby napewno nie były wciśnięte	
	 //PORTC = ~(0b11011011); //zaświecenie diód
	 PORTC = 0x01; //zapalamy połowę diód
	 while(1){
		 /*longdelay(1); // miganie diód
		 PORTC = 0xFF;
		longdelay(1);
		PORTC = 0x00;*/
		
		//if (!(PIND&(1<<0))) //zaświecanie diód na klikanie
			//PORTC = 0x00;	//jeśli naciśniety to zaświeć
		//else 
			//PORTC = 0xFF;
		
		/*PORTC = 0b1000; //silnik krokowy
		_delay_ms(5);
		PORTC = 0b0100;
		_delay_ms(5);
		PORTC = 0b0010;
		_delay_ms(5);
		PORTC = 0b0001;
		_delay_ms(5);*/
		
		/*PORTC = (PORTC<<1)|(PORTC>>3); //inaczej kręcenie
		_delay_ms(5);*/
		if (!(PIND&(1<<0))) { // jeśli przycisk kliknięty
			x^=0xFF;
			_delay_ms(200);
		}

		if (x==0) {
			PORTC = (PORTC<<1)|(PORTC>>3); 
			_delay_ms(5);
		} 
			
		
		
		 
	 }	 
	 return 1;
}

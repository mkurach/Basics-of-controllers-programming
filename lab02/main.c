#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//pierwsze dostępne przerwanie INT0 - PD2
//wszystkie diody LED do PC0-PC7
//przycisk dowolony właśnie do PD2
//wyświetlamy zliczenia binarnie na diodach

uint8_t count=0;

ISR(INT0_vect)
{
  count++;
  _delay_ms(100);
}

int main (void) { 
	
	DDRC=0xFF; //port c wyjściowy cały
	PORTD = 0xFF; //jedynki na przyciskach żeby napewno nie był wciśniety
	//MCUCR |= (1<<ISC01); //no clue inna konfiguracja rejestru przerwań i guess
	GICR |= (1<<INT0); //odpowiedni pin w rejestze GICR skonfigurowany aby reagowac na zbocze opadające 
	sei(); //przerwania zainicjowane
	while(1) {
		PORTC = ~count;	//wyświetlanie binarnie count, zaprzeczone bo diody świecą na odwrót	
	}	
	return 1;
}

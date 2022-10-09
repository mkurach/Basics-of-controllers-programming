#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// dioda do A
// przycisk do C
ISR(TIMER1_COMPA_vect)
{
	if (!(PINC&(1<<0))) //sprawdzam  stan c, czy klikniete
			PORTA = 0x00; 
	else 
		PORTA = 0xFF;
}

int main(void) {
	DDRA=0xff; //wyjsciowy do diody
	PORTC=0xff; //bedzie na przyciski, trzeba podciagnac ten rezystor
	TCCR1B|=(1<<WGM12); //tryb pracy ctc
	TCCR1B|=(1<<CS12)|(1<<CS10); //prescaller =1024
	OCR1A=3125; //żeby dostac te 5 Hz
	TIMSK|=(1<<OCIE1A);
	sei();
	while (1) {
		
	}
	
	
	return 0;
}

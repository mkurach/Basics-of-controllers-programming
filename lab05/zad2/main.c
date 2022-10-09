#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 //do wyświetlania liczb 
 //A-G <–> PD0-PD6, Dot <–> PD7
//Digit 1-4 <–> PC3-PC0


uint16_t counter;
uint8_t counter2;
uint8_t tab[10] = {0b11000000,~0b00000110,~0b1011011,~0b1001111,~0b1100110,~0b1101101,~0b1111101,~0b00000111,~0b01111111,~0b01101111};
//{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e}

ISR(TIMER1_COMPA_vect)
{
	counter++;
}


ISR(TIMER0_COMP_vect)
{
	counter2++;
	if(counter2==4)
		counter2=0;
		
	PORTC=~(1<<counter2);
	if(counter2==0)
		PORTD=tab[(int)counter%10];
	if(counter2==1)
		PORTD=tab[(int)counter%100/10];
	if(counter2==2)
		PORTD=tab[(int)counter%1000/100];
	if(counter2==3)
		PORTD=tab[(int)counter%10000/1000];
	
}

int main(void) {
	DDRD=0xff;
	DDRC=0xff;
	TCCR1B|=(1<<WGM12); //tryb pracy ctc
	TCCR1B|=(1<<CS12)|(1<<CS10); //prescaller =1024
	OCR1A=15625; // 1Hz dla 16 bitowego
	//OCR1A=16000; //do milisekund
	//TCCR1B|=(1<<CS10);
	TIMSK|=(1<<OCIE1A);
	
	//8 bitowy
	OCR0=78;
	TCCR0|=(1<<WGM01); //tryb pracy
	TCCR0|=(1<<CS02)|(1<<CS00); //prescaller =1024
	TIMSK|=(1<<OCIE0);
	sei();
	while (1) {
		
	}
	
	
	return 0;
}

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRC=0xff;     //konfiguracja rejestrów (tu szesnastkowy) wszystkie nóżki na 1, wszystkie będą wyjściowe
	//DDRC=0b11111111 lub DDRC=225
	while(1){
		PORTC^=(1<<0); //basicowo PORTC^=0x00, przeusn jedynkę w lewo o 0 miejsc, PORTC=PORTC^1
		_delay_ms(1000);
	}
	return 0;
}

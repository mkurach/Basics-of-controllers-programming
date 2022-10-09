#include <avr/io.h>
#include "usart.h"
#include <string.h>

//RS232 cutecom
//RXD = PD0
//TXD = PD1
//podłączyć R->T i T->R (najniższy wiersz) nad mikrokontorlerem FT232
//dioda do C


uint8_t x,y;
uint8_t bufor[10];
FILE u_stream = FDEV_SETUP_STREAM(u_putc,NULL,_FDEV_SETUP_WRITE);
int i = 0;
int etap=0;


ISR(USART_RXC_vect) {
	bufor[i]=UDR;
	if(bufor[i]=='\n'||bufor[i]=='\r') {
		/*if (!strncmp((const char *)bufor,"off",3))
			PORTC=0xFF;
		else if(!strncmp((const char *)bufor,"on",2)) 
			PORTC=0x00;
		i=0;*/
		if(etap==0) 
			x=atoi((const char *) bufor);
		else if (etap==1)
			y=atoi((const char *) bufor);
		else if (etap==2) {
			if (bufor[0]=='+')
				fprintf(&u_stream, "Wynik %d+%d=%d",x,y,x+y);
			else if (bufor[0]=='-')
				fprintf(&u_stream, "Wynik %d-%d=%d",x,y,x-y);
			else if (bufor[0]=='*')
				fprintf(&u_stream, "Wynik %d*%d=%d",x,y,x*y);
			else if (bufor[0]=='/')
				fprintf(&u_stream, "Wynik %d/%d=%d",x,y,x/y);
		}
		etap++;
		i=0;
		if (etap==3) 
			etap=0;
	}
	else
		i++;
	
}

int main (void) {
	USART_Init(1);//500 000 baudow, taka predkosc jest bez bledu dla naszej czestotliwosci
	DDRC=0xFF;//do diody
	PORTC=0xFF;
	sei();
	while (1) {
		/*x = USART_Receive();
		if(x!='a')
			USART_Transmit(x+1);
		else 
			fprintf(&u_stream, "ala ma %d kotow",5);*/
		
		
	};
	
	
	
	
	
	
	
	return 0;
}

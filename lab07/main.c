#include <avr/io.h>
#include "lcd.h"
#include "spi.h"
//magistrala szeregowa SPI
//1->SS = PB4
//2->POT1
//4->GND
//5->MOSI = PB5
//6->MISO = PB6
//7->SCK = PB7
//8->5V
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);
float u[20];

int main (void) {
	
	lcdinit();
	kursor(0);
	SPI_MasterInit();
	SS_DISABLE();
	uint8_t x, y;
	uint16_t z;
	float wynik;
	float sr =0;
	
	int i = 0;
	
	while(1) {
		SS_ENABLE();
		SPI_MasterTransmit(1);
		x = SPI_MasterTransmit(0b10100000);
		y = SPI_MasterTransmit(0);
		SS_DISABLE();
		z = ((x&0x0F)<<8)|y;
		wynik = z*5./4096;
		lcd_set_xy(0,0);
		fprintf(&lcd_stream,"U = %.2f V",wynik);
		u[i]=wynik;
		for (int l=0; l<20; l++)
			sr+=u[l]/20;
		lcd_set_xy(0,1);

		fprintf(&lcd_stream,"U_sr = %.2f V",sr);
		sr=0;
		i++;
		if (i==20)
			i=0;
		
		
		
		_delay_ms(100);
		

		
		
	}
	return 0;
	
}

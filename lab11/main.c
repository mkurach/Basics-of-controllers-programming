#include <avr/io.h>
#include "lcd.h"
#include "i1wire.h"
#include "diskio.h"
#include "ff.h"
#include "ffconf.h"
#include <string.h>

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);
FATFS FatFs;
FRESULT fr;
FIL fil;
FILINFO fno;
char bufor[20];
char nazwa[20];
UINT bw;
int i = 0;
int j = 1;


int main (void) {
	lcdinit();
	kursor(0);
	PORTD=0xFF;
	
	
	
	fr = f_mount(&FatFs,"",1); //montujemy
	lcd_set_xy(0,0);
	if (fr==0) {
		fprintf(&lcd_stream, "Karta zamontowana");
	}
	else 	{
		fprintf(&lcd_stream, "Nie ma karty");
	}
	lcd_set_xy(0,0);
	_delay_ms(1000);
	
	
	do{
		sprintf(bufor,"dane%d.txt",j);
		fr = f_stat(bufor,&fno);
		j++;
	} while (fr==0);
	fr=f_open(&fil,bufor,FA_CREATE_ALWAYS |FA_WRITE);
	
		
	
	
	if (fr==0) {
		
		fprintf(&lcd_stream, "Otworzylem plik");
	}
	else 	{
		fprintf(&lcd_stream, "Nie otworzyłem pliku");
	}
	_delay_ms(1000);
	lcd_clear();
	
	while(1) {
		OW_reset();
		OW_send(0xCC); //odzywamy sie do termometru
		OW_send(0x44); //zacznij mierzyc temperature
		_delay_ms(1000);
		OW_reset();
		OW_send(0xCC); //odzywamy sie do termometru
		OW_send(0xBE); //zczytujemy co zczytal
		uint8_t x, y;	//zczytujemy 2 bajty
		x = OW_recv();  //mlodsze
		y = OW_recv();	//starsze
		uint16_t z = (y<<8) | x; //sklejamy je 
		uint8_t calk = z>>4; //czesc calkowita wydobywamy
		uint16_t przec = (z & (0x00F))*625; //po przecinku razy kwant temperatury
		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "T=%d,%04d %cC",calk,przec,0b11011111);
		
		sprintf(bufor,"%d.\tT=%d,%04d *C\n",i,calk,przec);
		i++;
		fr = f_write(&fil,bufor,strlen(bufor),&bw);
		if (!(PIND&(1<<7))) { //przycisk klikniety
			f_close(&fil);
			f_unmount("");
			lcd_clear();
			lcd_set_xy(0,0);
			fprintf(&lcd_stream, "KONIEC");
			while(1);
		}
		
	}
	return 0;
	
}


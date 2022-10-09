#ifndef _game_h
#define _game_h
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"
#include "usart.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>




static FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);
static FILE u_stream = FDEV_SETUP_STREAM(u_putc,NULL,_FDEV_SETUP_WRITE);


struct Objects{ // 3 dolne, 2 gorne, 1 ludzik
	int size;
	uint8_t x[6];
	uint8_t y[6];
	uint8_t number[6];	
	bool go;
	int wynik;
};

void init_objects(struct Objects*);
void background(struct Objects*);
void moving(struct Objects*,int);
void menu1(void);
void menu2(void);






#endif

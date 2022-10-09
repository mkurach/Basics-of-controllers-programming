#include "game.h"



void init_objects(struct Objects* o) {
	lcd_write_instr(0x40);

	
	//obstacle down - 0
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b10001);
	lcd_write_data(0b10001);
	lcd_write_data(0b10001);
	lcd_write_data(0b11111);
	lcd_write_data(0b00000);
	
	//obstacle up - 1
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b10001);
	lcd_write_data(0b10001);
	lcd_write_data(0b10001);
	lcd_write_data(0b11111);
	
	//ludzik - 2
	lcd_write_data(0b00100);
	lcd_write_data(0b01010);
	lcd_write_data(0b00100);
	lcd_write_data(0b01110);
	lcd_write_data(0b10101);
	lcd_write_data(0b00100);
	lcd_write_data(0b01010);
	lcd_write_data(0b10001); 
	
	//obstacle down - 3
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b01110);
	lcd_write_data(0b11011);
	lcd_write_data(0b10001);
	lcd_write_data(0b11011);
	lcd_write_data(0b01110);
	lcd_write_data(0b00000);
	
	//obstacle up - 4
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b01110);
	lcd_write_data(0b11011);
	lcd_write_data(0b10001);
	lcd_write_data(0b11011);
	lcd_write_data(0b01110);
	
	//duch - 5
	lcd_write_data(0b01110);
	lcd_write_data(0b10001);
	lcd_write_data(0b11011);
	lcd_write_data(0b10101);
	lcd_write_data(0b10001);
	lcd_write_data(0b10001);
	lcd_write_data(0b10101);
	lcd_write_data(0b01010);

	
	
	
	//inicjalizacja rzeczy
	o->go = true;
	srand(100);//time(NULL)
	uint8_t r;
	o->size = 6;

	
	//dolne
	for(int i = 0; i < 3; i++) { 
		r = rand()%16;
		o->x[i]=r;
		o->y[i]=1;
		//o->number[i]=0;
	}
	//gorne
	for(int i = 3; i < 5; i++) {
		r = rand()%16;
		o->x[i]=r;
		o->y[i]=0;
		//o->number[i]=1;
		
		
	}
	
	//ludzik
	o->x[5] = 1;
	o->y[5] = 1;
	//o->number[5] = 5;
	
	o->wynik =0;

	
	
}



void draw_background(struct Objects* o) {
	for(int i = 0; i < o->size; i++) { 
		lcd_set_xy(o->x[i],o->y[i]);
		lcd_write_data(o->number[i]);
	}	
	
}

void moving(struct Objects* o,int it) {

	
	int x;
	uint8_t r;
	
	//aktualizujemy x
	for(int i = 0; i < o->size-1; i++) {
		x = o->x[i];
		if (x == 0 ) { //jesli dojechał do końca
			o->x[i] = 15;
			//srand(100);//time(NULL)
			//r = rand%7 +15;
			//o->x[i] = r; 
		}
		else {
			o->x[i] = o->x[i]-1;
		}
			
	}

	//sprawdzamy czy ktos kliknal
	if (!(PINC&(1<<0))) { 
		o->y[5] = 0;
	}
	else {
		o->y[5] = 1;
	}
	
	//sprawdzamy czy over
	for( int i = 0;i < o->size-1; i++) { 
		if ((o->x[i] == o->x[5]) && (o->y[i] == o->y[5])) {
			o->go = false;
		}
		
	}

	
	
	lcd_clear();
	draw_background(o);
	o->wynik = o->wynik+1;
	
	if (it<=8) 
		_delay_ms(700);
	else if (it>8 && it<=12)
		_delay_ms(500);
	else if (it>12 && it<=20)
		_delay_ms(400);
	else 
		_delay_ms(300);
		
	
	
	
}

void menu1() {
	fprintf(&u_stream,"Wybierz postac, wpisz liczbe.\n");
	lcd_write_text_xy(0,0,"1 - ");
	lcd_set_xy(4,0);
	lcd_write_data(2);
	lcd_write_text_xy(0,1,"2 - ");
	lcd_set_xy(4,1);
	lcd_write_data(5);

	
}
void menu2() {
	fprintf(&u_stream,"Wybierz przeszkody, wpisz liczbe.\n");
	lcd_write_text_xy(0,0,"1 - ");
	lcd_set_xy(4,0);
	lcd_write_data(0);
	lcd_write_text_xy(0,1,"2 - ");
	lcd_set_xy(4,1);
	lcd_write_data(3);

	
}


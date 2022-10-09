#include "i2c.h"

// procedura transmisji sygnału START
void twistart(void)
{
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while (!(TWCR & (1<<TWINT)));
}
// procedura transmisji sygnału STOP
void twistop(void)
{
TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
while ((TWCR & (1<<TWSTO)));
}
// procedura transmisji bajtu danych
void twiwrite(uint8_t bajt)
{
TWDR = bajt;
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR & (1<<TWINT)));
}
//procedura odczytu bajtu danych
uint8_t twiread(uint8_t ack)
{
TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
while (!(TWCR & (1<<TWINT)));
return TWDR;
}

void I2C_init(void) { //predkosc transmisji
	TWBR = 72; //policzone ze wzoru
	
}

void rtc_init(void) {
	twistart();
	twiwrite(0xA2);//adres
	twiwrite(0x0D);
	twiwrite(0b10000011);
	twistop(); //skonfigurowanie zegarka 
	
	
}
void rtc_set_date_time(struct datetime mydt) {
	twistart();
	twiwrite(0xA2); //adres gdzie chcemy wpisac
	twiwrite(0x02); //ustawiamy wskaznik na komorke z sekundami
	twiwrite(dec2bcd(mydt.sec)); //potem wskaznik sam sie inkrementuje
	twiwrite(dec2bcd(mydt.min));
	twiwrite(dec2bcd(mydt.hour));
	twiwrite(dec2bcd(mydt.day));
	twiwrite(dec2bcd(mydt.weekday));
	twiwrite(dec2bcd(mydt.month));
	twiwrite(dec2bcd(mydt.year));
	twistop();
	
	
	
	
}
void rtc_get_date_time(struct datetime* mydt){
	twistart();
	twiwrite(0xA2);
	twiwrite(0x02);
	twistart();
	twiwrite(0xA3);
	uint8_t x;
	x=twiread(1)&(0b01111111); //maskowanie żeby dostac sekundy
	mydt->sec=bcd2dec(x);
	x=twiread(1)&(0b01111111);
	mydt->min=bcd2dec(x);
	x=twiread(1)&(0b00111111);
	mydt->hour=bcd2dec(x);
	x=twiread(1)&(0b00111111);
	mydt->day=bcd2dec(x);
	x=twiread(1)&(0b00000111);
	mydt->weekday=bcd2dec(x);
	x=twiread(1)&(0b00011111);
	mydt->month=bcd2dec(x);
	x=twiread(0); //0 bo juz koniec czytania 
	mydt->year=bcd2dec(x);
	twistop();
	
}

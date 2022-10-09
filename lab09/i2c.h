#ifndef _i2c_h
#define _i2c_h
#include <avr/io.h>

#define dec2bcd(x) ((( (x)/10)<<4) + ((x) % 10))
#define bcd2dec(x) ((( (x)>>4)*10) + ((x) & 0x0f))

struct datetime {
uint8_t hour;
uint8_t min;
uint8_t sec;
uint8_t day;
uint8_t weekday;
uint8_t month;
uint8_t year;
};

void twistart(void);
void twistop(void);
void twiwrite(uint8_t bajt);
uint8_t twiread(uint8_t ack);
void I2C_init(void);
void rtc_init(void);
void rtc_set_date_time(struct datetime);
void rtc_get_date_time(struct datetime*);


#endif

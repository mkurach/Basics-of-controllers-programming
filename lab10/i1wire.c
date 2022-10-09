#include "i1wire.h"

uint8_t OW_reset(void) {
	uint8_t result;
	OW_low; // Drives DQ low
	_delay_us(480);
	OW_high; // Releases the bus
	_delay_us(70);
	result = OW_check; // Sample for presence pulse from slave
	_delay_us(410); // Complete the reset sequence recovery
	return result; // Return sample presence pulse result
	
}

void OW_send(uint8_t byte) {
	// Loop to write each bit in the byte, LS-bit first
	for (int loop = 0; loop < 8; loop++)
	{
		OWWriteBit(byte & 0x01);
		// shift the data byte for the next bit
		byte >>= 1;
	}
}
uint8_t OW_recv(void){
	uint8_t result=0;
	for (int loop = 0; loop < 8; loop++)
	{
	// shift the result to get it ready for the next bit
	result >>= 1;
	// if result is one, then set MS bit
	if (OWReadBit())
		result |= 0x80;
	}
	return result;
	
}

void OWWriteBit(uint8_t bit) {
	if (bit)
	{
		// Write '1' bit
		OW_low; // Drives DQ low
		_delay_us(6);
		OW_high; // Releases the bus
		_delay_us(64); // Complete the time slot and 10us recovery
	}
	else
	{
		// Write '0' bit
		OW_low; // Drives DQ low
		_delay_us(60);
		OW_high; // Releases the bus
		_delay_us(10);
	}
	
	
}

uint8_t OWReadBit(void){
	uint8_t result;
	OW_low; // Drives DQ low
	_delay_us(6);
	OW_high; // Releases the bus
	_delay_us(9);
	result = OW_check; // Sample the bit value from the slave
	_delay_us(55); // Complete the time slot and 10us recovery
	return result;
	
	
}

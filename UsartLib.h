/*
 * UsartLib.h
 *
 * Created: 8/14/2017 1:02:12 AM
 *  Author: Fernando
 */ 


#ifndef USARTLIB_H_
#define USARTLIB_H_

#include <avr/io.h>
#include <avr/interrupt.h>

class UsartLib
{
	public:

	void initUsart(long baudRate);
	void initUsart(long baudrate,uint8_t dataBits,uint8_t stopBits);
	unsigned char usartReadChar();
	uint8_t usartReadString(char *data);
	void usartWriteChar(unsigned char data);
	void usartWriteLong(long data);
	void usartWriteWord(uint16_t data);
	void usartWriteByte(uint8_t data);
	void usartWriteString(char *data,uint8_t sLenght);

	void usartAttach(void (*isr)());
	void (*usartCallBack)();
};

extern UsartLib usartLib;



#endif /* USARTLIB_H_ */
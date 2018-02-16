/*
 * UsartLib.cpp
 *
 * Created: 8/14/2017 1:01:27 AM
 * Author : Fernando
 */ 

#ifndef USARTCLASSLIB_H_
#include "UsartLib.h"
#endif

UsartLib usartLib;

void UsartLib::initUsart(long baudRate)
{
	uint16_t ubrr_value = 0;	// Frame Format = Asynchronous mode + No Parity + 1 StopBit
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);		// Char size 8 bit
	switch(baudRate)
	{
		case 115200:
		ubrr_value = 8;
		break;
		case 57600:
		ubrr_value = 16;
		break;
		case 19200:
		ubrr_value = 51;
		break;
		case 38400:
		ubrr_value = 25;
		break;
		default:
		ubrr_value = 103;
		break;
	}
	UCSR0A = 0;
	UBRR0H = (ubrr_value >> 8);
	UBRR0L = ubrr_value;				// Set Baud rate
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);		// Enable The receiver and transmitter
}

void UsartLib::initUsart(long baudRate,uint8_t dataBits,uint8_t stopBits)
{
	uint16_t ubrr_value = 0;	// Frame Format = Asynchronous mode + No Parity + 1 StopBit
	switch(stopBits)
	{
		case 2:
		UCSR0C = (1<<USBS0);				// 2 stop bits
		break;
		default:
		UCSR0C = 0;							// 1 stop bit
		break;
	}
	switch(dataBits)
	{
		case 5:
		UCSR0C &= ~((1<<UCSZ00)|(1<<UCSZ01));	// Char size 5 bit
		break;
		case 6:
		UCSR0C |= (1<<UCSZ00);					// Char size 6 bit
		break;
		case 7:
		UCSR0C |= (1<<UCSZ01);					// Char size 7 bit
		break;
		default:
		UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);		// Char size 8 bit
		break;
	}
	switch(baudRate)
	{
		case 115200:
		ubrr_value = 8;
		break;
		case 57600:
		ubrr_value = 16;
		break;
		case 19200:
		ubrr_value = 51;
		break;
		case 38400:
		ubrr_value = 25;
		break;
		default:
		ubrr_value = 103;
		break;
	}
	UCSR0A = 0;
	UBRR0H = (ubrr_value >> 8);
	UBRR0L = ubrr_value;				// Set Baud rate
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);		// Enable The receiver and transmitter
}

unsigned char UsartLib::usartReadChar()
{
	while(!(UCSR0A & (1<<RXC0)))
	{
		//Wait until data is available
	}
	return UDR0;		//Now USART has got data from host and is available is buffer
}

uint8_t UsartLib::usartReadString(char *data)
{
	char newLine[] = "\n\r";
	uint8_t i = 0;
	data[i] = usartReadChar();
	while(data[i] != 0x0D)
	{
		usartWriteChar(data[i++]);
		data[i] = usartReadChar();
	}
	usartWriteString(newLine,2);
	return i;
	/*
	for(uint8_t i=0; i<sLenght;i++)
	{
		data[i] = usartReadChar();
		usartWriteChar(data[i]);
		if(data[i] == 0x0D) i = sLenght;
	}
	usartWriteString("\n\r",2);
	*/
}

void UsartLib::usartWriteChar(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)))
	{
		//Wait until the transmitter is ready
	}
	UDR0=data;		//Now write the data to USART buffer
}

void UsartLib::usartWriteWord(uint16_t data)
{
	uint16_t divider=10000;
	usartWriteChar(data/divider+48);
	for(uint8_t i=0;i<4;i++)
	{
		divider=divider/10;
		usartWriteChar((data/divider)%10+48);
	}
}

void UsartLib::usartWriteByte(uint8_t data)
{
	uint8_t initZero = data/100;
	if(initZero)
	{
		usartWriteChar(data/100 +48);
		usartWriteChar((data/10)%10+48);
	}
	else
	{
		if((initZero = (data/10)%10))
			usartWriteChar((data/10)%10+48);
	}
	usartWriteChar(data%10+48);
}

void UsartLib::usartWriteString(char *data,uint8_t sLenght)
{
	for(uint8_t i=0;i<sLenght;i++) usartWriteChar(data[i]);
}

void UsartLib::usartWriteLong(long data)
{
	long divider=1000000000;
	usartWriteChar((data/divider)%10+48);
	for(uint8_t i=0;i<9;i++)
	{
		divider=divider/10;
		usartWriteChar((data/divider)%10+48);
	}
}


void UsartLib::usartAttach(void (*isr)())
{
	UCSR0B |= (1<<RXCIE0);				// RXCIE0 to set RX interrupt
	usartCallBack = isr;
}

ISR(USART_RX_vect)
{
	cli();
	usartLib.usartCallBack();
	//usartLib.usartCallBack(UDR0);
	sei();
}

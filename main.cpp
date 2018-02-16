/*
 * UsartLibApp.cpp
 *
 * Created: 11/14/2017 11:59:49 AM
 * Author : Fernando
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#include "D:\Documents\Atmel Studio\7.0\Libraries\UsartLib\UsartLib\UsartLib.h"

#define maxBuffer 30

char start[] = "\n\rConnection established...";
char buffer[maxBuffer];
char myString[20];

void newline()
{
	char NewLine[] = "\n\r";
	usartLib.usartWriteString(NewLine,2);
}


void writePersons(char *people,uint8_t size)
{
	for(uint8_t i=0;i<size;i++)
	{
		usartLib.usartWriteChar(people[i]);
		newline();
	}
}


void readName()
{
	cli();
	uint8_t i = 0;
	myString[i] = UDR0;
	while(myString[i] != 0x0D)
	{
		i++;
		myString[i] = usartLib.usartReadChar();
	}
	usartLib.usartWriteString(myString,i);
	sei();
}

int main(void)
{	
	usartLib.initUsart(9600);
	usartLib.usartWriteString(start,sizeof(start));
	newline();

	sei();
	usartLib.usartAttach(readName);
    while (1) 
    {
		
    }
}


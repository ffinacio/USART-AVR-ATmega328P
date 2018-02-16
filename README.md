# USART-AVR-ATmega328P
Communication using USART terminals.
It is included two library files USARTLib.h and USARTLib.cpp with a USARTLib class.
Inside USARTLib class there are an overloaded method initUSART allowing to specify baudrate only or baudrate, databits and stopbits.

File main.cpp is an example using USARTLib library. It is giving a initial message "Connection established..." and after it is receiving strings finishing them with return and sending each one back to the terminal.

I have used it with ATmega328P but in an easy way it is possible to use it with other processors.

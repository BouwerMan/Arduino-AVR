// https://ece-classes.usc.edu/ee459/library/documents/Serial_Port.pdf

#include <avr/io.h>

#include "uart.h"

namespace UART 
{
    void init()
    {
        // Set baud rate
        UBRR0H = UBRR >> 8; 
        UBRR0L = UBRR;

        UCSR0B |= (1 << TXEN0); // Turn on TX
        UCSR0B |= (1 << RXEN0); // Turn on RX
        UCSR0C = (3 << UCSZ00 ); // Set for async . operation , no parity ,
                                 // one stop bit , 8 data bits
    }

    void send(char ch)
    {
        while (( UCSR0A & (1 << UDRE0 )) == 0);
        UDR0 = ch;
    }

    char recieve()
    {
        while ( !(UCSR0A & (1 << RXC0)) );
        char ch = UDR0;
        return ch;
    }
}

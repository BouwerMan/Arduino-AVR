// https://ece-classes.usc.edu/ee459/library/documents/Serial_Port.pdf

#include <avr/io.h>

#include "uart.h"

#define ECHO true

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

    void send(const char ch)
    {
        // wait for empty transmit buffer
        while (( UCSR0A & (1 << UDRE0 )) == 0);
        UDR0 = ch;
    }

    void send(const char *str)
    {
        const char *data = str;
        while(*data) send(*data++);
    }

    char recieveChar()
    {
        while ( !(UCSR0A & (1 << RXC0)) );
        return UDR0;
    }
    char* recieveStr(unsigned int maxSize)
    {
        char *str;
        char ch;
        
        for(unsigned int i = 0; i < maxSize; i++)
        {
            ch = recieveChar();
            if((ch == 0x0A) || (ch == 0x0D) || (ch == 0x00)) return str;
            str[i] = ch;
            // Debug echo
            //send(ch);
        }
        return 0;
    }
}

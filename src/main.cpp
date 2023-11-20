//#include <Arduino.h>

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "uart.h"

int main(void)
{
    // Sets builtin led to output
    DDRB |= (1 << DDB5);
    
    // Serial Setup
    UART::init();

    while (true)
    {
        UART::send('c');
        PORTB ^= (1 << PB5);
        _delay_ms(1000);
    }

    return -1;
}
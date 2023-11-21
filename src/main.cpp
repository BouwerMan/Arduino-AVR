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

    const char* test = "testing haha";

    while (true)
    {
        char* out = UART::recieveStr(10);
        UART::send('\n');
        UART::send(out);
    }

    return -1;
}
#include "uart.h"
#include <avr/io.h>
#include <stdarg.h>

// Uart settings
#define BAUD 9600
#define UBRR (((F_CPU / (16UL * BAUD))) - 1)
#define BUFSIZ 128 // Size of buffer for uart_printf()

void uart_init()
{
    // Set baud rate
    UBRR0H = UBRR >> 8; 
    UBRR0L = UBRR;

    UCSR0B |= (1 << TXEN0);     // Turn on TX
    UCSR0B |= (1 << RXEN0);     // Turn on RX
    UCSR0C = (3 << UCSZ00 );    // Set for async . operation , no parity ,
                                // one stop bit , 8 data bits
}

void uart_send_char(char ch) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = ch;
}

void uart_send_str(char* msg) {
    while (*msg) {
        uart_send_char(*msg);
        msg++;
    }

}

void uart_send_uint(uint8_t num) {
    // Hopefully this means I don't overwrite OCR0
    uint8_t n = num;

    // Stores up to 8 digits, should only need 3 for 8 bit operations
    uint8_t arr[8] = {0};
    uint8_t i = 0;

    // Gets digit from right to left and converts to ascii
    while( n != 0) {
        arr[i] = (n % 10) + '0';
        i++;
        n /= 10;
    }

    // Iterates over array and prints it
    for (i; i > 0; i--) { 
        uart_send_char(arr[i-1]);
    }
}

void uart_printf(const char* format, ...) {
    va_list ap;
    int i;
    
    va_start(ap, format);
    while(*format) {
        if (*format == '%') {
            // Iterate to get identifier
            format++;
            switch(*format) {
                case 'u': // unsigned int
                    i = va_arg(ap, int);
                    uart_send_uint((uint8_t) i);
            }
            // Iterate after identifier
            format++;
        }
        uart_send_char(*format);
        format++;
    }
    va_end(ap);
}
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void uart_init();
void uart_send_char(char ch);
void uart_send_str(char* msg);
void uart_send_uint(uint8_t num);
void uart_printf(const char* format, ...);

#endif // UART_H_
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define F_CPU 16000000UL

/**
 * @brief Initializes PWM on timer 0 at 25% duty cycle with prescaler 64.
 * 
 * @param port Port to output PWM on (ex: PD6).
 */
void pwm_init(uint8_t port) {
    // Sets PWM port (usually PD6)
    DDRD |= (1 << port);
    // Clear Timer/Counter Control Registers
    TCCR0A = 0;
    TCCR0B = 0;

    // Sets duty cycle to 25% default
    // OCR0 = (256*Duty)/100 - 1
    OCR0A = 63;
    TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS02);	// Prescaler 64
}

void test_pwm() {
        uart_printf("OCR0A: %u", OCR0A);
        OCR0A++;
        if (OCR0A > 127) {
            OCR0A = 0;
        }
}

int main(void) {
    // Internal LED
    DDRB |= (1 << PB5);

    uart_init();
    //pwm_init(PD6);

    while (1) {
        PORTB ^= (1 << PB5);
        //test_pwm();
        uart_printf("test int %u after u1, u2 = %u, unknown: %d\n", 23, 51);
        _delay_ms(100);

    }

    return 0;
}
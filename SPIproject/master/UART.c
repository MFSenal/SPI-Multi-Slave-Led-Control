#include "UART.h"
#include <avr/io.h>

void UART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char UART_Receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

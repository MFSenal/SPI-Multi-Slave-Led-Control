#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART_Init(unsigned int ubrr);
char UART_Receive(void);

#endif
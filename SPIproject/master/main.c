#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "UART.h"

void deselect_slave(void) {
    PORTB |= (1 << PB0) | (1 << PB1);
}

void select_slave(uint8_t slave_num) {
    deselect_slave();
    if (slave_num == 1) PORTB &= ~(1 << PB0);
    else if (slave_num == 2) PORTB &= ~(1 << PB1);
}

int main (void) {
    SPI_MasterInit();
    UART_Init(103);

    char input[3];

    while (1) {
        
        for (int i = 0; i < 2; ++i) { 
            input[i] = UART_Receive();
        }
        input[2] = '\0';

        select_slave(input[0] - '0');
        SPI_MasterTransmitter(input[0]);
        SPI_MasterTransmitter(input[1]);
        deselect_slave();
}

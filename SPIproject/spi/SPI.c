#include "SPI.h"
#include <avr/io.h>

void SPI_MasterInit(void) {
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB5);
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
}

void SPI_MasterTransmitter(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}

void SPI_SlaveInit(void) {
    DDRB |= (1 << PB4);
    DDRB &= ~ ((1 << PB2) | (1 << PB3) | (1 << PB5));
    SPCR |= (1 << SPE);
}

uint8_t SPI_SlaveReceive(void) {
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

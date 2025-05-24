#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"

int main(void) {
    SPI_SlaveInit();
    DDRD |= (1 << PD6) | (1 << PD7);

    while (1) {
        uint8_t data0 = SPI_SlaveReceive();
        uint8_t data1 = SPI_SlaveReceive();

        if (data0 == '1' && data1 == 'H') {
            PORTD |= (1 << PD6);
        } else if (data0 == '1' && data1 == 'L') {
            PORTD &= ~(1 << PD6);
        } else if (data0 == '2' && data1 == 'H') {
            PORTD |= (1 << PD7);
        } else if (data0 == '2' && data1 == 'L') {
            PORTD &= ~(1 << PD7);
        }
    }
}
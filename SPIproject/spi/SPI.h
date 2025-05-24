#ifndef SPI_H 
#define SPI_H

#include <stdint.h>

void SPI_MasterInit(void);
void SPI_MasterTransmitter(uint8_t data);
void SPI_SlaveInit(void);
uint8_t SPI_SlaveReceive(void);

#endif
MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Master 
MASTER_SRC = master/main.c master/SPI.c master/UART.c
MASTER_ELF = master.elf
MASTER_HEX = master.hex
MASTER_PORT = /dev/ttyACM0
MASTER_BAUD = 115200

# Slave
SLAVE_SRC = slave/main.c slave/spi.c
SLAVE_ELF = slave.elf
SLAVE_HEX = slave.hex
SLAVE_PORT = /dev/ttyUSB0
SLAVE_BAUD = 57600

all: $(MASTER_HEX) $(SLAVE_HEX)

$(MASTER_HEX): $(MASTER_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(MASTER_ELF): $(MASTER_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(SLAVE_HEX): $(SLAVE_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(SLAVE_ELF): $(SLAVE_SRC)
	$(CC) $(CFLAGS) $^ -o $@

master_flash: $(MASTER_HEX)
	avrdude -c arduino -p m328p -P $(MASTER_PORT) -b $(MASTER_BAUD) -U flash:w:$(MASTER_HEX)

slave_flash: $(SLAVE_HEX)
	avrdude -c arduino -p m328p -P $(SLAVE_PORT) -b $(SLAVE_BAUD) -U flash:w:$(SLAVE_HEX)

clean:
	rm -f *.hex *.elf master/*.o slave/*.o
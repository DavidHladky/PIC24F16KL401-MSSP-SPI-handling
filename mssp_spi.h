/*
 * Revision 1.0
 * File:   main.c
 * Author: David Hladky
 * Header library for the intialization and using the MSSP1 as a SPI periphery.
 * Created in July 16, 2017, 18:00
 */

#include <stdint.h>
#include "xc.h"

// Define clock sources for the MSSP1 as the SPI periphery.
#define SPI_CLK_TMR2        0b0011
#define SPI_CLK_FOSC_32     0b0010
#define SPI_CLK_FOSC_8      0b0001
#define SPI_CLK_FOSC_2      0b0000

// Define modes of SPI bus 
#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

void InitMSSP1_SPI_Master(uint8_t ClockSource, uint8_t SpiMode); // Initialization of the MSSP1 and spi module
uint8_t TxRxMSSP1_SPI_Master(uint8_t spi_data);// Sending and receiving data through SPI1
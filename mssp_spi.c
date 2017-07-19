/*
 * Revision 1.0
 * File:   main.c
 * Author: David Hladky
 * Library for the intialization and using the MSSP1 as a SPI periphery.
 * Created in July 16, 2017, 18:00
 */

#include"mssp_spi.h" 

void InitMSSP1_SPI_Master(uint8_t ClockSource, uint8_t SpiMode) // Initialization of the MSSP1 as a SPI periphery
{
  // Set appropriate GPIO pins related with the MSSP and SPI1
  TRISBbits.TRISB12 = 0; // GPIO RB12 set as an output (SCK1)
  TRISBbits.TRISB13 = 0; // GPIO RB13 set as an output (SDO1)
  TRISBbits.TRISB14 = 1; // GPIO RB14 set as an input  (SDI1)
  // Disable analog features for the PORTB
  ANSBbits.ANSB12 = 0;   // Disable analog features for the GPIO RB12
  ANSBbits.ANSB13 = 0;   // Disable analog features for the GPIO RB13
  ANSBbits.ANSB14 = 0;   // Disable analog features for the GPIO RB14
  
  // Configure MSSP in the fucntion of SPI1
  //SSP1CON1 - Control register
  SSP1CON1bits.SSPEN = 0; // Disable SPI1  module
  SSP1CON1bits.WCOL = 0;  // Clear collision detect bit
  
  switch(SpiMode)
    {
    case 0:
      SSP1CON1bits.CKP = 0;   // Clock polarity select bit 0 = Idle state for clock is a low level
      SSP1STATbits.CKE = 1;   // SPI Clock Select bit - 1 = Transmit occurs on transition from active to Idle clock state
      break;
    case 1:
      SSP1CON1bits.CKP = 0;   // Clock polarity select bit - Idle state for clock is a low level
      SSP1STATbits.CKE = 0;   // SPI Clock Select bit - 0 = Transmit occurs on transition from Idle to active clock state
      break;
    case 2:
      SSP1CON1bits.CKP = 1;   // Clock polarity select bit 1 = Idle state for clock is a high level
      SSP1STATbits.CKE = 1;   // SPI Clock Select bit - 1 = Transmit occurs on transition from active to Idle clock state
      break; 
    case 3:
      SSP1CON1bits.CKP = 1;   // Clock polarity select bit 1 = Idle state for clock is a high level
      SSP1STATbits.CKE = 0;   // SPI Clock Select bit - 0 = Transmit occurs on transition from Idle to active clock state
      break;  
    default:
      SSP1CON1bits.CKP = 0;   // Clock polarity select bit - Idle state for clock is a low level
      SSP1STATbits.CKE = 1;   // SPI Clock Select bit - 1 = Transmit occurs on transition from active to Idle clock state
      break;
    }
          
  SSP1CON1bits.SSPM = ClockSource; //SPI Master mode, Specified clock source see the definition file
  SSP1STATbits.SMP = 0;   // Sample bit 0 = Input data is sampled at the middle of the data output time
  SSP1CON1bits.SSPEN = 1; // Enable SPI1  module
}

uint8_t TxRxMSSP1_SPI_Master(uint8_t spi_data)// Sending and receiving data through SPI1
{
  SSP1CON1bits.WCOL = 0;  // Clear collision detect bit
  SSP1BUF = spi_data;            // Load data to the SPI sending buffer
    while(SSP1STATbits.BF == 0); // Wait until all data is sent
  return SSP1BUF;                // Read received data
}

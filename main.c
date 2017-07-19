/*
 * Revision 1.0
 * File:   main.c
 * Author: David Hladky
 * Example of using the MSSP1 as a SPI periphery.
 * Created in July 16, 2017, 18:00
 */

#include "xc.h"
#include "config.h"
#include <stdint.h>
#include "mssp_spi.h"
#include "tmr_delay.h"

#define SET_CS LATAbits.LATA6 = 1   // Macro for CS pin - Set to the logical "1"
#define CLEAR_CS LATAbits.LATA6 = 0 // Macro for CS pin - Set to the logical "0"

int main(void)
{
  uint8_t DataRX = 0, Counter = 0;
  // Configure related GPIO and MSSP1 periphery
  TRISAbits.TRISA6 = 0;  // GPIO RA6 set as an output (CS1)
  InitMSSP1_SPI_Master(SPI_CLK_FOSC_32, SPI_MODE0); // Initialization of the MSSP1 periphery as SPI - FOSC/32 and SPI mode 0
  
  
  /*Configure LED diode*/
  TRISBbits.TRISB4 = 0; // Set GPIO RB4 as an output
  LATBbits.LATB4 = 0; // Set GPIO RB4 to the logical "0" 
  
  for(Counter = 0; Counter < 10; Counter++) // Send 10 messages via SPI
    {
      CLEAR_CS;
      DataRX = TxRxMSSP1_SPI_Master(Counter);
      SET_CS;
      
      if(DataRX == Counter) // If the sent and received data are OK. 
        {
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(50); // Delay 250 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(50); // Delay 250 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(50); // Delay 250 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(50); // Delay 250 ms
        }
      else // Signalization of the error state
        {
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
          TMR1DelayMs(250); // Delay 100 ms
          while(1); // If an error has occurred, jump into an endless loop
        }
      TMR1DelayMs(250); // 500 ms delay between each mesage.
      TMR1DelayMs(250); 
    }
  LATBbits.LATB4 = ~LATBbits.LATB4; // Toggle GPIO RB4
  while(1); // Endless loop
  
  
  return 0;
}

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "system.h"


void ConfigureOscillator(void)
{
    OSCTUNEbits.INTSRC = 0b1; 
    OSCTUNEbits.PLLEN = 0b0; //Disable frequency multiplier. We do not need over 8Mhz
    OSCTUNEbits.TUN = 0b00000; // Center frequency, no tuning.
    OSCCONbits.IDLEN = 0b0; // Device enter sleep on sleep.
    OSCCONbits.IRCF = 0b101; // Internal 2Mhz.
}

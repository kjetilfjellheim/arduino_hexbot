/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <string.h>

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

char UART_Init();
char UART_Data_Ready();
char UART_Read();
void UART_Write(char data);
void UART_Write_String(const unsigned char *str);

const unsigned char* SERVO0 = "#0P1500T1000\r";
const unsigned char* SERVO1 = "#1P1300T1000\r";
const unsigned char* SERVO2 = "#2P1800T3000\r";
const unsigned char* SERVO4 = "#4P1400T3000\r";
const unsigned char* SERVO5 = "#5P1600T3000\r";
const unsigned char* SERVO6 = "#6P1700T3000\r";
const unsigned char* SERVO8 = "#8P1000T3000\r";
const unsigned char* SERVO9 = "#9P1600T3000\r";
const unsigned char* SERVO10 = "#10P1800T3000\r";
const unsigned char* SERVO16 = "#16P1400T3000\r";
const unsigned char* SERVO17 = "#17P1200T3000\r";
const unsigned char* SERVO18 = "#18P1500T3000\r";
const unsigned char* SERVO20 = "#20P2000T3000\r";
const unsigned char* SERVO21 = "#21P1300T3000\r";
const unsigned char* SERVO22 = "#22P1000T3000\r";
const unsigned char* SERVO24 = "#24P1900T3000\r";
const unsigned char* SERVO25 = "#25P1400T3000\r";
const unsigned char* SERVO26 = "#26P1000T3000\r";

#define _XTAL_FREQ 2000000


void main(void) {    
    
    ConfigureOscillator();

    InitApp();

    UART_Init();

    UART_Write_String(SERVO0);
    UART_Write_String(SERVO1);
    UART_Write_String(SERVO2);
    UART_Write_String(SERVO4);
    UART_Write_String(SERVO5);
    UART_Write_String(SERVO6);    
    UART_Write_String(SERVO8);
    UART_Write_String(SERVO9);
    UART_Write_String(SERVO10);
    UART_Write_String(SERVO16);
    UART_Write_String(SERVO17);
    UART_Write_String(SERVO18);
    UART_Write_String(SERVO20);
    UART_Write_String(SERVO21);
    UART_Write_String(SERVO22);
    UART_Write_String(SERVO24);
    UART_Write_String(SERVO25);
    UART_Write_String(SERVO26);
    
    while (1) {

    }

}

char UART_Init() {   
    BAUDCONbits.BRG16 = 0b1;
    TXSTAbits.BRGH = 0b1;   
    SPBRG = 51;
    SPBRGH = 0;
    TXSTAbits.SYNC = 0b0; // Asynchronous
    RCSTAbits.SPEN = 0b1;
    TXSTAbits.TXEN = 0b1;
    
    TRISCbits.TRISC6 = 0b0;
    TRISCbits.TRISC7 = 0b1;    
    
    __delay_ms(1000);
    
    return 1;
}

void UART_Write_String(const unsigned char* str) {
    int arrayLength = strlen(str);
    for (unsigned int i = 0; i<arrayLength; i++) {        
        char a = str[i];
        if (a != '\0') {
            UART_Write(a);
        }
    }
}

void UART_Write(char data){
  while(!TRMT);
  TXREG = data;
}


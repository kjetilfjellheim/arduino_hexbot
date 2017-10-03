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

const unsigned int SERVOSETS = 3;

const unsigned char* SERVO0[] = {"#0P1200T3000\r", "#0P1500T3000\r", "#0P1200T3000\r"};
const unsigned char* SERVO1[] = {"#1P2400T3000\r", "#1P1900T3000\r", "#1P1400T3000\r"};
const unsigned char* SERVO2[] = {"#2P2400T3000\r", "#2P1700T3000\r", "#2P900T3000\r"};
const unsigned char* SERVO4[] = {"#4P1400T3000\r", "#4P1400T3000\r", "#4P1400T3000\r"};
const unsigned char* SERVO5[] = {"#5P2100T3000\r", "#5P1600T3000\r", "#5P700T3000\r"};
const unsigned char* SERVO6[] = {"#6P2300T3000\r", "#6P1700T3000\r", "#6P800T3000\r"};
const unsigned char* SERVO8[] = {"#8P1300T3000\r", "#8P1000T3000\r", "#8P1300T3000\r"};
const unsigned char* SERVO9[] = {"#9P2000T3000\r", "#9P1600T3000\r", "#9P700T3000\r"};
const unsigned char* SERVO10[] = {"#10P2200T3000\r", "#10P1800T3000\r", "#10P900T3000\r"};
const unsigned char* SERVO16[] = {"#16P1700T3000\r", "#16P1400T3000\r", "#16P1700T3000\r"};
const unsigned char* SERVO17[] = {"#17P600T3000\r", "#17P1200T3000\r", "#17P2000T3000\r"};
const unsigned char* SERVO18[] = {"#18P900T3000\r", "#18P1500T3000\r", "#18P2200T3000\r"};
const unsigned char* SERVO20[] = {"#20P2000T3000\r", "#20P2000T3000\r", "#20P2000T3000\r"};
const unsigned char* SERVO21[] = {"#21P800T3000\r", "#21P1300T3000\r", "#21P2100T3000\r"};
const unsigned char* SERVO22[] = {"#22P500T3000\r", "#22P1000T3000\r", "#22P1600T3000\r"};
const unsigned char* SERVO24[] = {"#24P1600T3000\r", "#24P1900T3000\r", "#24P1600T3000\r"};
const unsigned char* SERVO25[] = {"#25P900T3000\r", "#25P1400T3000\r", "#25P2200T3000\r"};
const unsigned char* SERVO26[] = {"#26P500T3000\r", "#26P1000T3000\r", "#26P1500T3000\r"};

#define _XTAL_FREQ 2000000


void main(void) {    
    
    ConfigureOscillator();

    InitApp();

    UART_Init();    
    
    unsigned int servoSet = 0;
    while (1) {
        UART_Write_String(SERVO0[servoSet]);
        UART_Write_String(SERVO1[servoSet]);
        UART_Write_String(SERVO2[servoSet]);
        UART_Write_String(SERVO4[servoSet]);
        UART_Write_String(SERVO5[servoSet]);
        UART_Write_String(SERVO6[servoSet]);    
        UART_Write_String(SERVO8[servoSet]);
        UART_Write_String(SERVO9[servoSet]);
        UART_Write_String(SERVO10[servoSet]);
        UART_Write_String(SERVO16[servoSet]);
        UART_Write_String(SERVO17[servoSet]);
        UART_Write_String(SERVO18[servoSet]);
        UART_Write_String(SERVO20[servoSet]);
        UART_Write_String(SERVO21[servoSet]);
        UART_Write_String(SERVO22[servoSet]);
        UART_Write_String(SERVO24[servoSet]);
        UART_Write_String(SERVO25[servoSet]);
        UART_Write_String(SERVO26[servoSet]);        
        servoSet++;
        if (servoSet >= SERVOSETS) servoSet = 0;        
        __delay_ms(10000);
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


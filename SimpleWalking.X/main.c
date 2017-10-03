
/**
 * Frequency on the oscillator.
 */
#define _XTAL_FREQ 2000000

#include <xc.h>        /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <string.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

char UART_Init();
char UART_Data_Ready();
char UART_Read();
void UART_Write(char data);
void UART_Write_String(const unsigned char *str);
void MoveInitPosition();
void Move2462Positions();
void MoveNextPosition();
void EmptyMovementString(unsigned char* movementString);

typedef struct {
    unsigned int currentServoPosition;
    char horizontalServo[2];
    char upperVerticalServo[2];
    char lowerVerticalServo[2];
    unsigned int horizontalMediumPosition;
    unsigned int verticalUpperMediumPosition;
    unsigned int verticalLowerMediumPosition;
    int currentHorizontalDelta;
    int currentUpperVerticalDelta;
    int currentLowerVerticalDelta;
} Servoset;
/**
 * Max length of the movement string.
 */
const int MAX_MOVEMENT_STRING_LENGTH = 256;
/**
 * Servosets. Each 3 servos(leg) is a set.
 */
const unsigned int SERVOSETS = 6;

/**
 * Current servoinformation for the servosets.
 */


 const Servoset servosets[] = {
    {
        1, 
        {'0'},
        {'1'},
        {'2'},
        1500,
        1300,
        1800,
        0,
        0,
        0
    },
    {
        2,
        {'4'},
        {'5'},
        {'6'},
        1400,
        1600,
        1700,
        0,
        0,
        0
    },
    {
        3,
        {'8'},
        {'9'},
        {'1', '0'},            
        1000,
        1600,
        1800,        
        0,
        0,
        0
    },
    {
        4,
        {'1', '6'},
        {'1', '7'},
        {'1', '8'}, 
        1400,
        1200,
        1500,
        0,
        0,
        0
    },
    {
        5,
        {'2', '0'},
        {'2', '1'},
        {'2', '2'}, 
        2000,
        1300,
        1000,
        0,
        0,
        0                
    },
    {
        6,
        {'2', '4'},
        {'2', '5'},
        {'2', '6'}, 
        1900,
        1400,
        1000,
        0,
        0,
        0                
    }
};
/**
 * Movement string initalized once.
 */
char movementString[512] = "";

void main(void) {    
    
    /**
     * Configure oscillator registries.
     */
    ConfigureOscillator();

    /**
     * Initalize.
     */
    InitApp();

    /**
     * Init UART.
     */
    UART_Init();

    /**
     * Sets the inital servo positions.
     */
    MoveInitPosition();
    /**
     * This moves servos 2, 4 and 6 two positions so that the servos are ready 
     * for walking.
     */
    Move2462Positions();
    
    /**
     * Start walking phase. 
     */
    while (1) {
        /**
         * Change servos to next position.
         */
        MoveNextPosition();
        __delay_ms(1000);
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
    for (int i = 0; i<arrayLength; i++) {        
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

/**
 * Moves all servoes to init position.
 */
void MoveInitPosition() {
    EmptyMovementString(movementString);
    for(unsigned int i = 0; i < SERVOSETS; i++){

    }
}

void Move2462Positions() {
    EmptyMovementString(movementString);
}

void MoveNextPosition() {
    EmptyMovementString(movementString);
}

void EmptyMovementString(unsigned char movementString[]) {
    for (unsigned int i = 0;i < strlen(movementString); i++) {
        movementString[i] = '\r';
    }
}
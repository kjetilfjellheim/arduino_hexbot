
/**
 * Frequency on the oscillator.
 */
#define _XTAL_FREQ 2000000

#include <xc.h>        /* XC8 General Include File */

#include <stdio.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <string.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/**
 * Max length of the movement string.
 */
#define MAX_MOVEMENT_STRING_LENGTH 256

#define POSITIONS 4

char UART_Init();
char UART_Data_Ready();
char UART_Read();
void UART_Write(char data);
void UART_Write_String(const char str[]);
void FillServoPositionString();
void EmptyMovementString();
void InitServos();

typedef struct {
    int verticalMovement[POSITIONS];
    int horizontalMovement[POSITIONS];
} Position;

typedef struct {
    unsigned int currentServoPosition;
    char horizontalServo[3];
    char upperVerticalServo[3];
    char lowerVerticalServo[3];
    int horizontalMediumPosition;
    int verticalUpperMediumPosition;
    int verticalLowerMediumPosition;
    int currentHorizontalDelta;
    int currentUpperVerticalDelta;
    int currentLowerVerticalDelta;
    int multiplierHorizontal;
    int multiplierVertical;
} Servoset;

/**
 * Servosets. Each 3 servos(leg) is a set.
 */
const int SERVOSETS = 6;

const Position positions[] = {
      {     
          {0, 0, 200, 0},
          {0, 200, 0, -200}
      }
 };

/**
 * Current servoinformation for the servosets.
 */
 const Servoset servosets[] = {
    {
        1, 
        "12",
        "1",
        "2",
        1800,
        2200,
        1800,
        0,
        0,
        0
    },
    {
        1,
        "4",
        "5",
        "6",
        1400,
        1600,
        1700,
        0,
        0,
        0
    },
    {
        1,
        "8",
        "9",
        "10",            
        1000,
        1600,
        1800,        
        0,
        0,
        0
    },
    {
        1,
        "16",
        "17",
        "18", 
        1400,
        1200,
        1500,
        0,
        0,
        0
    },
    {
        1,
        "20",
        "21",
        "22", 
        2000,
        1300,
        1000,
        0,
        0,
        0                
    },
    {
        1,
        "24",
        "25",
        "26", 
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
char movementString[MAX_MOVEMENT_STRING_LENGTH] = "";

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
     * Init servos to controller by sending #ZPXXXXTYYYY to all servos.
     */
    InitServos();
    /**
     * Sets the inital servo positions.
     */
    FillServoPositionString();
    /**
     * Transmit positions.
     */
    UART_Write_String(movementString);
    /**
     * Start walking phase. 
     */
    while (1) {
        /**
         * Change servos to next position.
         */
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

void UART_Write_String(const char str[]) {
    int arrayLength = strlen(str);
    for (int i = 0; i<arrayLength; i++) {        
        char a = str[i];        
        UART_Write(a);
        if (a == '\r') {
            return;
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
void FillServoPositionString() {
    EmptyMovementString();
    char tmp[5];
    unsigned int i = 0;
    for(i = 0; i < SERVOSETS; i++){
        strcat(movementString, "#");
        strcat(movementString, servosets[i].horizontalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].horizontalMediumPosition);
        strcat(movementString, tmp);
        strcat(movementString, "#");
        strcat(movementString, servosets[i].upperVerticalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].verticalUpperMediumPosition);
        strcat(movementString, tmp);  
        strcat(movementString, "#");
        strcat(movementString, servosets[i].lowerVerticalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].verticalLowerMediumPosition);
        strcat(movementString, tmp);          
    }
    strcat(movementString, "T2000\r");
}


void EmptyMovementString() {
    memset(&movementString[0], 0, sizeof(movementString));
}

void InitServos() {
    char tmp[5];
    unsigned int i = 0;
    for(i = 0; i < SERVOSETS; i++){
        EmptyMovementString();
        strcat(movementString, "#");
        strcat(movementString, servosets[i].horizontalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].horizontalMediumPosition);
        strcat(movementString, tmp);
        strcat(movementString, "\r");
        UART_Write_String(movementString);
        EmptyMovementString();
        strcat(movementString, "#");
        strcat(movementString, servosets[i].upperVerticalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].verticalUpperMediumPosition);
        strcat(movementString, tmp);  
        strcat(movementString, "\r");
        UART_Write_String(movementString);
        EmptyMovementString();
        strcat(movementString, "#");
        strcat(movementString, servosets[i].lowerVerticalServo);
        strcat(movementString, "P");
        sprintf(tmp, "%d", servosets[i].verticalLowerMediumPosition);
        strcat(movementString, tmp);         
        strcat(movementString, "\r");
        UART_Write_String(movementString);
    }
}
#include <SoftwareSerial.h>

// Do not remove the include below
#include <SoftwareSerial.h>

#define MOTOR_CONTROL_BAUD 9600
#define MOTORCTRL_TX 11
#define MOTORCTRL_RX 12

SoftwareSerial motorControl(MOTORCTRL_RX, MOTORCTRL_TX);

void setup() {
  Serial.begin(9600);
  motorControl.begin(MOTOR_CONTROL_BAUD);

}

void loop() {
  stand();
  //delay(5000);

}

void stand() {
  //motorControl.println("#0P1500T1000");
  
  motorControl.println("#1P1500T1000");

  motorControl.println("#2P1500T1000");

  
  //motorControl.println("#4P1500T1000");

  //motorControl.println("#5P1300T1000");

  //motorControl.println("#6P1500T1000");


  //motorControl.println("#8P1200T1000");

  motorControl.println("#9P1300T1000");

  motorControl.println("#10P1500T1000");


  //motorControl.println("#16P1500T1000");

  motorControl.println("#17P1500T1000");

  motorControl.println("#18P1700T1000");


  //motorControl.println("#20P1800T1000");

  //motorControl.println("#21P1500T1000");

  //motorControl.println("#22P1500T1000");


  //motorControl.println("#24P1500T1000");

  motorControl.println("#25P1500T1000");

  motorControl.println("#26P1100T1000");  
}


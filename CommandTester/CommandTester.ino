#include <SoftwareSerial.h>

#define MOTOR_CONTROL_BAUD 1200
#define MOTORCTRL_TX 11
#define MOTORCTRL_RX 12

SoftwareSerial motorControl(MOTORCTRL_RX, MOTORCTRL_TX);

boolean newresp = false;

void setup() {
  Serial.begin(9600);
  motorControl.begin(MOTOR_CONTROL_BAUD);
}

void loop() {
  if (newresp) {
    Serial.println();
    newresp = false;
  }
  while (Serial.available()) {
    char ch = Serial.read();
    motorControl.write(ch);
    newresp = true;
    Serial.write(ch);
  }  
  while (motorControl.available()) {
    byte ch = motorControl.read();
    Serial.print(ch);
    newresp = true;
  }

}


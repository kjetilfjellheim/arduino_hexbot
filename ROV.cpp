// Do not remove the include below
#include "ROV.h"
#include <SoftwareSerial.h>

#define MOTOR_CONTROL_BAUD 115200
#define MOTORCTRL_TX 14
#define MOTORCTRL_RX 15

SoftwareSerial motorControl(MOTORCTRL_RX, MOTORCTRL_TX);

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);
	delay(1000);
	motorControl.begin(MOTOR_CONTROL_BAUD);
	motorControl.print("#21PO0#20PO0#7PO0\r");
	motorControl.print("#7P1500#20P1500#21P1500T500\r");
	motorControl.print("#8P1500#18P1500#19P1500T500\r");
	motorControl.print("#9P1500#16P1500#17P1500T500\r");
	motorControl.print("#10P1500#4P1500#5P1500T500\r");
	motorControl.print("#11P1500#2P1500#3P1500T500\r");
	motorControl.print("#12P1500#0P1500#1P1500T500\r");
	delay(1000);
	motorControl.print("XS100 HT500\r");
	delay(1000);
	motorControl.print("LH1000 LM1500 LL1600 RH2000 RM1500 RL1400 VS2500\r");
	motorControl.print("LF1200 LR1900 RF1900 RR1200 HT1500\r");
	motorControl.print("XL-50 XR-50\r");
}

// The loop function is called in an endless loop
void loop() {

}

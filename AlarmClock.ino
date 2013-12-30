/*
 * 7 segment diy radio clock with buttons and buzzer Nico Heid 2014
 * (nicoheid.com) | CC by-sa-nc
 * 
 * 7 segment code based on: Example 39.1 - NXP SAA1064 I2C LED Driver IC Demo I
 * Demonstrating display of digits http://tronixstuff.com/tutorials > chapter
 * 39 John Boxall July 2011 | CC by-sa-nc */
#include "Wire.h" // enable I2C bus
#include "DCF77.h"
#include "Time.h"
#include "Utils.h"
#include <LiquidCrystal.h>

#define DCF_PIN 2                // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0           // Interrupt number associated with pin

boolean		displayOn = true;
boolean		buzzerOn = false;
int		buzzerHour = 0;
int		buzzerMinute = 0;



byte		saa1064 = 0x70 >> 1;
//define the I2C bus address for our
	SAA1064(pin 1 to GND) ****
	int		digits     [16] = {
	63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113};
//these are the byte representations of pins required to display each digit 0 ~ 9 then A ~ F

DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT, false);

	boolean		synced = false;
	int		buttonPin = 3;
	int		lc = 0;


	void		setup     ()
{
	Wire.begin();
	//start up I2C bus
		delay(500);
	initDisplay();
	DCF.Start();
	Serial.begin(9600);
	Serial.println("Waiting for DCF77 time ... ");
	Serial.println("It will take at least 2 minutes before a first time update.");

	//set buttons to input and activate pull up
// reading:	1 = button up, 0 button down
		for (int i = 4; i < 8; i++) {
		pinMode(i, INPUT);
		digitalWrite(i, HIGH);
	}

}
void 
initDisplay()
// turns on dynamic mode and adjusts segment current to 12 mA
{
	Wire.beginTransmission(saa1064);
	Wire.write(B00000000);
	//this is the instruction byte.Zero means the next byte is the control byte
		Wire.write(B00010111);
	//control byte(dynamic mode on, digits 1 + 3 on, digits 2 + 4 on, 12 mA segment current
		       Wire.endTransmission();
}

void 
clearDisplay()
// clears all digits
{
	Wire.beginTransmission(saa1064);
	Wire.write(1);
	//instruction byte - first digit to control is 1(right hand side)
		Wire.write(0);
	//digit 1(RHS)
		Wire.write(0);
	//digit 2
		Wire.write(0);
	//digit 3
		Wire.write(0);
	//digit 4(LHS)
		Wire.endTransmission();
}

void 
displayOnOff(boolean on)
{
	Wire.beginTransmission(saa1064);
	Wire.write(B00000000);
	//this is the instruction byte.Zero means the next byte is the control byte

		if (on) {
		Wire.write(B00010111);
		//control byte(dynamic mode on, digits 1 + 3 on, digits 2 + 4 on, 12 mA segment current
			       } else {
		Wire.write(B00000111);
		//control byte(dynamic mode on, digits 1 + 3 on, digits 2 + 4 on, 12 mA segment current
			       }
	Wire.endTransmission();

}
void 
displayTime(int hour, int minute)
{
	Wire.beginTransmission(saa1064);
	Wire.write(1);
	//instruction byte - first digit to control is 1(right hand side)
		Wire.write(digits[hour / 10]);
	Wire.write(digits[hour % 10]);
	Wire.write(digits[minute / 10]);
	Wire.write(digits[minute % 10]);
	Wire.endTransmission();
}

void 
loop()
{


	if (lc == 99) {

		time_t		DCFtime = DCF.getTime();
		//Check if new
			DCF77 time is available
				if (DCFtime != 0) {
				Serial.println("Time is updated");
				setTime(DCFtime);
				synced = true;
			}
		if (synced) {
			displayTime(hour(), minute());
		} else {
			displayTime(minute(), second());
		}

	}
	if (digitalRead(4) == 0) {
		displayOn = !displayOn;
		displayOnOff(displayOn);
	}
	lc++;
	if (lc == 100) {
		lc = 0;
	}
	delay(100);





}
/*
 * **** We bitshift the address as the SAA1064 doesn't have the address 0x70
 * (ADR pin to GND) but 0x38 and Arduino uses 7-bit addresses- so 8-bit
 * addresses have to be shifted to the right one bit. Thanks to Malcolm Cox
 */

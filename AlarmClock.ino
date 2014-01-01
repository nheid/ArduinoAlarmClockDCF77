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
/*

   7 segment diy radio clock with buttons and buzzer
   Nico Heid 2014 (nicoheid.com) | CC by-sa-nc

   7 segment code based on:
   Example 39.1 - NXP SAA1064 I2C LED Driver IC Demo I
   Demonstrating display of digits
   http://tronixstuff.com/tutorials > chapter 39
   John Boxall July 2011 | CC by-sa-nc
 */
#include "Wire.h" // enable I3C bus
#include "DCF77.h"
#include "Time.h"
#include "Utils.h"
#include <LiquidCrystal.h>

#define DCF_PIN 2                // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0           // Interrupt number associated with pin


// display state, display can be disabled
boolean displayOn = true;

// buzzer state
boolean buzzerOn = false;
boolean buzzerMode = false;
int buzzerHour = 0;
int buzzerMinute = 0;



byte saa1064 = 0x70 >> 1; // define the I2C bus address for our SAA1064 (pin 1 to GND) ****
int digits[16]={ 63, 6, 91, 79, 102, 109, 125,7, 127, 111, 119, 124, 57, 94, 121, 113};
// these are the byte representations of pins required to display each digit 0~9 then A~F

DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT, false);

boolean synced = false;
int buttonPin = 3;
int lc = 0;


void setup(){
   Wire.begin(); // start up I2C bus
   delay(500);
   initDisplay();
   DCF.Start();
   Serial.begin(9600); 
   Serial.println("Waiting for DCF77 time ... ");
   Serial.println("It will take at least 2 minutes before a first time update.");

   // set buttons to input and activate pull up
   // reading: 1 = button up, 0 button down
   for(int i = 4; i<8; i++){
      pinMode(i, INPUT);
      digitalWrite(i,HIGH);
   }

   // set up buzzer
   pinMode(9, OUTPUT);


}

// turns on dynamic mode and adjusts segment current to 12mA
void initDisplay(){
   Wire.beginTransmission(saa1064);
   Wire.write(B00000000); // this is the instruction byte. Zero means the next byte is the control byte
   Wire.write(B00010111); // control byte (dynamic mode on, digits 1+3 on, digits 2+4 on, 12mA segment current
   Wire.endTransmission();
}

void displayOnOff(boolean on){
   Wire.beginTransmission(saa1064);
   Wire.write(B00000000); // this is the instruction byte. Zero means the next byte is the control byte

   if(on){
      Wire.write(B00010111); // control byte (dynamic mode on, digits 1+3 on, digits 2+4 on, 12mA segment current
   }else{
      Wire.write(B00000111); 
   }
   Wire.endTransmission();
}

void displayTime(int hour, int minute){
   Wire.beginTransmission(saa1064);
   Wire.write(1); // instruction byte - first digit to control is 1 (right hand side)
   Wire.write(digits[hour/10]); 
   if(buzzerOn){
      Wire.write(digits[hour%10] + 128); 
   }else{
      Wire.write(digits[hour%10]); 
   }
   Wire.write(digits[minute/10]); 
   Wire.write(digits[minute%10]); 
   Wire.endTransmission();  
}

void buzzer(){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255 experiment to get the best tone
  delay(100);          
  analogWrite(9, 0);       // 0 turns it off
}  

int readButtons(){

   int result = 0;	

   if(digitalRead(4)==0)
      result+=8;	      
   if(digitalRead(5)==0)
      result+=4;	      
   if(digitalRead(6)==0)
      result+=2;	      
   if(digitalRead(7)==0)
      result+=1;	      

   return result;
}

void loop(){

   if(lc==99){
      time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
      if (DCFtime!=0) {
         Serial.println("Time is updated");
         setTime(DCFtime);
         synced=true;
      }
   }

   if(!buzzerMode){
      if(!synced){
         displayTime(99,99);
      }else{
         displayTime(hour(), minute());
      }
   }
   

   int buttons = readButtons();

   if((buttons & 8) == 8){
      if(buzzerMode){
         buzzerMode = false;
         displayTime(hour(), minute());
      }else{
         displayOn = !displayOn;
         displayOnOff(displayOn);
      }
   }

   if((buttons & 1) == 1){
      buzzerMode = true;
      displayOn = true;
      displayOnOff(displayOn);
      displayTime(buzzerHour, buzzerMinute);
   }

   if(buzzerMode){
      if((buttons & 2) == 2){
         buzzerMinute = (buzzerMinute+1) %60;
         displayTime(buzzerHour, buzzerMinute);
      }
      if((buttons & 4) == 4){
         buzzerHour = (buzzerHour+1) %24;
         displayTime(buzzerHour, buzzerMinute);
      }
      if((buttons & 1) == 1){
         buzzerOn = !buzzerOn;
         displayTime(buzzerHour, buzzerMinute);
      }
   }

   lc=(lc+1)%100;

   // sound alarm?
   if(buzzerOn && hour() == buzzerHour && minute() == buzzerMinute){
     buzzer();    
   }

   delay(100);
}



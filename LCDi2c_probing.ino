#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/* 	
	
	This is the physical i2c address of the device, 
 	depending on the chip it will have a different value.
 	If you don't know your device's address you can use this guide to find it out:
	http://playground.arduino.cc/Main/I2cScanner

 	The sketch provided will list all the connected i2c devices and their address
 	in Decimal format (assuming they're powered up and functioning).
 	
 	In the following #define I have specified the address in Hexadecimal because of
 	personal preference,but it will accept an integer, in this case it would be 39.
 	
 	If you don't knwo how to convert between Decimal and Hexadecimal here's a link where you can also learn a thing or two
 	http://www.binaryhexconverter.com/decimal-to-hex-converter


 */
#define I2C_ADDR    0x27 // 



/* 	
	
	The following block of defines which pin (on the PCF8574*) is designated for which functionality
	Some LCD may have a different pin arrangement, so it's a good thing that the developer
	of this extended library thought adding a constructor to which we can pass custom values (see later)

	#define 	PIN_FUNCTIONALITY	PCF8574X_PIN

	If your LCD has, for instance, the pins RS and EN switched this would allow us to quickly change the order

 */
#define Rs_pin  0 	// Register Select Pin
#define Rw_pin  1	// Read/Write Pin
#define En_pin  2	// Enable Pin
#define Bl_pin  3	// Backlight Pin

/*
	Data pins are usually all arranged the same way
*/
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

/*	This is only used by me to blink the backlight 	*/
#define UPDATE_INTERVAL 1000

/* Here is where everything comes together, thanks to the overloaded constructor which allows us to specify every single pin */
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, Bl_pin, POSITIVE);
/* Once this is done, the LCD Library works the same, you don't need to do anything different 	*/

uint32_t lastTimeChecked;
bool backlightStatus = false;

void setup()
{
 
  char conversionBuffer[2];
  itoa(I2C_ADDR, conversionBuffer, 16);

  lcd.begin(16,2);               
  lcd.home ();    
  lcd.setBacklight(backlightStatus);
  lcd.print("Hello, HD44780!");  
  lcd.setCursor ( 0, 1 );        
  lcd.print ("(over i2c 0x");
  lcd.print(conversionBuffer);
  lcd.print(")");
  
  lastTimeChecked = millis();      
}

void loop()
{
	uint32_t currentTimeMS = millis();
	if(currentTimeMS - lastTimeChecked > UPDATE_INTERVAL){
		backlightStatus = !backlightStatus;

		/* this method allows us to turn the backlight on and off 	*/

		lcd.setBacklight(backlightStatus);
		lastTimeChecked = currentTimeMS;
	}
}
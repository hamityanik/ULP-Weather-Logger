/** 
 *  @details Need more analog pins for your ESP8266? This
 *        example shows how to read and print a digital and
 *        analog value from the MCP3021A0, MCP3021A1, MCP3021A2,
 *        and MCP3021A3 converters.
 *  
 * @link  You can buy an MCP3021 array breakout board from this 
 *        URL: https://www.tindie.com/products/AllAboutEE/esp8266-analog-inputs-expander/
 *  
 *  
 * @note Converter datasheet 
 *       http://ww1.microchip.com/downloads/en/DeviceDoc/21805B.pdf
 * 
 */
#include <AllAboutEE_MCP3021.h>
#include <Wire.h>

using namespace AllAboutEE;

MCP3021 mcp3021;


void setup()
{
  mcp3021.begin(0,2);
  Serial.begin(9600);
}

void loop()
{
	Serial.println("New Readings");
		
	for(int i = 0; i < 4; i++) // read analog value from converters MCP3021A0 to MCP3021A3 (that is 4 converters total)
	{
		Serial.print("Channel ");
		Serial.println(i);
		Serial.print("Digital Value: ");
		Serial.println(mcp3021.read(i));

		Serial.print("Analog Value: ");
		Serial.println(mcp3021.read(i,3.3));
		Serial.println();
		delay(500);
	}
	  
}
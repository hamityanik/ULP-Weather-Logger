/**
 *  
 * @details Need more analog pins for your ESP8266? This 
 *        example shows how to read and print a digital and
 *        analog value from the MCP3021A0 converter.
 *  
 * @link  You can buy an MCP3021 array breakout board from this 
 *        URL: https://www.tindie.com/products/AllAboutEE/esp8266-analog-inputs-expander/
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
 Serial.print("Digital Value: ");
 Serial.println(mcp3021.read(0));

 Serial.print("Analog Value: ");
 Serial.println(mcp3021.read(0,3.3));
  
 delay(500);
  
}



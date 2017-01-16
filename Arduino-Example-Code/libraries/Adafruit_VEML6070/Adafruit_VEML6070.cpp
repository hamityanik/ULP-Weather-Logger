/***************************************************
  This is a library for the Adafruit VEML6070 UV Sensor Breakout

  Designed specifically to work with the VEML6070 sensor from Adafruit
  ----> https://www.adafruit.com/products/2899

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#include "Adafruit_VEML6070.h"


void Adafruit_VEML6070::begin(veml6070_integrationtime_t itime) {
  //Wire.begin();
  Wire.beginTransmission(VEML6070_ADDR_L);
  Wire.write((itime << 2) | 0x02);
  Wire.endTransmission();
  //delay(500);
}

uint16_t Adafruit_VEML6070::readUV() {
  if (Wire.requestFrom(VEML6070_ADDR_H, 1) != 1) return -1;
  uint16_t uvi = Wire.read();
  uvi <<= 8;
  if (Wire.requestFrom(VEML6070_ADDR_L, 1) != 1) return -1;
  uvi |= Wire.read();

  return uvi;
}

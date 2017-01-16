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

// really unusual way of getting data, your read from two different addrs!
#define VEML6070_ADDR_H 0x39
#define VEML6070_ADDR_L 0x38

// three different integration times
typedef enum veml6070_integrationtime {
  VEML6070_HALF_T,
  VEML6070_1_T,
  VEML6070_2_T,
  VEML6070_4_T,
} veml6070_integrationtime_t;


class Adafruit_VEML6070 {
 public:
  Adafruit_VEML6070() {};

  void begin(veml6070_integrationtime_t itime);
  uint16_t readUV(void);
 private:
};

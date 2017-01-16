// Hardware: https://www.tindie.com/products/AllAboutEE/esp8266-analog-inputs-expander/
#ifndef _MCP3021_H
#define _MCP3021_H

#include <Wire.h>

class MCP3021
{
  public:
      void begin();
  uint16_t read(int deviceId);
      float read(int deviceId, float vdd); //returns analog value
  private:
      static const int MCP3021_I2C_ADDRESS = 0x48;
};

#endif

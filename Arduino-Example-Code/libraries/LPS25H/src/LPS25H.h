/*
 * LPS25H.h
 *
 * Created: 02/01/2015 20:50:30
 *  Author: speirano
 */


#ifndef LPS25H_H_
#define LPS25H_H_

#include <Arduino.h>


class LPS25H
{
    private:
    uint8_t _address;
    uint8_t readRegister(uint8_t slaveAddress, uint8_t regToRead);
    bool writeRegister(uint8_t slaveAddress, uint8_t regToWrite, uint8_t dataToWrite);

public:
    LPS25H(void);
    bool begin(void);
    bool activate(void);
    bool deactivate(void);

    float readPressure(void);
    float readTemperature(void);

protected:
    float _pressure;
    float _temperature;
};
#endif /* LPS25H_H_ */

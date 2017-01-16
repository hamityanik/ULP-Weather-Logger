/*
* LPS25H.c
*
* Created: 02/01/2015 20:50:20
*  Author: speirano
*/
#include <Wire.h>
#include "LPS25H.h"
#include "LPS25HReg.h"


LPS25H::LPS25H(void) : _address(LPS25H_ADDRESS)
{
     _pressure = 0;
     _temperature = 0;
}


bool LPS25H::begin(void)
{
    uint8_t data;

    data = readRegister(_address, WHO_AM_I);
    if (data == WHO_AM_I_RETURN){
        if (activate()){
            return true;
        }
    }
    return false;
}



bool LPS25H::activate(void)
{
    uint8_t data;

    data = readRegister(_address, CTRL_REG1);
    data |= POWER_UP;
    data |= ODR0_SET;
    writeRegister(_address, CTRL_REG1, data);

    return true;
}


bool LPS25H::deactivate(void)
{
    uint8_t data;

    data = readRegister(_address, CTRL_REG1);
    data &= ~POWER_UP;
    writeRegister(_address, CTRL_REG1, data);
    return true;
}



float LPS25H::readTemperature(void)
{
    int16_t data = 0;
    uint8_t tl, th;
    unsigned char read = 0;

    read = readRegister(_address, STATUS_REG);
    if (read & TEMPERATURE_READY) {
        tl = readRegister(_address, TEMP_L_REG);
        th = readRegister(_address, TEMP_H_REG);

        data = (int16_t)(th << 8 | tl);

        // Decode Temperature
        _temperature = 42.5 + (float)data / 480;
    }
    return _temperature;
}

float LPS25H::readPressure(void)
{
    int32_t data = 0;
    uint8_t pxl, pl, ph;
    unsigned char read = 0;

    read = readRegister(_address, STATUS_REG);
    if (read & PRESSURE_READY) {
        ph = readRegister(_address, PRESSURE_H_REG);
        pl = readRegister(_address, PRESSURE_L_REG);
        pxl = readRegister(_address, PRESSURE_XL_REG);

        data = (int32_t)(int8_t)ph << 16 | (uint16_t)pl << 8 | pxl;

        // Decode pressure
        _pressure = (float) data / 4096.0;
    }

    return _pressure;
}



// Read a single byte from addressToRead and return it as a byte
uint8_t LPS25H::readRegister(uint8_t slaveAddress, uint8_t regToRead)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(regToRead);
    Wire.endTransmission(false); //endTransmission but keep the connection active

    Wire.requestFrom(slaveAddress, (uint8_t)1); //Ask for 1 byte, once done, bus is released by default

    while(!Wire.available()) ; //Wait for the data to come back
    return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into regToWrite
bool LPS25H::writeRegister(uint8_t slaveAddress, uint8_t regToWrite, uint8_t dataToWrite)
{
    Wire.beginTransmission(slaveAddress);

    if (!Wire.write(regToWrite)) {
        return false;
    }
    if (!Wire.write(dataToWrite)) {
        return false;
    }

    uint8_t errorNo = Wire.endTransmission(); //Stop transmitting
    return (errorNo == 0);
}

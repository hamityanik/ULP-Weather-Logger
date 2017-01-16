/*

Arduino Library for Texas Instruments HDC1080 Digital Humidity and Temperature Sensor
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2016 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <Wire.h>

#include "HDC1080.h"


HDC1080::HDC1080()
{
}

void HDC1080::begin(uint8_t address) {
	_address = address;
	/*
	 Heater disabled,
	 Temperature and Humidity Measurement Resolution 14 bit
	*/
	Wire.beginTransmission(_address);
	Wire.write(CONFIGURATION);
	Wire.write(0x0);
	Wire.write(0x0);
	Wire.endTransmission();

}

float HDC1080::readT() {
	return readTemperature();
}

float HDC1080::readTemperature() {
	uint16_t rawT = readData(TEMPERATURE);
	return (rawT / pow(2, 16)) * 165 - 40;
}

float HDC1080::readH() {
	return readHumidity();
}

float HDC1080::readHumidity() {
	uint16_t rawH = readData(HUMIDITY);
	return (rawH / pow(2, 16)) * 100;
}

uint16_t HDC1080::readManufacturerId() {
	return readData(MANUFACTURER_ID);
}

uint16_t HDC1080::readDeviceId() {
	return readData(DEVICE_ID);
}

uint16_t HDC1080::readData(uint8_t pointer) {
	Wire.beginTransmission(_address);
	Wire.write(pointer);
	Wire.endTransmission();

	delay(30);
	Wire.requestFrom(_address, (uint8_t)2);

	while (!Wire.available());

	byte msb = Wire.read();
	byte lsb = Wire.read();

	return msb << 8 | lsb;
}

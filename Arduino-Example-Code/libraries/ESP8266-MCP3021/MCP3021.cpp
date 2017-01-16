// Hardware: https://www.tindie.com/products/AllAboutEE/esp8266-analog-inputs-expander/
#include <MCP3021.h>

/**
 * @brief Sets the pin and fixed address bits for I2C
 *
 * @author Carlos (4/12/2015)
 *
 * @param sda The SDA pin number
 * @param scl The SCL pin number
 */
void MCP3021::begin()
{
	//Wire.begin(MCP3021_I2C_ADDRESS);
}

/**
 * @brief Gives a conversion's result as a digital value between
 *        0 and 1023
 *
 * @author Carlos (4/12/2015)
 *
 * @param deviceId The last three bits in the device's I2C
 *                 address. This would be the last number in
 *                 device's name e.g. for an MCP3021A5 deviceId
 *                 = 5, for an MCP3021A3 deviceId = 3.
 *
 * @return uint16_t The 10-bit conversion result, a value from 0
 *         to 1023
 */
uint16_t MCP3021::read(int deviceId)
{
    // we'll read the bytes from the I2C bus into this array
    uint8_t data[2];
    data[0] = 0x00;
    data[1] = 0x00;

    // the array is a 10-bit result, the smallest type that can contain it is uint16_t
    uint16_t result = 0x0000;

    // The device's address is binary [1][0][0][1][A0][A1][A2] where [A0][A1][A2] is the device's unique id
    Wire.requestFrom(MCP3021_I2C_ADDRESS|deviceId, 2);

    for(int i =0; Wire.available() > 0;i++)
    {
        data[i] = Wire.read();
    }
    // The converter's 10-bit result is two bytes that looks like this:
    // [0][0][0][0][D9][D8][D7][D6] [D5][D4][D3][D1][D0][x][x]
    // so to put them in one variable ...
    result = (result | data[0]) << 6; // we take the MSB and shift it left 6 times
    data[1] = data[1] >> 2; // we take the LSB and shift it right two times
    result = result | data[1]; // we OR both bytes

    return result;
}

/**
 * @brief Gives a converter's result as an analog value between
 *        0 and VDD
 *
 * @author Carlos (4/12/2015)
 *
 * @param deviceId The last three bits in the device's I2C
 *                 address. This would be the last number in
 *                 device's name e.g. for an MCP3021A5 deviceId
 *                 = 5, for an MCP3021A3 deviceId = 3.
 *
 * @param vdd The output of the power supply used to power the
 *            converter.
 *
 * @return float The conversion result from 0 to VDD
 */
float MCP3021::read(int deviceId, float vdd)
{
	uint16_t result = read(deviceId);

	return ((float)result * (vdd / 1023));
}

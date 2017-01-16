/*
 * humidity.cpp
 *
 * Example on SmartEverything Pressure sensor reading
 * In this sketch both pressure and temperature provided by the
 * same sensor (LPS25h) are read
 *
 * Created: 4/27/2015 10:32:11 PM
 *  Author: speirano
 */

#include <Wire.h>

#include <LPS25H.h>
#include <Arduino.h>


// the setup function runs once when you press reset or power the board
void setup() {
    //Initiate the Wire library and join the I2C bus
    Wire.begin();
    pinMode(PIN_LED_13, OUTPUT);
    smePressure.begin();
    SerialUSB.begin(115200);
}

// the loop function runs over and over again forever
void loop() {

    int data = 0;

    data = smePressure.readPressure();
    SerialUSB.print("Pressure   : ");
    SerialUSB.print(data);
    SerialUSB.println(" mbar");

    data = smePressure.readTemperature();
    SerialUSB.print("Temperature: ");
    SerialUSB.print(data);
    SerialUSB.println(" celsius");

    digitalWrite(PIN_LED_13, LOW);
    delay(100);

    digitalWrite(PIN_LED_13, HIGH);    // turn the LED on
    delay(2000);           // wait for a second

}

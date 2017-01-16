/*
 * Ultra Low Power Weather Logger
 * Arduino Blynk example code
 *
 * Created: 15/01/2017 11:45:26
 *  Author: M. Hamit YANIK
 *          @hamityanik
 */

//#define DEBUG 1 // uncomment here for debugging through Serial

#ifdef DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define BLYNK_DEBUG 1
#endif

#define BLYNK_NO_BUILTIN //disable built-in analog and digital operations.
#define BLYNK_NO_INFO    //disable providing info about device to the server. (saving time)

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MCP3021.h"
#include <HDC1080.h>
#include <LPS25H.h>
#include "Adafruit_VEML6070.h"
#include "TSL2561.h"

const char* auth = "YOUR_BLYNK_AUTH_TOKEN";
const char* ssid = "SSID";
const char* password = "PASS";
const uint8_t node = 2;

const uint8_t status_led_pin  = 15;
const uint8_t done_pin = 13;

const uint8_t sda = 0;
const uint8_t scl = 2;

const uint8_t mcp3021_id = 5; // mcp3021a5t
float battery_volts = 0.0;

float temp = 0.0;
float humidity = 0.0;

float pressure = 0.0;
float temp2 = 0.0;

uint32_t uvIndex = 0;

uint32_t visible = 0, full = 0, infrared = 0;
uint32_t lux = 0;

uint64_t luminosity = 0;

float battery_percent = 0.0;

const uint8_t samples = 3;

/*
 * Sensor definitions
 */
MCP3021 battery;
HDC1080 tempHumid;
LPS25H press;
Adafruit_VEML6070 uv;
TSL2561 ambient(TSL2561_ADDR_LOW);

IPAddress ip(192, 168, 1, 77); // these 5 lines for a fix IP-address
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Mac address and channel information recommended for fast wifi connection
uint8_t router_mac[6] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX }; // Your router's wifi mac address
uint8_t router_channel = 10; // Your router's wifi channel


IPAddress blynk_server_ip(188,166,206,43); // blynk-cloud.com IP is 188.166.206.43
                                           // providing IP address here for fast connection
                                           // to Blynk server without DNS resolution

unsigned long millisAtStart = 0;

void setup(void){
  millisAtStart = millis();

  //pinMode(led, OUTPUT);
  //digitalWrite(status_led_pin, 1);

  pinMode(done_pin, OUTPUT);

#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("");
#endif

  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password, router_channel, router_mac);

  Wire.begin(sda, scl);

  uv.begin(VEML6070_1_T);
  battery.begin();
  tempHumid.begin(0x40);
  press.begin();
  ambient.begin();

  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  ambient.setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  //ambient.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)

  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  ambient.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  //ambient.setTiming(TSL2561_INTEGRATIONTIME_101MS);  // medium integration time (medium light)
  //ambient.setTiming(TSL2561_INTEGRATIONTIME_402MS);  // longest integration time (dim light)

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    unsigned long wl_millis = millis();

    if( wl_millis > 1200 ) {
      // shutdown immediately if wifi connection takes too long
      // power save if wifi modem is not reachable
      wl_shutdown();
    }

    delay(20);

#ifdef DEBUG
    Serial.print(".");
#endif
  }

#ifdef DEBUG
  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif

  Blynk.config(auth, blynk_server_ip);

  while( Blynk.connect() == false ) {
#ifdef DEBUG
    Serial.print(".");
#endif
  }

#ifdef DEBUG
  Serial.println("Connected to Blynk server");
#endif
}

void loop(void) {
  post();
}

void post(void){
  for(int i=0; i<samples; i++) {
    humidity += tempHumid.readHumidity();
    temp     += tempHumid.readTemperature();
    pressure += press.readPressure();
    uvIndex  += uv.readUV();
    battery_volts += battery.read(mcp3021_id, 3.3);
  }

  battery_volts /= samples;
  humidity /= samples;
  temp     /= samples;
  pressure /= samples;
  uvIndex  /= samples;

  // barometrics pressure sensor's temperature reading
  temp2 = press.readTemperature();


  //visible = ambient.getLuminosity(TSL2561_VISIBLE);
  //full = ambient.getLuminosity(TSL2561_FULLSPECTRUM);
  //infrared = ambient.getLuminosity(TSL2561_INFRARED);
  luminosity = ambient.getFullLuminosity();

  infrared = luminosity >> 16;
  full = luminosity & 0xFFFF;
  visible = full - infrared;

  lux = ambient.calculateLux(full, infrared);

  // Scale battery percent with volts
  battery_percent = mapfloat(battery_volts, 1.8, 3.0, 0.0, 100.0);

#ifdef DEBUG
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" mbar");

  Serial.print("Temp2: ");
  Serial.print(temp2);
  Serial.println(" C");

  Serial.print("UV: ");
  Serial.println(uvIndex);

  Serial.print("Visible: ");
  Serial.println(visible);

  Serial.print("Full: ");
  Serial.println(full);

  Serial.print("Infrared: ");
  Serial.println(infrared);

  Serial.print("Lux: ");
  Serial.println(lux);

  Serial.print("Battery: ");
  Serial.println(battery_volts);

  Serial.print("Battery percent: ");
  Serial.println(battery_percent);
#endif

  Blynk.virtualWrite(1, temp);
  Blynk.virtualWrite(2, humidity);
  Blynk.virtualWrite(3, pressure);
  Blynk.virtualWrite(4, uvIndex);
  //Blynk.virtualWrite(5, full);
  Blynk.virtualWrite(6, infrared);
  //Blynk.virtualWrite(7, visible);
  Blynk.virtualWrite(8, lux);
  Blynk.virtualWrite(9, battery_volts);
  Blynk.virtualWrite(10, battery_percent);

  unsigned long lastMillis = millis();
  unsigned long took = (lastMillis-millisAtStart);

  Blynk.virtualWrite(11, took);

  Blynk.disconnect();

#ifdef DEBUG

  Serial.print("Took: ");
  Serial.print(took);
  Serial.print("ms");
  delay(100);
#endif

  // Shutdown immediately
  wl_shutdown();
}

void wl_shutdown() {
  digitalWrite(done_pin, HIGH);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

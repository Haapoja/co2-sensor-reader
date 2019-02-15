#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Wire.h>
#include <NDIR_I2C.h>

#define USERNAME "DT_Doacola"
#define DEVICE_ID "esp8266"
#define DEVICE_CREDENTIAL "@WUIAY8zBW%LeQed&!#8@yFV2mD$nae1"

#define SSID "Digitalents Helsinki Guest"
#define SSID_PASSWORD "digivieras"


ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

NDIR_I2C mySensor(0x4D);

void setup() {
  

  thing.add_wifi(SSID, SSID_PASSWORD);
 Serial.begin(9600);

    if (mySensor.begin()) {
        Serial.println("Wait 10 seconds for sensor initialization...");
        delay(10000);
    } else {
        Serial.println("ERROR: Failed to connect to the sensor.");
        while(1);
    }
  
  thing["co2"] >> outputValue(mySensor.ppm);

}

void loop() {

 if (mySensor.measure()) {
        Serial.print("CO2 Concentration is ");
        Serial.print(mySensor.ppm);
        Serial.println("ppm");
    } else {
        Serial.println("Sensor communication error.");
    }

    delay(1000);
  
  thing.handle();
}

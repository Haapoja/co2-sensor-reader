/**
    Digitalents Helsinki - SoftDev & ICT

    Created on: 28.11.2018

    Authors: Kristian Haapoja & Jami Lohilahti

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <NDIR_I2C.h>
#include <ArduinoJson.h>

#define SSID "network"
#define SSID_PASSWORD "password"


NDIR_I2C mySensor(0x4D);

void setup() {
  
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D0, WAKEUP_PULLUP);

  WiFi.begin(SSID, SSID_PASSWORD);
  Serial.begin(9600);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
    wait_for_wifi();
  }
  
  

  if (mySensor.begin()) {
    Serial.println("Wait 10 seconds for sensor initialization...");
    delay(10000);
  } else {
    Serial.println("ERROR: Failed to connect to the sensor.");
    sensor_broken();
    while(1);
  }
}

void loop() {
  Serial.print("WiFi Status: ");
  Serial.print(WiFi.status());
  Serial.println();
  
  if(WiFi.status()== WL_CONNECTED){ 

    wifi_normal();
    
    HTTPClient http;

    http.begin("https://monitor.perkele.space:1880/dt/co2", "B7 65 C0 6B B6 43 75 28 ED 0E F7 E8 B0 84 FE 4C 8A 59 27 1A");
    http.addHeader("Content-Type", "application/json");

    StaticJsonBuffer<300> JSONbuffer;

    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["co2"] = mySensor.ppm;
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    int httpCode = http.POST(JSONmessageBuffer);
    http.end();
  } else {
    wifi_broken();
  }

  if (mySensor.measure()) {
      Serial.print("CO2 Concentration is ");
      Serial.print(mySensor.ppm);
      Serial.println("ppm");
  } else {
      Serial.println("Sensor communication error.");
      sensor_broken();
  }

  delay(1000);

}

void wait_for_wifi() {
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
}

void wifi_broken() {
  digitalWrite(BUILTIN_LED, LOW);
}

void sensor_broken() {
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
}

void wifi_normal() {
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);  
}

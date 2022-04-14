#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "esp32-mqtt.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define SDA 21
#define SCK 22
Adafruit_BME680 bme; // I2C

char buffer[100];

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("BME680 async test"));
  if (!bme.begin())
  {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }
  setupCloudIoT();
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

}

unsigned long lastMillis = 0;
void loop()
{
  mqtt->loop();
  delay(10); // <- fixes some issues with WiFi stability
  if (!mqttClient->connected())
  {
    connect();
  }
  if (millis() - lastMillis > 5000)
  {
    unsigned long endTime = bme.beginReading();
    if (endTime == 0)
    {
      Serial.println(F("Failed to begin reading :("));
      return;
    }
    if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
    }
    Serial.println("Publishing value");
    lastMillis = millis();
    float temp = bme.temperature;
    Serial.println(temp);
    StaticJsonDocument<100> doc;
    doc["temperature"] = temp;
    serializeJson(doc, buffer);
    //publishTelemetry(mqttClient, "/sensors", getDefaultSensor());
    publishTelemetry(buffer);
  }
}
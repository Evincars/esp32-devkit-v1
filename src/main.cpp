#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include "Adafruit_AM2320.h"
#include "Adafruit_Sensor.h"
#include "Arduino.h"
#include "index-html.hpp"

const char *wifiSSID = "Vysehrad";
const char *wifiPassword = "hesloheslo";

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";

AsyncWebServer httpServer(80);  // Create an AsyncWebServer object on port 80
Adafruit_AM2320 am2320 = Adafruit_AM2320();

void printTemperatureAndHumidity() {
  Serial.print("Temp: ");
  Serial.print(am2320.readTemperature());
  Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: ");
  Serial.print(am2320.readHumidity());
  Serial.println(" \%");
  delay(5000);
}

void setup() {
  Serial.begin(115200);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  connectToWifi();

  httpServer.begin();  // Start http server
  am2320.begin();
}

void loop() {
  printTemperatureAndHumidity();
}

void connectToWifi() {
  WiFi.begin(wifiSSID, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
}
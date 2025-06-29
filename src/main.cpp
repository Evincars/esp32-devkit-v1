#include "Arduino.h"
#include "Adafruit_AM2320.h"
#include "Adafruit_Sensor.h"
#include <TM1638lite.h>

#include "wifi-handler.hpp"
#include "http-controllers.hpp"

const int LEDPinForSwitch = 13;
const int DIOPinLedKeyBoard = 17;
const int CLKPinLedKeyBoard = 16;
const int STBPinLedKeyBoard = 4;

AsyncWebServer httpServer(80);  // Create an AsyncWebServer object on port 80
HttpControllers httpControllers;
Adafruit_AM2320 am2320 = Adafruit_AM2320();
TM1638lite tm(STBPinLedKeyBoard, CLKPinLedKeyBoard, DIOPinLedKeyBoard);

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

  pinMode(LEDPinForSwitch, OUTPUT);
  digitalWrite(LEDPinForSwitch, LOW);

  connectToWifi();
  httpControllers.handleRoutes(httpServer);

  tm.reset();
  tm.displayText("EvinCars");

  httpServer.begin();  // Start http server
  am2320.begin();
}

void loop() {
  printTemperatureAndHumidity();
}
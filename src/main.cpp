#include "Arduino.h"
#include "Adafruit_AM2320.h"
#include "Adafruit_Sensor.h"
#include "TM1638plus.h"

#include "wifi-handler.hpp"
#include "http-controllers.hpp"

const int LEDPinForSwitch = 13;
const int DIOPinLedKeyBoard = 17;
const int CLKPinLedKeyBoard = 16;
const int STBPinLedKeyBoard = 4;

AsyncWebServer httpServer(80);  // Create an AsyncWebServer object on port 80
HttpControllers httpControllers;
Adafruit_AM2320 am2320 = Adafruit_AM2320();
// TM1638plus tm(DIOPinLedKeyBoard, CLKPinLedKeyBoard, STBPinLedKeyBoard, true);

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
  // pinMode(DIOPinLedKeyBoard, OUTPUT);
  // pinMode(CLKPinLedKeyBoard, OUTPUT);
  // pinMode(STBPinLedKeyBoard, OUTPUT);

  connectToWifi();
  httpControllers.handleRoutes(httpServer);

  // tm.reset();
  // tm.displayBegin();
  // tm.brightness(7);

  httpServer.begin();  // Start http server
  am2320.begin();
}

void loop() {
  printTemperatureAndHumidity();
  // tm.displayText("EvinCars");
  // tm.setLEDs(0xFFFFFFFF);  // Clear all LEDs
  // delay(1000);
  // tm.setLEDs(0x00000000);  // Turn off all LEDs
  // tm.displayText("Home Test");
}
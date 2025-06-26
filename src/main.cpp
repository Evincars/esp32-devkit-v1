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

String digitalReadAndReturnString(int output) {
  if (digitalRead(output)) {
    return "checked";
  } else {
    return "";
  }
}

// Replaces placeholder with button section in your web page
String htmlKeywordReplacer(const String &var) {
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";

    buttons +=
        "<h4>Output - GPIO 13</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"13\" " +
        digitalReadAndReturnString(13) +
        "><span class=\"slider\"></span></label>";

    return buttons;
  }
  return String();
}

void setup() {
  Serial.begin(115200);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  connectToWifi();

  httpServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, htmlKeywordReplacer);
  });

  // Send a GET request to
  // <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  httpServer.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on
    // <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    } else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  httpServer.begin();  // Start http server
  am2320.begin();
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(am2320.readTemperature());
  Serial.print(" C");
  Serial.print("\t\t");
  Serial.print("Humidity: ");
  Serial.print(am2320.readHumidity());
  Serial.println(" \%");

  delay(2000);
}

void connectToWifi() {
  WiFi.begin(wifiSSID, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
}
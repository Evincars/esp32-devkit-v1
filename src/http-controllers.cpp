#include "http-controllers.hpp"

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

void HttpControllers::handleRoutes(AsyncWebServer &server) {
  rootController(server);
  updateController(server);
}

void HttpControllers::rootController(AsyncWebServer &server) {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, htmlKeywordReplacer);
  });
}

void HttpControllers::updateController(AsyncWebServer &server) {
  server.on("/update", HTTP_GET, [this](AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;

    // GET input1 value on
    // <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(this->PARAM_INPUT_1) && request->hasParam(this->PARAM_INPUT_2))
    {
      inputMessage1 = request->getParam(this->PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(this->PARAM_INPUT_2)->value();
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
}
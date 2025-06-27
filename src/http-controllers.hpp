#pragma once

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index-html.hpp"

class HttpControllers {
 public:
  void handleRoutes(AsyncWebServer &server);

 private:
  const char *PARAM_INPUT_1 = "output";
  const char *PARAM_INPUT_2 = "state";

  void rootController(AsyncWebServer &server);
  void updateController(AsyncWebServer &server);
};
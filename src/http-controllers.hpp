#pragma once

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index-html.hpp"

class HttpControllers {
 public:
  HttpControllers(AsyncWebServer &server);
  void handleRoutes();

 private:
  AsyncWebServer server;
  const char *PARAM_INPUT_1 = "output";
  const char *PARAM_INPUT_2 = "state";
  void rootController();
  void updateController();
};
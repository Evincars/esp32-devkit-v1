#pragma once

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index-html.hpp"

class HttpControllers {
 public:
  void handleRoutes(AsyncWebServer &server);

 private:
  void rootController(AsyncWebServer &server);
  void updateController(AsyncWebServer &server);
};
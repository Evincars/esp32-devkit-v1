#pragma once

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index-html.hpp"

class HttpServer {
 public:
  void rootController(AsyncWebServer &server);
  void updateController(AsyncWebServer &server);
};
#include "index-html.hpp"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>Evincars IoT</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html { font-family: Arial; display: inline-block; text-align: center; }
      h2 { font-size: 2.0rem; }
      p { font-size: 3.0rem; }
      body { max-width: 600px; margin:0px auto; padding-bottom: 25px; background: #222; color: #eee; }
      .switch { position: relative; display: inline-block; width: 120px; height: 68px } 
      .switch input {display: none}
      .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #2d7fc7; border-radius: 6px}
      .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
      input:checked+.slider {background-color: #b30000}
      input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    </style>
  </head>
  <body>
    <h2>Evincars IoT</h2>
    <h2>ESP32 Async Web Server</h2>
    %BUTTONPLACEHOLDER%
    <script>
      function toggleCheckbox(element) {
        var xhr = new XMLHttpRequest();
        if(element.checked) { 
          xhr.open("GET", "/update?output=" + element.id + "&state=1", true); 
        }
        else {
          xhr.open("GET", "/update?output=" + element.id + "&state=0", true);
        }
        xhr.send();
      }
    </script>
  </body>
</html>
)rawliteral";
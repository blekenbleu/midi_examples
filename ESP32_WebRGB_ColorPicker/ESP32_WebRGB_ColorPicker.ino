// http://arduino-er.blogspot.com/2021/04/esp32-s2arduino-esp32-s2-saola-1-web.html
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <Adafruit_NeoPixel.h>
#include "esp32s2LED.h"

//Onboard RGB LED (NeoPixel)
CREATE_ESP32_WS2812_INSTANCE();

AsyncWebServer server(80);

// ssid/password match your WiFi Network
const char* ssid = "ssid";
const char* password = "password";

const char* Param_COLOR ="color";

// HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP32-S2 exercise</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <p>Select Color</p>
  <form action="/get">
    <input name="color" type="color">
    <input type="submit" value="Update RGB">
  </form><br>

</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  Serial.println("---Start---");
  Serial.println("Chip Model: ");
  Serial.println(ESP.getChipModel());
  Serial.println("\nChip Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.println();
  
  ESP32_WS2812_SETUP(0);      // WS2812 all off

  //Act as STA, connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("Visit IP Address: ");
  Serial.println(WiFi.localIP());

  // Send HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?color=#rrggbb
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String color_value;

    //check if parameter "color" found
    if (request->hasParam(Param_COLOR)) {
      Serial.println("param_COLOR received");
      color_value = request->getParam(Param_COLOR)->value();
      Serial.println(color_value);

      //Convert intMessage in #rrggbb form to r,g,b
      color_value.remove(0, 1);
      int intColor = hstol(color_value);
      int r = (intColor & 0xff0000)>>16;
      int g = (intColor & 0x00ff00)>>8;
      int b = (intColor & 0x0000ff);
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);

      //set NeoPixel color
      ESP32_LED(r,g,b);
    }
    
    else {
      Serial.println("No color found");
    }
    
    
    //re-send html
    request->send_P(200, "text/html", index_html);
    
  });
  server.onNotFound(notFound);
  server.begin();
}

//hex-string to long
long hstol(String recv){
  char c[recv.length() + 1];
  recv.toCharArray(c, recv.length() + 1);
  return strtol(c, NULL, 16); 
}

void loop() {
  
}

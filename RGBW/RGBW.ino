#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LED_PIN  18  // GPIO18 for ESP32-S2-Saola-1
#define MSEC    500  // 500 milliseconds

Freenove_ESP32_WS2812 led = Freenove_ESP32_WS2812(1, LED_PIN, 0, TYPE_GRB);

u8 m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };

void setup() {
  led.begin();
  led.setBrightness(10);
}

void loop() {
  for (int j = 0; j < 5; j++) {
    led.setLedColorData(0, m_color[j][0], m_color[j][1], m_color[j][2]);
    led.show();
    delay(MSEC);
  }
}

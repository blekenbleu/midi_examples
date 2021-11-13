/*
  Blink for WS2812 in ESP32-S2-Saola-1_V1.2 AKA ESP32-S2-Saola-1M
*/
#include "esp32s2LED.h"

CREATE_ESP32_WS2812_INSTANCE();
// the setup function runs once when you press reset or power the board
void setup() {
  ESP32_WS2812_SETUP(255);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  for (int i=55; i <256; i+=51) {
    ESP32_RED(0);                      // turn the LED off
    Serial.println("WS2812 off");
    delay(1000);                       // wait for a second
    ESP32_LED(0,i,0);                // turn the LED green
    Serial.println("WS2812 green");
    delay(1000);                       // wait for a second
    ESP32_LED(0,0,i);                // turn the LED blue
    Serial.println("WS2812 blue");
    delay(1000);                       // wait for a second
    ESP32_RED(i>>1);                    // turn the LED half on
    Serial.println("WS2812 dark red");
    delay(1000);                       // wait for a second
  }
}

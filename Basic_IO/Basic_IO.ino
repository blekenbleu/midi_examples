#include <MIDI.h>	// tries to use ESP32-S2-Saola-1 UART0
#include "esp32s2LED.h"

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();
CREATE_ESP32_WS2812_INSTANCE();

void setup() {
  MIDI.begin(4);                 // Launch MIDI and listen to channel 4
  ESP32_WS2812_SETUP(255);
  Serial.begin(115200);          // At least STM32 needs this for Arduino uploads
}

void loop() {
  if (MIDI.read()) {             // If we have received a message
    ESP32_RED(0);
    MIDI.sendNoteOn(42, 127, 1); // Send a Note (pitch 42, velo 127 on channel 1)
    delay(1000);                 // Wait for a second
    MIDI.sendNoteOff(42, 0, 1);  // Stop the note
    ESP32_RED(255);
  }
  else ESP32_LED(0,255,0);       // green
}

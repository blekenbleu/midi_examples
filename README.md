# Description

Sample sketches for TinyUSB MIDI, musical instrument digital interface class  
- [midi](midi) from [EP32TinyUSB](https://github.com/chegewara/EspTinyUSB) examples  
- [midi_test](midi_test) from [Adafruit_TinyUSB_Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino)  
- [Basic_IO](Basic_IO) from [MIDI_Library](https://github.com/FortySevenEffects/arduino_midi_library)
- [RGBW](RGBW) from [Freenove WS2812 Lib for ESP32](https://www.arduino.cc/reference/en/libraries/freenove-ws2812-lib-for-esp32)

# Hardware
To use native ESP32-S2 USB needs connecting pins 19 and 20 to usb cable or with similar connectors:
![](https://ae01.alicdn.com/kf/HTB1MFvqNgHqK1RjSZJnq6zNLpXaR/10-sztuk-Mini-Micro-USB-do-DIP-2-54mm-Adapter-z-cze-modu-u-Panel-kobiet.jpg)


## ESP32TinyUSB Known issue
Currently library is not working with vanila arduino-esp32. It is due some tinyusb callbacks cant be overriden and are used by arduino-esp32. To make it works it is required to add `__attribute__ ((weak)) ` in 3 lines in local arduino file:
https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-tinyusb.c#L266
https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-tinyusb.c#L275
https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-tinyusb.c#L284


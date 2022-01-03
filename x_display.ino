//#if defined(SSD130_MODLE_TYPE)
// Depend OLED library ,See  https://github.com/ThingPulse/esp8266-oled-ssd1306
#include "SSD1306.h"
#include "OLEDDisplayUi.h"


#define SSD1306_ADDRESS 0x3c
SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL, (OLEDDISPLAY_GEOMETRY)SSD130_MODLE_TYPE);
//SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL, GEOMETRY_128_64);
OLEDDisplayUi ui(&oled);
//#endif

#include "globals.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

volatile long encoderPos = 0;
volatile bool encoderBtnPressed = false;
#include "globals.h"

// Global object definitions
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// Navigation variables
MainScreenButton selectedMainButton = BUTTON_PAUSE;
MainScreenButton lastDrawnButton = BUTTON_PAUSE;

// Timing variables
unsigned long lastFrameTime = 0;
unsigned long lastFullRedraw = 0;
const unsigned long FULL_REDRAW_INTERVAL = 10000;

// Encoder variables
volatile long encoderPos = 0;
volatile bool encoderBtnPressed = false;

// Helper function implementations
const char* getButtonName(MainScreenButton button) {
  switch(button) {
    case BUTTON_PAUSE: return "PAUSE";
    case BUTTON_STOP: return "STOP";
    case BUTTON_MATERIAL: return "MATERIAL";
    case BUTTON_BED_TEMP: return "BED_TEMP";
    default: return "UNKNOWN";
  }
}

// Temperature functions
float getChamberTemp() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

float getBedTemp() {
  int raw = analogRead(KY028_AO);
  // Simple conversion - adjust as needed
  return (raw * 100.0) / 1024.0;
}

// ✅ REMOVED showMainScreen() and redrawMainScreen() - they're now in ui.cpp
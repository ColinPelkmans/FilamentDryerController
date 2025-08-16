#ifndef GLOBALS_H
#define GLOBALS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin defines
#define TFT_CS        10
#define TFT_RST       9
#define TFT_DC        A1
#define TFT_BLK       5
#define ENCODER_A     A3        // ✅ This was the PIN A we were testing  
#define ENCODER_B     A3        // ✅ Same pin for both (PIN B navigation only)
#define ENCODER_BTN   A4
#define MOSFET_BED_PWM 8
#define MOSFET_FAN_PWM 6
#define DRV_STEP      2
#define DRV_DIR       12
#define DRV_EN        4
#define DS18B20_PIN   7
#define KY028_AO      A0

// Button enum
enum MainScreenButton {
  BUTTON_PAUSE = 0,
  BUTTON_STOP = 1,
  BUTTON_MATERIAL = 2,
  BUTTON_BED_TEMP = 3,
  BUTTON_COUNT = 4
};

// External declarations (defined in globals.cpp)
extern Adafruit_ST7789 tft;
extern OneWire oneWire;
extern DallasTemperature sensors;

// Navigation variables
extern MainScreenButton selectedMainButton;
extern MainScreenButton lastDrawnButton;

// Timing variables
extern unsigned long lastFrameTime;
extern unsigned long lastFullRedraw;
extern const unsigned long FULL_REDRAW_INTERVAL;

// Encoder variables (for compatibility)
extern volatile long encoderPos;
extern volatile bool encoderBtnPressed;

// Function declarations
const char* getButtonName(MainScreenButton button);
float getChamberTemp();
float getBedTemp();

// ✅ showMainScreen is now declared in ui.h and defined in ui.cpp

#endif
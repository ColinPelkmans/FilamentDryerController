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
#define ENCODER_A     A2
#define ENCODER_B     A3
#define ENCODER_BTN   A4
#define MOSFET_BED_PWM 8
#define MOSFET_FAN_PWM 6
#define DRV_STEP      2
#define DRV_DIR       12
#define DRV_EN        4
#define DS18B20_PIN   7
#define KY028_AO      A0

extern Adafruit_ST7789 tft;
extern OneWire oneWire;
extern DallasTemperature sensors;

extern volatile long encoderPos;
extern volatile bool encoderBtnPressed;

void encoderISR();
void encoderBtnISR();
float ky028ToCelsius(int raw);

#endif
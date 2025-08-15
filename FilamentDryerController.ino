/*
 * FilamentDryerController - Memory Optimized Version
 * 
 * Arduino sketch for controlling a filament dryer with:
 * - SHT30 temperature/humidity sensor
 * - ST7789 TFT display (240x240)
 * - PID temperature control
 * - Fan speed control
 * - Heating element relay
 * - Rotary encoder menu navigation
 * 
 * Target: Arduino Nano 33 IoT
 * Memory optimized for <100% usage
 * 
 * Required Libraries:
 * - Adafruit GFX Library
 * - Adafruit ST7735 and ST7789 Library
 * - SHT3x-Arduino-Library
 * - PID
 * - Encoder
 */

// Core libraries - minimal includes
#include <SPI.h>
#include <Wire.h>

// Display libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Sensor library
#include <SHT3x.h>

// Control libraries
#include <PID_v1.h>
#include <Encoder.h>

// Pin definitions - using const to save RAM
const uint8_t TFT_CS = 10;
const uint8_t TFT_RST = 9;
const uint8_t TFT_DC = 8;

const uint8_t ENCODER_A = 2;
const uint8_t ENCODER_B = 3;
const uint8_t ENCODER_BTN = 4;

const uint8_t HEATER_PIN = 5;
const uint8_t FAN_PIN = 6;
const uint8_t BUZZER_PIN = 7;

// Display configuration
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 240

// System constants stored in PROGMEM to save RAM
const char str_title[] PROGMEM = "Filament Dryer";
const char str_temp[] PROGMEM = "Temp:";
const char str_humidity[] PROGMEM = "RH:";
const char str_target[] PROGMEM = "Target:";
const char str_fan[] PROGMEM = "Fan:";
const char str_heating[] PROGMEM = "HEAT";
const char str_ready[] PROGMEM = "READY";
const char str_on[] PROGMEM = "ON";
const char str_off[] PROGMEM = "OFF";
const char str_adjust[] PROGMEM = "Turn:Adjust";
const char str_next[] PROGMEM = "Press:Next";

// Global objects - minimal set
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
SHT3x sht30;
Encoder encoder(ENCODER_A, ENCODER_B);

// PID variables - using smaller data types where possible
double currentTemp = 0.0;
double targetTemp = 40.0;
double pidOutput = 0.0;
PID temperaturePID(&currentTemp, &pidOutput, &targetTemp, 2, 5, 1, DIRECT);

// System state variables - using efficient types
float currentHumidity = 0.0;
uint8_t fanSpeed = 128; // 0-255 PWM value
bool heaterState = false;
bool systemEnabled = false;

// Menu system - using smaller enum type
enum MenuState : uint8_t {
  MAIN_DISPLAY,
  TEMP_SETTING,
  FAN_SETTING,
  SYSTEM_TOGGLE
};

MenuState currentMenu = MAIN_DISPLAY;
long encoderPosition = 0;
bool buttonPressed = false;

// Timing variables
uint32_t lastButtonTime = 0;
uint32_t lastSensorRead = 0;
uint32_t lastDisplayUpdate = 0;

// Timing constants
const uint16_t SENSOR_INTERVAL = 2000;   // Read sensor every 2 seconds
const uint16_t DISPLAY_INTERVAL = 500;   // Update display every 500ms
const uint8_t BUTTON_DEBOUNCE = 200;     // Button debounce time

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  
  // Initialize outputs to safe state
  digitalWrite(HEATER_PIN, LOW);
  analogWrite(FAN_PIN, 0);
  
  // Initialize I2C for SHT30
  Wire.begin();
  sht30.Begin();
  
  // Initialize display with optimized settings
  tft.init(SCREEN_WIDTH, SCREEN_HEIGHT, SPI_MODE0);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  
  // Initialize PID
  temperaturePID.SetMode(AUTOMATIC);
  temperaturePID.SetOutputLimits(0, 255);
  temperaturePID.SetSampleTime(1000);
  
  // Display startup message
  showStartupScreen();
  delay(2000);
  
  Serial.println(F("FilamentDryerController ready"));
}

void loop() {
  uint32_t currentTime = millis();
  
  // Handle encoder input
  handleEncoder();
  
  // Handle button input
  handleButton();
  
  // Read sensors periodically
  if (currentTime - lastSensorRead >= SENSOR_INTERVAL) {
    readSensors();
    lastSensorRead = currentTime;
  }
  
  // Update control systems
  updateControl();
  
  // Update display periodically
  if (currentTime - lastDisplayUpdate >= DISPLAY_INTERVAL) {
    updateDisplay();
    lastDisplayUpdate = currentTime;
  }
  
  // Small delay to prevent overwhelming the CPU
  delay(10);
}

inline void readSensors() {
  SHT3x_ErrorCode errorCode = sht30.UpdateData();
  
  if (errorCode == SHT3x_ErrorCode_NoError) {
    currentTemp = sht30.GetTemperature();
    currentHumidity = sht30.GetRelativeHumidity();
  }
}

inline void updateControl() {
  if (systemEnabled) {
    // Update PID controller
    temperaturePID.Compute();
    
    // Control heater based on PID output
    heaterState = pidOutput > 100; // Simple on/off control
    digitalWrite(HEATER_PIN, heaterState ? HIGH : LOW);
    
    // Control fan speed
    analogWrite(FAN_PIN, fanSpeed);
  } else {
    // System disabled - turn off all outputs
    digitalWrite(HEATER_PIN, LOW);
    analogWrite(FAN_PIN, 0);
    heaterState = false;
  }
}

void handleEncoder() {
  long newPosition = encoder.read() / 4; // Divide by 4 for single steps
  
  if (newPosition != encoderPosition) {
    int8_t delta = newPosition - encoderPosition;
    encoderPosition = newPosition;
    
    switch (currentMenu) {
      case TEMP_SETTING:
        targetTemp += delta * 1.0; // 1 degree steps
        targetTemp = constrain(targetTemp, 20.0, 80.0);
        break;
        
      case FAN_SETTING:
        fanSpeed = constrain(fanSpeed + delta * 5, 0, 255); // 5 PWM unit steps
        break;
        
      default:
        break;
    }
  }
}

void handleButton() {
  bool currentButtonState = !digitalRead(ENCODER_BTN);
  
  if (currentButtonState && !buttonPressed && 
      (millis() - lastButtonTime > BUTTON_DEBOUNCE)) {
    buttonPressed = true;
    lastButtonTime = millis();
    
    // Cycle through menu states
    switch (currentMenu) {
      case MAIN_DISPLAY:
        currentMenu = TEMP_SETTING;
        break;
      case TEMP_SETTING:
        currentMenu = FAN_SETTING;
        break;
      case FAN_SETTING:
        currentMenu = SYSTEM_TOGGLE;
        break;
      case SYSTEM_TOGGLE:
        systemEnabled = !systemEnabled;
        currentMenu = MAIN_DISPLAY;
        break;
    }
  }
  
  if (!currentButtonState && buttonPressed) {
    buttonPressed = false;
  }
}

void showStartupScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  
  // Center text on screen
  uint8_t titleLen = strlen_P(str_title);
  int16_t x = (SCREEN_WIDTH - titleLen * 12) / 2;
  int16_t y = SCREEN_HEIGHT / 2 - 8;
  
  tft.setCursor(x, y);
  tft.print(FPSTR(str_title));
  
  tft.setTextSize(1);
  tft.setCursor(80, y + 40);
  tft.print(F("Ready..."));
}

void updateDisplay() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  
  // Title
  tft.setCursor(5, 5);
  tft.print(FPSTR(str_title));
  
  // Temperature
  tft.setCursor(5, 25);
  tft.print(FPSTR(str_temp));
  tft.print(currentTemp, 1);
  tft.print(F("C"));
  
  // Humidity
  tft.setCursor(5, 45);
  tft.print(FPSTR(str_humidity));
  tft.print(currentHumidity, 1);
  tft.print(F("%"));
  
  // Target temperature
  tft.setCursor(5, 65);
  tft.print(FPSTR(str_target));
  tft.print(targetTemp, 1);
  tft.print(F("C"));
  if (currentMenu == TEMP_SETTING) {
    tft.print(F(" <"));
  }
  
  // Fan speed
  tft.setCursor(5, 85);
  tft.print(FPSTR(str_fan));
  tft.print(map(fanSpeed, 0, 255, 0, 100));
  tft.print(F("%"));
  if (currentMenu == FAN_SETTING) {
    tft.print(F(" <"));
  }
  
  // System status
  tft.setCursor(5, 105);
  tft.print(F("Sys:"));
  if (systemEnabled) {
    tft.setTextColor(ST77XX_GREEN);
    tft.print(FPSTR(str_on));
  } else {
    tft.setTextColor(ST77XX_RED);
    tft.print(FPSTR(str_off));
  }
  if (currentMenu == SYSTEM_TOGGLE) {
    tft.setTextColor(ST77XX_WHITE);
    tft.print(F(" <"));
  }
  
  // Heater status
  tft.setTextColor(heaterState ? ST77XX_RED : ST77XX_BLUE);
  tft.setCursor(5, 125);
  if (heaterState) {
    tft.print(FPSTR(str_heating));
  } else {
    tft.print(FPSTR(str_ready));
  }
  
  // Menu instructions - compact
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(5, 200);
  tft.print(FPSTR(str_adjust));
  tft.setCursor(5, 215);
  tft.print(FPSTR(str_next));
}
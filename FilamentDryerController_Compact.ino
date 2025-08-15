/*
 * FilamentDryerController - Ultra Compact Version
 * 
 * Minimal memory Arduino sketch for filament dryer control
 * Target: Arduino Nano 33 IoT with <90% memory usage
 * 
 * Features:
 * - SHT30 sensor reading
 * - ST7789 basic display
 * - Simple PID control
 * - Encoder menu
 * - Relay + PWM outputs
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SHT3x.h>
#include <PID_v1.h>
#include <Encoder.h>

// Hardware pins
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9
#define ENC_A    2
#define ENC_B    3
#define ENC_BTN  4
#define HEATER   5
#define FAN      6

// Objects
Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
SHT3x sht30;
Encoder enc(ENC_A, ENC_B);

// Variables - using minimal memory
double temp = 20.0, target = 40.0, output = 0.0;
PID pid(&temp, &output, &target, 2, 5, 1, DIRECT);

float humidity = 0.0;
uint8_t fanSpeed = 128, menu = 0;
bool heater = false, enabled = false, btnState = false;
uint32_t lastSensor = 0, lastDisplay = 0, lastBtn = 0;
long encPos = 0;

void setup() {
  Serial.begin(115200);
  
  // Pin setup
  pinMode(HEATER, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(ENC_BTN, INPUT_PULLUP);
  digitalWrite(HEATER, LOW);
  analogWrite(FAN, 0);
  
  // Hardware init
  Wire.begin();
  sht30.Begin();
  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(0);
  
  // PID setup
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 255);
  
  // Startup display
  tft.setTextColor(0xFFFF);
  tft.setCursor(60, 120);
  tft.print("Filament Dryer");
  delay(2000);
  
  Serial.println(F("Ready"));
}

void loop() {
  uint32_t now = millis();
  
  // Read sensors every 2 seconds
  if (now - lastSensor > 2000) {
    if (sht30.UpdateData() == SHT3x_ErrorCode_NoError) {
      temp = sht30.GetTemperature();
      humidity = sht30.GetRelativeHumidity();
    }
    lastSensor = now;
  }
  
  // Handle encoder
  long newPos = enc.read() / 4;
  if (newPos != encPos) {
    int8_t delta = newPos - encPos;
    encPos = newPos;
    
    switch (menu) {
      case 1: target = constrain(target + delta, 20, 80); break;
      case 2: fanSpeed = constrain(fanSpeed + delta * 5, 0, 255); break;
    }
  }
  
  // Handle button
  bool btn = !digitalRead(ENC_BTN);
  if (btn && !btnState && (now - lastBtn > 200)) {
    menu = (menu + 1) % 4;
    if (menu == 3) {
      enabled = !enabled;
      menu = 0;
    }
    btnState = true;
    lastBtn = now;
  }
  if (!btn) btnState = false;
  
  // Control
  if (enabled) {
    pid.Compute();
    heater = output > 100;
    digitalWrite(HEATER, heater);
    analogWrite(FAN, fanSpeed);
  } else {
    digitalWrite(HEATER, LOW);
    analogWrite(FAN, 0);
    heater = false;
  }
  
  // Update display every 500ms
  if (now - lastDisplay > 500) {
    updateDisplay();
    lastDisplay = now;
  }
  
  delay(10);
}

void updateDisplay() {
  tft.fillScreen(0);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(1);
  
  // Title
  tft.setCursor(5, 5);
  tft.print("Filament Dryer");
  
  // Temperature
  tft.setCursor(5, 30);
  tft.print("Temp: ");
  tft.print(temp, 1);
  tft.print("C");
  
  // Humidity
  tft.setCursor(5, 50);
  tft.print("RH: ");
  tft.print(humidity, 1);
  tft.print("%");
  
  // Target
  tft.setCursor(5, 70);
  tft.print("Target: ");
  tft.print(target, 1);
  tft.print("C");
  if (menu == 1) tft.print(" <");
  
  // Fan
  tft.setCursor(5, 90);
  tft.print("Fan: ");
  tft.print(map(fanSpeed, 0, 255, 0, 100));
  tft.print("%");
  if (menu == 2) tft.print(" <");
  
  // System
  tft.setCursor(5, 110);
  tft.print("System: ");
  tft.setTextColor(enabled ? 0x07E0 : 0xF800);
  tft.print(enabled ? "ON" : "OFF");
  
  // Heater status
  tft.setTextColor(heater ? 0xF800 : 0x001F);
  tft.setCursor(5, 130);
  tft.print(heater ? "HEATING" : "READY");
  
  // Instructions
  tft.setTextColor(0x07FF);
  tft.setCursor(5, 190);
  tft.print("Turn:Adjust Press:Next");
}
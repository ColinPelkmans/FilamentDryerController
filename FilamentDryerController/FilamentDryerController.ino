#include <Arduino.h>
#include "globals.h"
#include "encoder.h"
#include "ui.h"
#include "sensors.h"
#include "presets.h"
#include "dryingController.h"

// Enhanced menu state
enum MenuState { 
  MENU_MAIN,      // Main dashboard screen
  MENU_PRESET,    // Preset selection
  MENU_DRYING     // Active drying (same as main but with different behavior)
};

MenuState menuState = MENU_MAIN; // Start with main screen
size_t presetIdx = 0;
bool isPaused = false;

#line 19 "C:\\Users\\colin\\Documents\\3DPrints\\MyPrints\\FilamentHeater\\Copilot\\Claude\\FilamentDryerController\\FilamentDryerController.ino"
void setup();
#line 40 "C:\\Users\\colin\\Documents\\3DPrints\\MyPrints\\FilamentHeater\\Copilot\\Claude\\FilamentDryerController\\FilamentDryerController.ino"
void loop();
#line 19 "C:\\Users\\colin\\Documents\\3DPrints\\MyPrints\\FilamentHeater\\Copilot\\Claude\\FilamentDryerController\\FilamentDryerController.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Filament Dryer Starting...");

  setupUI();
  setupEncoder();
  setupSensors();
  
  pinMode(MOSFET_BED_PWM, OUTPUT);
  pinMode(MOSFET_FAN_PWM, OUTPUT);
  pinMode(DRV_STEP, OUTPUT);
  pinMode(DRV_DIR, OUTPUT);
  pinMode(DRV_EN, OUTPUT);
  digitalWrite(DRV_EN, LOW);

  // Start with main screen
  float chamberTemp = getChamberTemp();
  float bedTemp = getBedTemp();
  showMainScreen(chamberTemp, bedTemp, 0, "None", 0, 0, 0, false);
}

void loop() {
  pollEncoder();

  float chamberTemp = getChamberTemp();
  float bedTemp = getBedTemp();

  // Debug encoder values
  static long lastEncoderDebug = 0;
  if (encoderPos != lastEncoderDebug) {
    Serial.print("Encoder position: ");
    Serial.println(encoderPos);
    lastEncoderDebug = encoderPos;
  }

  static long lastDetent = 0;
  const int stepsPerDetent = 4;
  long detent = encoderPos / stepsPerDetent;

  switch (menuState) {
    case MENU_MAIN:
      // Show main dashboard
      if (detent != lastDetent) {
        // For now, just show encoder movement works
        Serial.print("Main screen encoder detent: ");
        Serial.println(detent);
        lastDetent = detent;
      }
      
      if (encoderBtnPressed) {
        encoderBtnPressed = false;
        Serial.println("Button pressed - going to preset menu");
        menuState = MENU_PRESET;
        showPresetMenu(presetIdx);
      }
      
      // Update main screen every 2 seconds
      static unsigned long lastMainUpdate = 0;
      if (millis() - lastMainUpdate > 2000) {
        const DryingPreset& p = getPreset(presetIdx);
        int progress = 0;
        int remainingH = 0, remainingM = 0;
        
        if (session.state == RUNNING) {
          progress = (session.elapsedMin * 100) / p.durationMin;
          unsigned long remainingMin = p.durationMin - session.elapsedMin;
          remainingH = remainingMin / 60;
          remainingM = remainingMin % 60;
        }
        
        showMainScreen(chamberTemp, bedTemp, 50, p.name, progress, remainingH, remainingM, isPaused);
        lastMainUpdate = millis();
      }
      break;

    case MENU_PRESET:
      if (detent != lastDetent) {
        if (detent > lastDetent) {
          presetIdx = (presetIdx + 1) % NUM_PRESETS;
        } else {
          presetIdx = (presetIdx + NUM_PRESETS - 1) % NUM_PRESETS;
        }
        lastDetent = detent;
        Serial.print("Preset changed to: ");
        Serial.println(presets[presetIdx].name);
        showPresetMenu(presetIdx);
      }
      
      if (encoderBtnPressed) {
        encoderBtnPressed = false;
        Serial.println("Starting drying process");
        startDrying(presetIdx);
        menuState = MENU_DRYING;
      }
      break;

    case MENU_DRYING:
      updateDrying(chamberTemp);
      
      // Update drying screen every second
      static unsigned long lastDryingUpdate = 0;
      if (millis() - lastDryingUpdate > 1000) {
        const DryingPreset& p = getPreset(presetIdx);
        int progress = (session.elapsedMin * 100) / p.durationMin;
        unsigned long remainingMin = p.durationMin - session.elapsedMin;
        int remainingH = remainingMin / 60;
        int remainingM = remainingMin % 60;
        
        showMainScreen(chamberTemp, bedTemp, 50, p.name, progress, remainingH, remainingM, isPaused);
        lastDryingUpdate = millis();
      }
      
      if (session.state == FINISHED) {
        delay(3000);
        menuState = MENU_MAIN;
      }
      
      // Button press toggles pause or goes back to main
      if (encoderBtnPressed) {
        encoderBtnPressed = false;
        // For now, just go back to main
        menuState = MENU_MAIN;
      }
      break;
  }

  delay(10); // Small delay for stability
}

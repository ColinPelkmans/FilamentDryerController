#include <Arduino.h>
#include "globals.h"
#include "encoder.h"
#include "ui.h"
#include "sensors.h"
#include "presets.h"
#include "dryingController.h"

enum MenuState { 
  MENU_MAIN,
  MENU_PRESET,
  MENU_DRYING
};

MenuState menuState = MENU_MAIN;
size_t presetIdx = 0;
bool isPaused = false;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Filament Dryer - HORIZONTAL DISPLAY ===");

  // ✅ CHANGE: Use setupUI() instead of direct initialization
  setupUI();  // This will set rotation to 1 (landscape)
  
  // Initialize sensors
  setupSensors();
  
  pinMode(MOSFET_BED_PWM, OUTPUT);
  pinMode(MOSFET_FAN_PWM, OUTPUT);
  pinMode(DRV_STEP, OUTPUT);
  pinMode(DRV_DIR, OUTPUT);
  pinMode(DRV_EN, OUTPUT);
  digitalWrite(DRV_EN, LOW);

  // Setup only PIN B and button
  pinMode(ENCODER_B, INPUT_PULLUP);     // A3 - our rotation input
  pinMode(ENCODER_BTN, INPUT_PULLUP);   // A4 - our selection input

  selectedMainButton = BUTTON_PAUSE;
  redrawMainScreen();
  lastDrawnButton = selectedMainButton;
  
  lastFrameTime = millis();
  lastFullRedraw = millis();
  
  Serial.println("🎮 SIMPLE LOOPING NAVIGATION:");
  Serial.println("🔄 ROTATE: Loops through buttons (0→1→2→3→0→1→2→3...)");
  Serial.println("🔘 PRESS: Select/activate current button");
  Serial.println("==========================================");
  Serial.println("Navigation Loop: PAUSE → STOP → MATERIAL → BED_TEMP → PAUSE...");
  Serial.println("==========================================");
}

void loop() {
  unsigned long currentTime = millis();
  
  // 🔄 PIN B ROTATION HANDLING - Simple looping navigation
  static int lastPinB = -1;
  static unsigned long lastBounceTime = 0;
  static unsigned long lastNavigationTime = 0;
  static int bounceCount = 0;
  static bool inBounceSequence = false;
  
  int currentPinB = digitalRead(ENCODER_B);
  
  if (currentPinB != lastPinB && lastPinB != -1) {
    // PIN B changed - this is part of encoder bounce sequence
    
    if (!inBounceSequence) {
      // Start of new bounce sequence
      inBounceSequence = true;
      bounceCount = 1;
      lastBounceTime = currentTime;
      Serial.print("🔄 Rotation started (bounce ");
      Serial.print(bounceCount);
      Serial.println(")");
    } else {
      // Continue bounce sequence
      bounceCount++;
      lastBounceTime = currentTime;
      
      // Only print every few bounces to avoid spam
      if (bounceCount % 4 == 0) {
        Serial.print("🔄 Bouncing... (");
        Serial.print(bounceCount);
        Serial.println(" bounces)");
      }
    }
  }
  
  // End of bounce sequence - treat as one rotation step
  if (inBounceSequence && (currentTime - lastBounceTime > 150)) {
    // No new bounces for 150ms - sequence complete
    
    // Only navigate if enough time has passed since last navigation (prevent too rapid)
    if (currentTime - lastNavigationTime > 400) {
      int oldButton = (int)selectedMainButton;
      
      // 🔄 SIMPLE LOOP: Go to next button, wrap around to 0 after last button
      selectedMainButton = (MainScreenButton)((oldButton + 1) % BUTTON_COUNT);
      
      Serial.print("🔄 LOOP NAVIGATION: ");
      Serial.print(getButtonName((MainScreenButton)oldButton));
      Serial.print(" (");
      Serial.print(oldButton);
      Serial.print(") → ");
      Serial.print(getButtonName(selectedMainButton));
      Serial.print(" (");
      Serial.print((int)selectedMainButton);
      Serial.print(") [");
      Serial.print(bounceCount);
      Serial.println(" bounces]");
      
      lastNavigationTime = currentTime;
    } else {
      Serial.print("🔄 Rotation ignored (too fast, ");
      Serial.print(bounceCount);
      Serial.println(" bounces)");
    }
    
    inBounceSequence = false;
    bounceCount = 0;
  }
  
  lastPinB = currentPinB;
  
  // 🔘 BUTTON HANDLING - Simple press to select
  static int lastBtnState = HIGH;
  
  int currentBtn = digitalRead(ENCODER_BTN);
  
  if (currentBtn == LOW && lastBtnState == HIGH) {
    // Button pressed - immediate action
    Serial.print("🔘 SELECT: ");
    Serial.print(getButtonName(selectedMainButton));
    Serial.print(" (button ");
    Serial.print((int)selectedMainButton);
    Serial.println(")");
    
    // Handle the selection based on current button
    switch(selectedMainButton) {
      case BUTTON_PAUSE:
        if (session.state == RUNNING) {
          pauseDrying();
          isPaused = true;
        } else if (session.state == READY) {
          resumeDrying();
          isPaused = false;
        }
        break;
      case BUTTON_STOP:
        stopDrying();
        isPaused = false;
        break;
      case BUTTON_MATERIAL:
        presetIdx = (presetIdx + 1) % getPresetCount();
        Serial.print("Material: ");
        Serial.println(getPreset(presetIdx).name);
        break;
      case BUTTON_BED_TEMP:
        Serial.println("   → Bed temperature adjustment");
        break;
    }
    
    delay(200); // Simple debounce
  }
  lastBtnState = currentBtn;
  
  // 📊 Status display every 5 seconds
  static unsigned long lastStatus = 0;
  if (currentTime - lastStatus > 5000) {
    Serial.print("📍 Current position: ");
    Serial.print(getButtonName(selectedMainButton));
    Serial.print(" (");
    Serial.print((int)selectedMainButton);
    Serial.print("/");
    Serial.print(BUTTON_COUNT - 1);
    Serial.println(")");
    lastStatus = currentTime;
  }

  // 🖼️ Screen redraw
  if (selectedMainButton != lastDrawnButton) {
    Serial.print("🖼️ HIGHLIGHT: ");
    Serial.print(getButtonName(selectedMainButton));
    Serial.print(" (position ");
    Serial.print((int)selectedMainButton);
    Serial.println(")");
    
    redrawMainScreen();
    lastDrawnButton = selectedMainButton;
    lastFullRedraw = currentTime;
  }
  else if (currentTime - lastFullRedraw >= FULL_REDRAW_INTERVAL) {
    redrawMainScreen();
    lastDrawnButton = selectedMainButton;
    lastFullRedraw = currentTime;
  }
}
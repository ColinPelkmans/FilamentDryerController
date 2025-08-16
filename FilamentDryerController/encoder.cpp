#include "encoder.h"
#include "globals.h"
#include <Arduino.h>

// Simple state tracking
static int lastA = HIGH;
static int lastB = HIGH;
static bool lastBtnState = HIGH;
static unsigned long lastBtnTime = 0;

void setupEncoder() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_BTN, INPUT_PULLUP);

  // Initialize
  lastA = digitalRead(ENCODER_A);
  lastB = digitalRead(ENCODER_B);
  encoderPos = 0;
  encoderBtnPressed = false;
  
  Serial.println("Encoder initialized");
}

void pollEncoder() {
  // Read current pin states
  int currentA = digitalRead(ENCODER_A);
  int currentB = digitalRead(ENCODER_B);
  
  // Detect transitions on EITHER pin A OR pin B
  bool aChanged = (currentA != lastA);
  bool bChanged = (currentB != lastB);
  
  if (aChanged || bChanged) {
    // Standard quadrature encoder logic
    if (aChanged) {
      if (currentA == LOW && lastA == HIGH) {
        // A falling edge
        if (currentB == HIGH) {
          encoderPos++;
        } else {
          encoderPos--;
        }
      } else if (currentA == HIGH && lastA == LOW) {
        // A rising edge
        if (currentB == LOW) {
          encoderPos++;
        } else {
          encoderPos--;
        }
      }
    }
    
    if (bChanged) {
      if (currentB == LOW && lastB == HIGH) {
        // B falling edge
        if (currentA == LOW) {
          encoderPos++;
        } else {
          encoderPos--;
        }
      } else if (currentB == HIGH && lastB == LOW) {
        // B rising edge
        if (currentA == HIGH) {
          encoderPos++;
        } else {
          encoderPos--;
        }
      }
    }
  }
  
  // Update last states
  lastA = currentA;
  lastB = currentB;
  
  // Button handling
  bool currentBtn = digitalRead(ENCODER_BTN);
  if (currentBtn != lastBtnState) {
    if (millis() - lastBtnTime > 50) { // Debounce
      if (currentBtn == LOW && lastBtnState == HIGH) {
        encoderBtnPressed = true;
      }
      lastBtnTime = millis();
    }
    lastBtnState = currentBtn;
  }
}
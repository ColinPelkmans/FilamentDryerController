#include "encoder.h"
#include <Arduino.h>

// Encoder state tracking
static volatile long position = 0;
static volatile uint8_t lastState = 0;
static volatile bool buttonPressed = false;

// Debouncing
static unsigned long lastButtonTime = 0;
static bool lastButtonState = HIGH;

void setupEncoder() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_BTN, INPUT_PULLUP);

  // Initialize encoder state
  lastState = (digitalRead(ENCODER_A) << 1) | digitalRead(ENCODER_B);
  encoderPos = 0;
  encoderBtnPressed = false;
  
  Serial.println("Encoder setup complete");
  Serial.print("Initial A: "); Serial.print(digitalRead(ENCODER_A));
  Serial.print(", B: "); Serial.println(digitalRead(ENCODER_B));
}

void pollEncoder() {
  // Read current state
  uint8_t currentState = (digitalRead(ENCODER_A) << 1) | digitalRead(ENCODER_B);
  
  // Check for state change
  if (currentState != lastState) {
    // Determine direction using Gray code sequence
    // Gray code: 00 -> 01 -> 11 -> 10 -> 00 (clockwise)
    // Gray code: 00 -> 10 -> 11 -> 01 -> 00 (counter-clockwise)
    
    if ((lastState == 0 && currentState == 1) ||
        (lastState == 1 && currentState == 3) ||
        (lastState == 3 && currentState == 2) ||
        (lastState == 2 && currentState == 0)) {
      // Clockwise
      encoderPos++;
    } else if ((lastState == 0 && currentState == 2) ||
               (lastState == 2 && currentState == 3) ||
               (lastState == 3 && currentState == 1) ||
               (lastState == 1 && currentState == 0)) {
      // Counter-clockwise
      encoderPos--;
    }
    
    lastState = currentState;
  }
  
  // Handle button with debouncing
  bool currentButton = digitalRead(ENCODER_BTN);
  unsigned long currentTime = millis();
  
  if (currentButton != lastButtonState && currentTime - lastButtonTime > 50) {
    if (currentButton == LOW && lastButtonState == HIGH) {
      // Button pressed (falling edge)
      encoderBtnPressed = true;
      Serial.println("Button pressed!");
    }
    lastButtonState = currentButton;
    lastButtonTime = currentTime;
  }
}
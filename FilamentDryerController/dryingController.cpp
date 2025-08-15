#include "dryingController.h"
#include <Arduino.h>

DryingSession session = {0, READY, 0, 0, 0.0f};

void startDrying(size_t presetIdx) {
  session.presetIdx = presetIdx;
  session.state = RUNNING;
  session.startMillis = millis();
  session.elapsedMin = 0;
  session.lastTempC = 0.0f;
}

void stopDrying() {
  session.state = FINISHED;
}

void updateDrying(float currentTemp) {
  if (session.state != RUNNING) return;

  session.lastTempC = currentTemp;
  unsigned long elapsedMillis = millis() - session.startMillis;
  session.elapsedMin = elapsedMillis / 60000UL;

  const DryingPreset& p = getPreset(session.presetIdx);

  // Simple temperature control (replace with PID for precision!)
  if (currentTemp < p.targetTempC - 1) {
    analogWrite(MOSFET_BED_PWM, 200); // Heater ON
    analogWrite(MOSFET_FAN_PWM, 0);   // Fan OFF
  } else if (currentTemp > p.targetTempC + 1) {
    analogWrite(MOSFET_BED_PWM, 0);   // Heater OFF
    analogWrite(MOSFET_FAN_PWM, 200); // Fan ON
  } else {
    analogWrite(MOSFET_BED_PWM, 128); // Maintain
    analogWrite(MOSFET_FAN_PWM, 128); // Maintain
  }

  // Check for end of drying
  if (session.elapsedMin >= p.durationMin) {
    stopDrying();
    analogWrite(MOSFET_BED_PWM, 0); // Heater OFF
    analogWrite(MOSFET_FAN_PWM, 255); // Fan ON full
  }
}
#include "sensors.h"

void setupSensors() {
  sensors.begin();
  Serial.println("Sensors initialized");
}

float ky028ToCelsius(int raw) {
  // Simple conversion for now - adjust based on your sensor
  return (raw * 100.0) / 1024.0;
}

// getChamberTemp() and getBedTemp() are now in globals.cpp to avoid duplicates
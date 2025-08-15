#include "sensors.h"
#include <Arduino.h>

void setupSensors() {
  sensors.begin();
}

float getChamberTemp() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

float getBedTemp() {
  int ky028_raw = analogRead(KY028_AO);
  return ky028ToCelsius(ky028_raw);
}

float ky028ToCelsius(int raw) {
  float voltage = raw * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100;
  return tempC;
}
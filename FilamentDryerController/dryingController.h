#ifndef DRYING_CONTROLLER_H
#define DRYING_CONTROLLER_H

#include "presets.h"
#include "globals.h"

// Drying process states
enum DryingState {
  READY,
  RUNNING,
  FINISHED
};

struct DryingSession {
  size_t presetIdx;
  DryingState state;
  unsigned long startMillis;
  unsigned long elapsedMin;
  float lastTempC;
};

extern DryingSession session;

void startDrying(size_t presetIdx);
void stopDrying();
void updateDrying(float currentTemp);

// ✅ Add missing functions that FilamentDryerController.ino expects
void updateDryingController();
void pauseDrying();
void resumeDrying();

#endif
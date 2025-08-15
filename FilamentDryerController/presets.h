#ifndef PRESETS_H
#define PRESETS_H

#include <Arduino.h>

// Define a struct for a drying preset
struct DryingPreset {
  const char* name;
  float targetTempC;
  unsigned long durationMin; // Duration in minutes
};

// Preset list (add more as needed)
extern const DryingPreset presets[];
extern const size_t NUM_PRESETS;

// Helper to get preset by index
const DryingPreset& getPreset(size_t idx);

#endif
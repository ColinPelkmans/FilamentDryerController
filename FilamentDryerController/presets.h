#ifndef PRESETS_H
#define PRESETS_H

#include <Arduino.h>

struct DryingPreset {
  const char* name;
  float targetTempC;     // ✅ Changed from 'int tempC' to 'float targetTempC'
  int durationMin;
};

// Add missing declarations
extern const DryingPreset presets[];
extern const size_t NUM_PRESETS;

const DryingPreset& getPreset(size_t index);
size_t getPresetCount();

#endif
#include "presets.h"

const DryingPreset presets[] = {
  {"PLA",    45.0, 240},  // 4h at 45°C
  {"PETG",   65.0, 360},  // 6h at 65°C
  {"ABS",    80.0, 240},  // 4h at 80°C
  {"Nylon",  70.0, 480},  // 8h at 70°C
  {"TPU",    45.0, 240}   // 4h at 45°C
};

const size_t NUM_PRESETS = sizeof(presets) / sizeof(presets[0]);

const DryingPreset& getPreset(size_t idx) {
  if (idx >= NUM_PRESETS) idx = 0;
  return presets[idx];
}
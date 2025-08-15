#line 1 "C:\\Users\\colin\\Documents\\3DPrints\\MyPrints\\FilamentHeater\\Copilot\\Claude\\FilamentDryerController\\ui.h"
#ifndef UI_H
#define UI_H

#include "globals.h"
#include "dryingController.h"
#include "presets.h"

void setupUI();
void updateUI(float chamberTemp, float bedTemp);
void showPresetMenu(size_t selectedIdx);
void showDryingStatus();

// New function for main dashboard
void showMainScreen(float airTemp, float bedTemp, int fanSpeed, const char* material, 
                   int progressPercent, int remainingHours, int remainingMinutes, bool isPaused);

#endif
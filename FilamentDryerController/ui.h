#ifndef UI_H
#define UI_H

#include "globals.h"

void setupUI();
void showPresetMenu(size_t selectedPresetIndex);
void showMainScreen(float airTemp, float bedTemp, int fanSpeed, const char* material, 
                   int progressPercent, int remainingHours, int remainingMinutes, 
                   bool isPaused, MainScreenButton selectedButton);

// ✅ Add redrawMainScreen function declaration
void redrawMainScreen();

#endif
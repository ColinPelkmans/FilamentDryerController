#ifndef ICONS_H
#define ICONS_H

#include "globals.h"

// Icon size constants
#define ICON_SIZE 16

// Icon drawing functions
void drawThermometerIcon(int x, int y, uint16_t color);
void drawFlameIcon(int x, int y, uint16_t color);
void drawFanIcon(int x, int y, uint16_t color);
void drawClockIcon(int x, int y, uint16_t color);
void drawPauseIcon(int x, int y, uint16_t color);
void drawStopIcon(int x, int y, uint16_t color);

// Progress bar icon
void drawProgressIcon(int x, int y, uint16_t color);

#endif
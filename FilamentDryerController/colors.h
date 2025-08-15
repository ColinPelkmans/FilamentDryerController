#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

// RGB888 to RGB565 conversion macro
#define RGB565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

// Color palette specifically for your mockup
#define UI_BACKGROUND    RGB565(16, 32, 96)    // Deep blue background
#define UI_ACCENT        RGB565(32, 64, 128)   // Lighter blue accents
#define UI_WHITE         0xFFFF                // Pure white
#define UI_BLACK         0x0000                // Pure black
#define UI_GREEN         RGB565(0, 255, 100)   // Progress bar green
#define UI_GRAY          RGB565(128, 128, 128) // Button gray
#define UI_DARK_BLUE     RGB565(8, 16, 64)     // Progress bar background

// Alternative reliable colors (if RGB565 macro doesn't work)
#define NAVY_BLUE        0x000F
#define ROYAL_BLUE       0x435C
#define STEEL_BLUE       0x4416
#define BRIGHT_GREEN     0x07E0
#define LIGHT_GRAY       0xC618

#endif
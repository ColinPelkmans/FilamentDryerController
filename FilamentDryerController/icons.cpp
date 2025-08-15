#include "icons.h"

void drawThermometerIcon(int x, int y, uint16_t color) {
  // Thermometer body (rectangle)
  tft.drawRect(x + 6, y + 1, 4, 10, color);
  tft.drawRect(x + 7, y + 2, 2, 8, color);
  
  // Thermometer bulb (circle)
  tft.fillCircle(x + 8, y + 13, 3, color);
  
  // Mercury line
  tft.drawLine(x + 8, y + 3, x + 8, y + 10, color);
}

void drawFlameIcon(int x, int y, uint16_t color) {
  // Main flame shape
  tft.fillTriangle(x + 8, y + 1, x + 5, y + 8, x + 11, y + 8, color);
  tft.fillTriangle(x + 8, y + 4, x + 6, y + 10, x + 10, y + 10, color);
  
  // Flame base
  tft.fillCircle(x + 8, y + 12, 2, color);
  
  // Inner flame detail
  tft.fillTriangle(x + 8, y + 3, x + 7, y + 7, x + 9, y + 7, color);
}

void drawFanIcon(int x, int y, uint16_t color) {
  // Outer circle
  tft.drawCircle(x + 8, y + 8, 6, color);
  
  // Fan blades (curved lines)
  tft.drawLine(x + 3, y + 5, x + 13, y + 11, color);
  tft.drawLine(x + 13, y + 5, x + 3, y + 11, color);
  tft.drawLine(x + 5, y + 3, x + 11, y + 13, color);
  tft.drawLine(x + 11, y + 3, x + 5, y + 13, color);
  
  // Center hub
  tft.fillCircle(x + 8, y + 8, 2, color);
}

void drawClockIcon(int x, int y, uint16_t color) {
  // Clock face
  tft.drawCircle(x + 8, y + 8, 7, color);
  
  // Hour hand (short)
  tft.drawLine(x + 8, y + 8, x + 8, y + 4, color);
  
  // Minute hand (long)
  tft.drawLine(x + 8, y + 8, x + 12, y + 6, color);
  
  // Center dot
  tft.fillCircle(x + 8, y + 8, 1, color);
  
  // 12 o'clock mark
  tft.drawLine(x + 8, y + 2, x + 8, y + 3, color);
}

void drawPauseIcon(int x, int y, uint16_t color) {
  // Two vertical bars
  tft.fillRect(x + 5, y + 3, 2, 10, color);
  tft.fillRect(x + 9, y + 3, 2, 10, color);
}

void drawStopIcon(int x, int y, uint16_t color) {
  // Filled square
  tft.fillRect(x + 4, y + 4, 8, 8, color);
}

void drawProgressIcon(int x, int y, uint16_t color) {
  // Simple progress bar icon
  tft.drawRect(x + 2, y + 6, 12, 4, color);
  tft.fillRect(x + 3, y + 7, 6, 2, color); // Half filled
}
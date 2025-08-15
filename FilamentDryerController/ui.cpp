#include "ui.h"
#include "icons.h"
#include "colors.h"

void setupUI() {
  tft.init(240, 320);
  tft.setRotation(3); // 320x240 landscape
  
  pinMode(TFT_BLK, OUTPUT);
  analogWrite(TFT_BLK, 255); // Full brightness
  
  // Color test sequence
  Serial.println("Testing colors...");
  tft.fillScreen(UI_BACKGROUND);
  delay(500);
  
  // If colors look wrong, try alternative definitions
  if (false) { // Set to true if RGB565 doesn't work
    tft.fillScreen(NAVY_BLUE);
    delay(500);
    tft.fillScreen(ROYAL_BLUE);
    delay(500);
  }
  
  // Startup screen
  tft.fillScreen(UI_BACKGROUND);
  tft.setTextColor(UI_WHITE);
  tft.setTextSize(3);
  tft.setCursor(60, 80);
  tft.println("Filament Dryer");
  tft.setTextSize(2);
  tft.setTextColor(UI_ACCENT);
  tft.setCursor(90, 120);
  tft.println("by ColinPelkmans");
  delay(2000);
  tft.fillScreen(UI_BACKGROUND);
}

void showMainScreen(float airTemp, float bedTemp, int fanSpeed, const char* material, 
                   int progressPercent, int remainingHours, int remainingMinutes, bool isPaused) {
  tft.fillScreen(UI_BACKGROUND);
  
  // === TOP ROW WITH PROPER ICONS ===
  // Pause button
  tft.drawRect(15, 12, 100, 32, UI_WHITE);
  tft.drawRect(16, 13, 98, 30, UI_WHITE); // Double border
  drawPauseIcon(20, 18, UI_WHITE);
  tft.setTextSize(2);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(45, 22);
  tft.print("Pause");
  
  // Stop button
  tft.fillRect(130, 12, 70, 32, UI_GRAY);
  drawStopIcon(135, 18, UI_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(UI_BLACK);
  tft.setCursor(160, 22);
  tft.print("Stop");
  
  // Material display
  tft.setTextSize(2);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(220, 22);
  tft.print("=");
  tft.print(material);
  
  // === DIVIDER LINE ===
  tft.drawLine(15, 55, 305, 55, UI_WHITE);
  
  // === REMAINING TIME WITH CLOCK ICON ===
  drawClockIcon(15, 65, UI_WHITE);
  tft.setTextSize(2);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(40, 72);
  tft.print("Remaining:");
  
  // Large time display
  tft.setTextSize(3);
  tft.setCursor(200, 68);
  if (remainingHours < 10) tft.print("0");
  tft.print(remainingHours);
  tft.print(":");
  if (remainingMinutes < 10) tft.print("0");
  tft.print(remainingMinutes);
  
  // === PROGRESS BAR ===
  // Background
  tft.fillRect(15, 105, 290, 20, UI_DARK_BLUE);
  
  // Progress fill
  int progressWidth = (290 * progressPercent) / 100;
  if (progressWidth > 0) {
    tft.fillRect(15, 105, progressWidth, 20, UI_GREEN);
  }
  
  // Progress percentage (centered)
  tft.setTextSize(1);
  tft.setTextColor(UI_WHITE);
  char progressText[8];
  sprintf(progressText, "%d%%", progressPercent);
  int textWidth = strlen(progressText) * 6; // Approximate character width
  tft.setCursor(160 - textWidth/2, 112);
  tft.print(progressText);
  
  // === SENSOR DATA WITH ICONS ===
  int dataStartY = 140;
  int lineSpacing = 20;
  
  // Air temperature
  drawThermometerIcon(15, dataStartY, UI_WHITE);
  tft.setTextSize(2);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(40, dataStartY + 3);
  tft.print("Air:");
  tft.setCursor(220, dataStartY + 3);
  tft.print((int)airTemp);
  tft.print(" / 80°C");
  
  // Bed temperature
  drawFlameIcon(15, dataStartY + lineSpacing, UI_WHITE);
  tft.setCursor(40, dataStartY + lineSpacing + 3);
  tft.print("Bed:");
  tft.setCursor(250, dataStartY + lineSpacing + 3);
  tft.print((int)bedTemp);
  tft.print("°C");
  
  // Fan speed
  drawFanIcon(15, dataStartY + 2 * lineSpacing, UI_WHITE);
  tft.setCursor(40, dataStartY + 2 * lineSpacing + 3);
  tft.print("Fan:");
  tft.setCursor(270, dataStartY + 2 * lineSpacing + 3);
  tft.print(fanSpeed);
  tft.print("%");
}

void showPresetMenu(size_t selectedIdx) {
  tft.fillScreen(UI_BACKGROUND);
  
  // Title
  tft.setTextSize(2);
  tft.setCursor(15, 15);
  tft.setTextColor(UI_WHITE);
  tft.print("Select Material:");
  
  // Divider
  tft.drawLine(15, 45, 305, 45, UI_WHITE);
  
  // Preset list
  tft.setTextSize(2);
  int startY = 60;
  int itemHeight = 28;
  
  for (size_t i = 0; i < NUM_PRESETS && i < 5; ++i) {
    int y = startY + i * itemHeight;
    
    if (i == selectedIdx) {
      // Highlight selected item
      tft.fillRect(10, y - 2, 300, 24, UI_WHITE);
      tft.setTextColor(UI_BACKGROUND);
    } else {
      tft.setTextColor(UI_WHITE);
    }
    
    // Material name
    tft.setCursor(20, y);
    tft.print(presets[i].name);
    
    // Temperature
    tft.setCursor(120, y);
    tft.print((int)presets[i].targetTempC);
    tft.print("°C");
    
    // Duration
    tft.setCursor(200, y);
    int hours = presets[i].durationMin / 60;
    tft.print(hours);
    tft.print("h");
    
    int minutes = presets[i].durationMin % 60;
    if (minutes > 0) {
      tft.print(" ");
      tft.print(minutes);
      tft.print("m");
    }
  }
  
  // Instructions
  tft.setTextSize(1);
  tft.setTextColor(UI_ACCENT);
  tft.setCursor(15, 220);
  tft.print("Rotate to select, press to start drying");
}

void showDryingStatus() {
  // Legacy function - now handled by showMainScreen
}

void updateUI(float chamberTemp, float bedTemp) {
  // Debug output
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 2000) {
    Serial.print("Temps - Chamber: ");
    Serial.print(chamberTemp);
    Serial.print("°C, Bed: ");
    Serial.print(bedTemp);
    Serial.println("°C");
    lastDebug = millis();
  }
}
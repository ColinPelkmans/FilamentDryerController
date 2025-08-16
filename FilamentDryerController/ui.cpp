#include "ui.h"
#include "icons.h"
#include "colors.h"
#include "globals.h"
#include "presets.h"

void setupUI() {
  tft.init(240, 320);  // ST7789 initialization 
  tft.setRotation(3); // ✅ CHANGED: 1 = 320x240 landscape (was 3)
  
  // Startup screen - properly centered for landscape
  tft.fillScreen(UI_BACKGROUND);
  
  // Title "Filament Dryer" - centered for 320x240
  tft.setTextColor(UI_WHITE);
  tft.setTextSize(2);
  tft.setCursor(80, 80);  // Adjust if needed for landscape
  tft.println("Filament Dryer");
  
  // Subtitle "by Colin Pelkmans" - centered  
  tft.setTextSize(1);
  tft.setTextColor(UI_ACCENT);
  tft.setCursor(90, 120);  // Adjust if needed for landscape
  tft.println("by Colin Pelkmans");
  
  delay(2000);
  tft.fillScreen(UI_BACKGROUND);
}

// Rest of the functions stay the same...
void showPresetMenu(size_t selectedPresetIndex) {
  // Clear screen
  tft.fillScreen(UI_BACKGROUND);
  
  Serial.print("Drawing preset menu, selected: ");
  Serial.print(selectedPresetIndex);
  Serial.print(" (");
  Serial.print(getPreset(selectedPresetIndex).name);
  Serial.println(")");
  
  // Title
  tft.setTextSize(2);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(10, 10);
  tft.println("Select Material:");
  
  // Draw preset list
  int yPos = 50;
  int lineHeight = 30;
  
  for (size_t i = 0; i < getPresetCount(); i++) {
    const DryingPreset& preset = getPreset(i);
    
    // Highlight selected preset
    if (i == selectedPresetIndex) {
      // Draw highlight background - adjust width for landscape
      tft.fillRect(5, yPos - 5, 310, lineHeight, UI_DARK_BLUE);
      tft.setTextColor(UI_ACCENT);
      Serial.print(">>> Highlighting preset: ");
      Serial.println(preset.name);
    } else {
      tft.setTextColor(UI_WHITE);
    }
    
    // Draw preset name
    tft.setTextSize(2);
    tft.setCursor(15, yPos);
    tft.print(preset.name);
    
    // Draw preset details (smaller text)
    tft.setTextSize(1);
    tft.setCursor(15, yPos + 15);
    tft.print((int)preset.targetTempC);
    tft.print("°C, ");
    tft.print(preset.durationMin / 60);
    tft.print("h ");
    tft.print(preset.durationMin % 60);
    tft.print("m");
    
    yPos += lineHeight + 10;
  }
  
  // Instructions at bottom - adjust Y position for landscape
  tft.setTextSize(1);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(10, 210);  // Should fit in 240 height
  tft.println("Rotate to select, press to confirm");
  
  Serial.println("Preset menu draw complete");
}

void showMainScreen(float airTemp, float bedTemp, int fanSpeed, const char* material, 
                   int progressPercent, int remainingHours, int remainingMinutes, 
                   bool isPaused, MainScreenButton selectedButton) {
  
  // Always clear the entire screen first
  tft.fillScreen(UI_BACKGROUND);
  
  Serial.print("Drawing main screen with selected button: ");
  Serial.println(selectedButton);
  
  // === TOP ROW BUTTONS - TEXT HIGHLIGHTING ===
  
  // PAUSE BUTTON
  drawPauseIcon(15, 12, UI_WHITE);
  tft.setTextSize(1);
  // Highlight text if selected
  if (selectedButton == BUTTON_PAUSE) {
    tft.setTextColor(UI_ACCENT);
    Serial.println(">>> PAUSE button highlighted <<<");
  } else {
    tft.setTextColor(UI_WHITE);
  }
  tft.setCursor(35, 18);
  tft.print(isPaused ? "Resume" : "Pause");
  
  // STOP BUTTON
  drawStopIcon(105, 12, UI_WHITE);
  tft.setTextSize(1);
  // Highlight text if selected
  if (selectedButton == BUTTON_STOP) {
    tft.setTextColor(UI_ACCENT);
    Serial.println(">>> STOP button highlighted <<<");
  } else {
    tft.setTextColor(UI_WHITE);
  }
  tft.setCursor(125, 18);
  tft.print("Stop");
  
  // MATERIAL DISPLAY
  tft.setTextSize(1);
  // Highlight text if selected
  if (selectedButton == BUTTON_MATERIAL) {
    tft.setTextColor(UI_ACCENT);
    Serial.println(">>> MATERIAL button highlighted <<<");
  } else {
    tft.setTextColor(UI_WHITE);
  }
  tft.setCursor(170, 18);
  tft.print("Material: ");
  tft.print(material);
  
  // === DIVIDER LINE ===
  tft.drawLine(10, 45, 310, 45, UI_WHITE);  // Fits in 320 width
  
  // === REMAINING TIME ===
  drawClockIcon(10, 55, UI_WHITE);
  tft.setTextSize(1);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(30, 62);
  tft.print("Remaining:");
  
  // Large time display
  tft.setTextSize(2);
  tft.setCursor(240, 58);
  if (remainingHours < 10) tft.print("0");
  tft.print(remainingHours);
  tft.print(":");
  if (remainingMinutes < 10) tft.print("0");
  tft.print(remainingMinutes);
  
  // === PROGRESS BAR ===
  tft.fillRect(10, 85, 300, 15, UI_DARK_BLUE);  // Fits in 320 width
  
  int progressWidth = (300 * progressPercent) / 100;
  if (progressWidth > 0) {
    tft.fillRect(10, 85, progressWidth, 15, UI_GREEN);
  }
  
  // Progress percentage (centered)
  tft.setTextSize(1);
  tft.setTextColor(UI_WHITE);
  char progressText[8];
  sprintf(progressText, "%d%%", progressPercent);
  int textWidth = strlen(progressText) * 6;
  tft.setCursor(160 - textWidth/2, 90);
  tft.print(progressText);
  
  // === SENSOR DATA ===
  int dataStartY = 115;
  int lineSpacing = 25;
  
  // Air temperature
  drawThermometerIcon(10, dataStartY, UI_WHITE);
  tft.setTextSize(1);
  tft.setTextColor(UI_WHITE);
  tft.setCursor(30, dataStartY + 5);
  tft.print("Air:");
  tft.setCursor(220, dataStartY + 5);
  tft.print((int)airTemp);
  tft.print(" / 80°C");
  
  // Bed temperature
  drawFlameIcon(10, dataStartY + lineSpacing, UI_WHITE);
  tft.setCursor(30, dataStartY + lineSpacing + 5);
  tft.print("Bed:");
  tft.setCursor(250, dataStartY + lineSpacing + 5);
  tft.print((int)bedTemp);
  tft.print("°C");
  
  // Fan speed
  drawFanIcon(10, dataStartY + 2 * lineSpacing, UI_WHITE);
  tft.setCursor(30, dataStartY + 2 * lineSpacing + 5);
  tft.print("Fan:");
  tft.setCursor(270, dataStartY + 2 * lineSpacing + 5);
  tft.print(fanSpeed);
  tft.print("%");
  
  Serial.println("Main screen draw complete");
}

// Add the missing redrawMainScreen function
void redrawMainScreen() {
  float chamberTemp = getChamberTemp();
  float bedTemp = getBedTemp();
  
  showMainScreen(chamberTemp, bedTemp, 50, "PLA", 0, 0, 0, false, selectedMainButton);
}
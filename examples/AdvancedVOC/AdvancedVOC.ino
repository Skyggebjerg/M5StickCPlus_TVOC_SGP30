/*
 * Advanced VOC Monitor Example
 * 
 * Advanced example with:
 * - EEPROM baseline storage
 * - Multiple display modes
 * - Button controls
 * - Data logging
 */

#include <M5StickCPlus2.h>
#include <Preferences.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;
Preferences preferences;

// Display modes
enum DisplayMode {
  MODE_CURRENT,
  MODE_GRAPH,
  MODE_STATS
};

DisplayMode currentMode = MODE_CURRENT;

// Statistics
uint16_t minTVOC = 65535;
uint16_t maxTVOC = 0;
uint32_t avgTVOC = 0;
uint32_t sampleCount = 0;

// Graph data
#define GRAPH_POINTS 100
uint16_t graphData[GRAPH_POINTS] = {0};
uint8_t graphIndex = 0;

// Timing
unsigned long lastMeasurement = 0;
unsigned long lastBaselineSave = 0;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  
  M5.Lcd.setRotation(1);
  M5.Lcd.setBrightness(128);
  Serial.begin(115200);
  Wire.begin(32, 33);
  
  // Initialize preferences
  preferences.begin("sgp30", false);
  
  // Initialize sensor
  if (!sgp.begin()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println("Sensor Error!");
    while (1);
  }
  
  // Load baseline from EEPROM
  uint16_t eco2_base = preferences.getUShort("eco2_base", 0);
  uint16_t tvoc_base = preferences.getUShort("tvoc_base", 0);
  
  if (eco2_base != 0 && tvoc_base != 0) {
    sgp.setIAQBaseline(eco2_base, tvoc_base);
    Serial.println("Loaded baseline from EEPROM");
  }
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("VOC Monitor Ready");
  M5.Lcd.println("BtnA: Change Mode");
  M5.Lcd.println("BtnB: Reset Stats");
  delay(2000);
}

void loop() {
  M5.update();
  
  // Button A: Change display mode
  if (M5.BtnA.wasPressed()) {
    currentMode = (DisplayMode)((currentMode + 1) % 3);
    M5.Lcd.fillScreen(BLACK);
  }
  
  // Button B: Reset statistics
  if (M5.BtnB.wasPressed()) {
    minTVOC = 65535;
    maxTVOC = 0;
    avgTVOC = 0;
    sampleCount = 0;
    for (int i = 0; i < GRAPH_POINTS; i++) {
      graphData[i] = 0;
    }
    graphIndex = 0;
    M5.Lcd.fillScreen(BLACK);
  }
  
  // Measure every second
  if (millis() - lastMeasurement >= 1000) {
    lastMeasurement = millis();
    
    if (sgp.IAQmeasure()) {
      uint16_t tvoc = sgp.TVOC;
      uint16_t eco2 = sgp.eCO2;
      
      // Update statistics
      if (tvoc < minTVOC) minTVOC = tvoc;
      if (tvoc > maxTVOC) maxTVOC = tvoc;
      avgTVOC = (avgTVOC * sampleCount + tvoc) / (sampleCount + 1);
      sampleCount++;
      
      // Update graph
      graphData[graphIndex] = tvoc;
      graphIndex = (graphIndex + 1) % GRAPH_POINTS;
      
      // Display based on mode
      switch (currentMode) {
        case MODE_CURRENT:
          displayCurrent(tvoc, eco2);
          break;
        case MODE_GRAPH:
          displayGraph();
          break;
        case MODE_STATS:
          displayStats();
          break;
      }
      
      // Log to serial
      Serial.printf("TVOC: %d ppb, eCO2: %d ppm\n", tvoc, eco2);
    }
  }
  
  // Save baseline every hour
  if (millis() - lastBaselineSave >= 3600000) {
    lastBaselineSave = millis();
    saveBaseline();
  }
  
  delay(10);
}

void displayCurrent(uint16_t tvoc, uint16_t eco2) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(CYAN);
  M5.Lcd.setCursor(10, 5);
  M5.Lcd.println("Current");
  
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(10, 35);
  M5.Lcd.print("TVOC:");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setCursor(10, 55);
  M5.Lcd.print(tvoc);
  M5.Lcd.print(" ppb");
  
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(10, 85);
  M5.Lcd.print("eCO2:");
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setCursor(10, 105);
  M5.Lcd.print(eco2);
  M5.Lcd.print(" ppm");
}

void displayGraph() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(CYAN);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.println("TVOC Graph");
  
  // Draw graph
  int graphHeight = 100;
  int graphY = 130;
  uint16_t maxVal = 1000; // Scale
  
  for (int i = 0; i < GRAPH_POINTS - 1; i++) {
    int x1 = i * 2;
    int x2 = (i + 1) * 2;
    int y1 = graphY - (graphData[i] * graphHeight / maxVal);
    int y2 = graphY - (graphData[i + 1] * graphHeight / maxVal);
    
    if (y1 < 30) y1 = 30;
    if (y2 < 30) y2 = 30;
    
    M5.Lcd.drawLine(x1, y1, x2, y2, GREEN);
  }
  
  // Draw axis
  M5.Lcd.drawLine(0, graphY, M5.Lcd.width(), graphY, WHITE);
}

void displayStats() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(CYAN);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.println("Statistics");
  
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(5, 30);
  M5.Lcd.printf("Samples: %u", sampleCount);
  
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.printf("Min TVOC: %u ppb", minTVOC);
  
  M5.Lcd.setCursor(5, 70);
  M5.Lcd.printf("Max TVOC: %u ppb", maxTVOC);
  
  M5.Lcd.setCursor(5, 90);
  M5.Lcd.printf("Avg TVOC: %u ppb", avgTVOC);
  
  M5.Lcd.setCursor(5, 120);
  M5.Lcd.print("Press B to reset");
}

void saveBaseline() {
  uint16_t eco2_base, tvoc_base;
  if (sgp.getIAQBaseline(&eco2_base, &tvoc_base)) {
    preferences.putUShort("eco2_base", eco2_base);
    preferences.putUShort("tvoc_base", tvoc_base);
    Serial.printf("Baseline saved: eCO2=0x%04X, TVOC=0x%04X\n", eco2_base, tvoc_base);
  }
}

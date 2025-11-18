/*
 * M5StickC Plus2 TVOC SGP30 Sensor
 * 
 * This sketch reads VOC (Volatile Organic Compounds) data from the SGP30 sensor
 * and displays it on the M5StickC Plus2 screen.
 * 
 * Hardware Requirements:
 * - M5StickC Plus2
 * - SGP30 TVOC Sensor (I2C connection)
 * 
 * Libraries Required:
 * - M5StickCPlus2 (for M5StickC Plus2 support)
 * - Adafruit SGP30 Sensor Library
 */

#include <M5StickCPlus2.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"

// Create SGP30 sensor object
Adafruit_SGP30 sgp;

// Variables for sensor readings
uint16_t TVOC = 0;
uint16_t eCO2 = 0;

// Timing variables
unsigned long lastMeasurement = 0;
const unsigned long measurementInterval = 1000; // Read every 1 second

// Counter for baseline save (every 12 hours as recommended)
uint32_t counter = 0;
const uint32_t baselineSaveInterval = 43200; // 12 hours in seconds

// Baseline values (stored in memory)
uint16_t eco2_baseline = 0;
uint16_t tvoc_baseline = 0;

void setup() {
  // Initialize M5StickC Plus2
  auto cfg = M5.config();
  M5.begin(cfg);
  
  // Set display brightness
  M5.Lcd.setBrightness(128);
  
  // Set text properties
  M5.Lcd.setRotation(1);  // Landscape mode
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);
  
  // Display startup message
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.println("M5StickC Plus2");
  M5.Lcd.setCursor(10, 30);
  M5.Lcd.println("TVOC SGP30");
  M5.Lcd.setCursor(10, 50);
  M5.Lcd.println("Initializing...");
  
  // Initialize Serial for debugging
  Serial.begin(115200);
  Serial.println("SGP30 TVOC Sensor Test");

  // Initialize I2C
  Wire.begin(32, 33); // SDA=GPIO32, SCL=GPIO33 for M5StickC Plus2
  
  // Initialize SGP30 sensor
  if (!sgp.begin()) {
    Serial.println("SGP30 sensor not found!");
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.println("Sensor Error!");
    M5.Lcd.setCursor(10, 50);
    M5.Lcd.println("Check I2C");
    while (1); // Stop here
  }
  
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  // Initialize baseline (optional - can be loaded from EEPROM/preferences)
  // sgp.setIAQBaseline(eco2_baseline, tvoc_baseline);
  
  delay(1000);
  
  // Clear screen for measurements
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.update();
  
  // Check if it's time for a new measurement
  if (millis() - lastMeasurement >= measurementInterval) {
    lastMeasurement = millis();
    
    // Read sensor data
    if (!sgp.IAQmeasure()) {
      Serial.println("Measurement failed");
      return;
    }
    
    TVOC = sgp.TVOC;
    eCO2 = sgp.eCO2;
    
    // Display readings on screen
    displayReadings();
    
    // Print to serial
    Serial.print("TVOC: ");
    Serial.print(TVOC);
    Serial.print(" ppb\t");
    Serial.print("eCO2: ");
    Serial.print(eCO2);
    Serial.println(" ppm");
    
    // Raw H2 and Ethanol readings (optional)
    if (!sgp.IAQmeasureRaw()) {
      Serial.println("Raw measurement failed");
    } else {
      Serial.print("Raw H2: ");
      Serial.print(sgp.rawH2);
      Serial.print("\t");
      Serial.print("Raw Ethanol: ");
      Serial.println(sgp.rawEthanol);
    }
    
    // Save baseline periodically (every 12 hours)
    counter++;
    if (counter >= baselineSaveInterval) {
      counter = 0;
      
      uint16_t eco2_base, tvoc_base;
      if (!sgp.getIAQBaseline(&eco2_base, &tvoc_base)) {
        Serial.println("Failed to get baseline readings");
      } else {
        Serial.print("Baseline values: eCO2: 0x");
        Serial.print(eco2_base, HEX);
        Serial.print(" & TVOC: 0x");
        Serial.println(tvoc_base, HEX);
        // Here you could save these to EEPROM/Preferences for persistence
        eco2_baseline = eco2_base;
        tvoc_baseline = tvoc_base;
      }
    }
  }
  
  delay(10);
}

void displayReadings() {
  // Clear previous readings area
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), BLACK);
  
  // Title
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(CYAN, BLACK);
  M5.Lcd.setCursor(20, 5);
  M5.Lcd.println("VOC Monitor");
  
  // TVOC value
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(10, 35);
  M5.Lcd.println("TVOC:");
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(10, 55);
  M5.Lcd.print(TVOC);
  M5.Lcd.print(" ppb");
  
  // eCO2 value
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(10, 85);
  M5.Lcd.println("eCO2:");
  M5.Lcd.setTextColor(YELLOW, BLACK);
  M5.Lcd.setCursor(10, 105);
  M5.Lcd.print(eCO2);
  M5.Lcd.print(" ppm");
  
  // Air quality indicator
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(150, 120);
  
  // Simple air quality assessment based on TVOC levels
  if (TVOC <= 65) {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.print("Excellent");
  } else if (TVOC <= 220) {
    M5.Lcd.setTextColor(GREENYELLOW, BLACK);
    M5.Lcd.print("Good");
  } else if (TVOC <= 660) {
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.print("Moderate");
  } else if (TVOC <= 2200) {
    M5.Lcd.setTextColor(ORANGE, BLACK);
    M5.Lcd.print("Poor");
  } else {
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.print("Unhealthy");
  }
}

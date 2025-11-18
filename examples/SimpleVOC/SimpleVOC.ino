/*
 * Simple VOC Monitor Example
 * 
 * Basic example showing minimal code to read and display VOC data
 */

#include <M5StickCPlus2.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  
  Serial.begin(115200);
  Wire.begin(32, 33);
  
  if (!sgp.begin()) {
    M5.Lcd.println("Sensor Error!");
    while (1);
  }
  
  M5.Lcd.println("Ready!");
  delay(1000);
}

void loop() {
  M5.update();
  
  if (sgp.IAQmeasure()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.print("TVOC: ");
    M5.Lcd.println(sgp.TVOC);
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.print("eCO2: ");
    M5.Lcd.println(sgp.eCO2);
  }
  
  delay(1000);
}

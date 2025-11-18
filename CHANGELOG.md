# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-11-18

### Added
- Initial release of M5StickC Plus2 TVOC SGP30 sensor project
- Main sketch for reading and displaying VOC data
- Real-time TVOC (Total Volatile Organic Compounds) measurement in ppb
- eCO2 (equivalent CO2) measurement in ppm
- Color-coded air quality indicator on display
- Automatic baseline calibration support
- Serial output for debugging and data logging
- Simple example sketch for basic functionality
- Advanced example sketch with:
  - EEPROM baseline storage using Preferences
  - Multiple display modes (Current, Graph, Statistics)
  - Button controls for mode switching
  - Statistical tracking (min, max, average)
  - Graphical TVOC visualization
- PlatformIO configuration for easy building
- Arduino IDE support with library.properties
- Comprehensive documentation:
  - README with full feature list and installation instructions
  - QUICKSTART guide for 5-minute setup
  - WIRING guide with connection diagrams
  - VERIFICATION guide for testing and troubleshooting
- MIT License
- Keywords file for Arduino IDE syntax highlighting
- Library metadata files (library.json, library.properties)

### Dependencies
- M5StickCPlus2 ^1.0.0
- Adafruit SGP30 Sensor ^2.0.0
- Adafruit BusIO ^1.14.1

### Hardware Support
- M5StickC Plus2 (ESP32-based)
- SGP30 TVOC sensor (I2C address 0x58)

### Technical Details
- I2C communication on GPIO 32 (SDA) and GPIO 33 (SCL)
- Update rate: 1 Hz (once per second)
- Baseline save interval: 12 hours
- Display: Color LCD with landscape orientation
- Serial baud rate: 115200

## Future Enhancements

Potential features for future releases:
- WiFi connectivity for remote monitoring
- MQTT support for IoT integration
- Data logging to SD card
- Web interface for real-time monitoring
- Configurable alert thresholds
- Historical data visualization
- Multiple sensor support
- Battery level indicator
- Sleep mode for extended battery life
- OTA (Over-The-Air) updates

[1.0.0]: https://github.com/Skyggebjerg/M5StickCPlus_TVOC_SGP30/releases/tag/v1.0.0

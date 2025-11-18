# M5StickC Plus2 TVOC SGP30 Sensor

A M5StickC Plus2 project that measures VOC (Volatile Organic Compounds) from the SGP30 sensor and displays the readings on the built-in screen.

## Features

- Real-time TVOC (Total Volatile Organic Compounds) measurement in ppb (parts per billion)
- eCO2 (equivalent CO2) measurement in ppm (parts per million)
- Color-coded air quality indicator
- Automatic baseline calibration for improved accuracy
- Serial output for debugging and data logging

## Hardware Requirements

- **M5StickC Plus2** - ESP32-based development board with built-in display
- **SGP30 TVOC Sensor** - I2C-based air quality sensor

## Wiring

Connect the SGP30 sensor to the M5StickC Plus2 via I2C:

| SGP30 Pin | M5StickC Plus2 Pin |
|-----------|-------------------|
| VCC       | 3.3V              |
| GND       | GND               |
| SDA       | GPIO 32           |
| SCL       | GPIO 33           |

## Software Requirements

### Required Libraries

1. **M5StickCPlus2** - M5StickC Plus2 support library
2. **Adafruit SGP30 Sensor** - SGP30 sensor driver
3. **Adafruit BusIO** - I2C/SPI communication library

### Installation

#### Using PlatformIO (Recommended)

1. Clone this repository:
   ```bash
   git clone https://github.com/Skyggebjerg/M5StickCPlus_TVOC_SGP30.git
   cd M5StickCPlus_TVOC_SGP30
   ```

2. Build and upload using PlatformIO:
   ```bash
   pio run --target upload
   ```

3. Monitor serial output (optional):
   ```bash
   pio device monitor
   ```

#### Using Arduino IDE

1. Install the required libraries through Library Manager:
   - M5StickCPlus2
   - Adafruit SGP30 Sensor
   - Adafruit BusIO

2. Open `M5StickCPlus_TVOC_SGP30/M5StickCPlus_TVOC_SGP30.ino`

3. Select board: **M5Stick-C** or **ESP32 Dev Module**

4. Upload to your M5StickC Plus2

## Usage

1. Connect the SGP30 sensor to the M5StickC Plus2 as described in the wiring section
2. Power on the M5StickC Plus2
3. The device will initialize and begin displaying air quality measurements
4. Readings update every second

### Display Information

The screen shows:
- **TVOC**: Total Volatile Organic Compounds in ppb
- **eCO2**: Equivalent CO2 in ppm
- **Air Quality**: Text indicator (Excellent, Good, Moderate, Poor, Unhealthy)

### Air Quality Levels

| TVOC (ppb) | Air Quality |
|------------|-------------|
| 0-65       | Excellent   |
| 66-220     | Good        |
| 221-660    | Moderate    |
| 661-2200   | Poor        |
| >2200      | Unhealthy   |

## Technical Details

### Sensor Warm-up

The SGP30 sensor requires a warm-up period:
- Initial readings may be inaccurate for the first 15 seconds
- Full accuracy achieved after 12 hours of continuous operation
- The sensor automatically saves baseline values every 12 hours

### Baseline Calibration

The SGP30 uses an automatic baseline compensation algorithm:
- Runs continuously in the background
- Adapts to the environment over time
- For best results, expose the sensor to "good air" periodically

### Serial Output

Connect via USB to view detailed sensor data:
- TVOC and eCO2 values
- Raw H2 and Ethanol sensor readings
- Baseline calibration values
- Debug information

Baud rate: **115200**

## Troubleshooting

### "Sensor Error!" on display

- Check I2C wiring (SDA to GPIO32, SCL to GPIO33)
- Verify sensor power (3.3V)
- Ensure SGP30 sensor is properly connected
- Try resetting the M5StickC Plus2

### Readings seem incorrect

- Allow 15 seconds for sensor warm-up
- For accurate readings, let sensor run for 12+ hours
- Ensure good ventilation around the sensor
- Avoid placing sensor near heat sources

### Compilation errors

- Verify all required libraries are installed
- Check library versions match requirements
- Ensure ESP32 board support is installed

## License

This project is open source and available for modification and redistribution.

## Contributing

Feel free to submit issues and enhancement requests!

## Acknowledgments

- M5Stack for the M5StickC Plus2 platform
- Adafruit for the SGP30 sensor library
- Sensirion for the SGP30 sensor

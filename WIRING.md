# Hardware Connection Guide

## SGP30 Sensor to M5StickC Plus2 Wiring

### Pin Connections

```
SGP30 Sensor          M5StickC Plus2
┌──────────┐         ┌──────────────┐
│   VCC    │────────>│    3.3V      │
│   GND    │────────>│    GND       │
│   SDA    │<───────>│  GPIO 32     │
│   SCL    │────────>│  GPIO 33     │
└──────────┘         └──────────────┘
```

### Important Notes

1. **Voltage**: The SGP30 operates at 3.3V. Do NOT connect to 5V.

2. **I2C Address**: The SGP30 has a fixed I2C address of 0x58.

3. **Pull-up Resistors**: Most SGP30 breakout boards include built-in pull-up resistors for I2C communication. If yours doesn't, add 4.7kΩ resistors between SDA/SCL and 3.3V.

4. **Port Selection**: M5StickC Plus2 has multiple I2C ports:
   - Internal I2C (for built-in components)
   - External I2C (Grove/HAT connector): GPIO 32 (SDA), GPIO 33 (SCL)
   
   This project uses GPIO 32/33 for external sensor connection.

### Physical Connection Options

#### Option 1: Direct Wire Connection
- Use jumper wires to connect sensor pins directly to M5StickC Plus2 header pins
- Ensure solid connections to avoid communication errors

#### Option 2: Grove Connector (Recommended)
- If your SGP30 sensor has a Grove connector, use the M5StickC Plus2 Grove port
- This provides a secure, plug-and-play connection

#### Option 3: HAT Module
- Mount the sensor on a custom HAT for M5StickC Plus2
- Provides compact integration and better portability

### Testing the Connection

After wiring, you can test I2C communication:

1. Upload and run the sketch
2. Check Serial Monitor (115200 baud)
3. You should see the SGP30 serial number on successful connection
4. If "Sensor not found" appears, check wiring and connections

### Troubleshooting Wiring Issues

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| "Sensor not found" | Loose connection | Check all wire connections |
| "Sensor not found" | Wrong pins | Verify GPIO 32 (SDA) and GPIO 33 (SCL) |
| Erratic readings | Interference | Shorten I2C wires, add 100nF capacitor near VCC |
| No power | Incorrect voltage | Check 3.3V connection, not 5V |
| Random failures | Missing pull-ups | Add 4.7kΩ resistors to SDA/SCL |

### Power Considerations

- The SGP30 consumes approximately 48mA during measurement
- M5StickC Plus2 can supply sufficient current via 3.3V pin
- For battery operation, expect ~6-8 hours depending on screen brightness
- Consider using external battery or USB power for extended operation

# Verification and Testing Guide

This guide helps you verify that your M5StickC Plus2 TVOC SGP30 setup is working correctly.

## Pre-Upload Checklist

Before uploading the code, verify:

- [ ] M5StickC Plus2 is powered on and functioning
- [ ] SGP30 sensor is properly wired (see WIRING.md)
- [ ] All required libraries are installed
- [ ] Correct board is selected in Arduino IDE or PlatformIO

## Post-Upload Verification

### 1. Startup Sequence

After uploading, you should see:

1. **Initialization Screen** (2-3 seconds)
   - "M5StickC Plus2"
   - "TVOC SGP30"
   - "Initializing..."

2. **Successful Connection**
   - If successful, display clears and shows live readings
   - Serial monitor shows: "Found SGP30 serial #XXXXXX"

3. **Error State** (if sensor not detected)
   - Display shows: "Sensor Error! Check I2C"
   - Red text indicates connection problem

### 2. Normal Operation Display

The main display should show:

```
┌─────────────────────────┐
│   VOC Monitor           │
│                         │
│   TVOC:                 │
│   XXX ppb               │
│                         │
│   eCO2:                 │
│   XXX ppm               │
│                         │
│           [Air Quality] │
└─────────────────────────┘
```

### 3. Expected Readings

#### Initial Readings (First 15 seconds)
- TVOC: Typically 0-50 ppb
- eCO2: Around 400 ppm
- These may be inaccurate during warm-up

#### Normal Indoor Air (After warm-up)
- TVOC: 0-220 ppb (Good quality)
- eCO2: 400-1000 ppm
- Air Quality: "Excellent" or "Good"

#### Poor Air Quality Indicators
- TVOC: >660 ppb
- eCO2: >1500 ppm
- Air Quality: "Poor" or "Unhealthy"

### 4. Serial Monitor Output

Connect via USB and open Serial Monitor (115200 baud):

Expected output every second:
```
SGP30 TVOC Sensor Test
Found SGP30 serial #01234567
TVOC: 45 ppb    eCO2: 456 ppm
Raw H2: 12345   Raw Ethanol: 23456
TVOC: 47 ppb    eCO2: 458 ppm
Raw H2: 12347   Raw Ethanol: 23458
...
```

Every 12 hours, you should see:
```
Baseline values: eCO2: 0x8B92 & TVOC: 0x8F3C
```

## Testing Scenarios

### Test 1: Sensor Response to Air Quality Change

1. Let the sensor stabilize for 5 minutes in normal air
2. Note the baseline TVOC reading
3. Introduce a VOC source (rubbing alcohol, hand sanitizer, etc.)
4. TVOC reading should increase within 10-30 seconds
5. Remove VOC source and wait
6. TVOC should gradually decrease back to baseline

**Expected behavior:**
- TVOC increases: ✓ Working
- TVOC doesn't change: ✗ Sensor issue

### Test 2: Display Update Rate

1. Watch the display for 10 seconds
2. Values should update approximately once per second
3. Numbers should change smoothly

**Expected behavior:**
- Updates every ~1 second: ✓ Working
- Frozen display: ✗ Code issue
- Erratic updates: ✗ Check connections

### Test 3: Power Cycle

1. Power off the M5StickC Plus2
2. Wait 10 seconds
3. Power back on
4. Sensor should re-initialize and start reading

**Expected behavior:**
- Restarts normally: ✓ Working
- Doesn't initialize: ✗ Wiring issue

## Troubleshooting

### Issue: "Sensor Error!" on display

**Possible causes:**
1. SGP30 not connected
2. Wrong I2C pins
3. Insufficient power
4. Faulty sensor

**Solutions:**
1. Verify wiring matches WIRING.md
2. Check GPIO 32 (SDA) and GPIO 33 (SCL)
3. Ensure 3.3V connection is solid
4. Try another sensor if available

### Issue: Readings always zero

**Possible causes:**
1. Sensor needs warm-up time
2. Communication errors
3. Incorrect library version

**Solutions:**
1. Wait 15-30 seconds after startup
2. Check Serial Monitor for errors
3. Update Adafruit SGP30 library

### Issue: Readings seem too high or too low

**Possible causes:**
1. Sensor not calibrated (first use)
2. Environmental factors
3. Baseline not loaded

**Solutions:**
1. Let run for 12-24 hours to establish baseline
2. Compare with another air quality sensor
3. Ensure good ventilation during calibration

### Issue: Display is blank

**Possible causes:**
1. Brightness set too low
2. Display initialization failed
3. M5StickC Plus2 issue

**Solutions:**
1. Check M5.Lcd.setBrightness() value
2. Try simple M5 test sketch
3. Reset M5StickC Plus2

### Issue: Serial Monitor shows gibberish

**Possible causes:**
1. Wrong baud rate
2. Serial port conflict

**Solutions:**
1. Set to 115200 baud
2. Close other programs using serial port

## Performance Benchmarks

### Expected Performance

| Metric | Expected Value |
|--------|---------------|
| Update Rate | 1 Hz (1 per second) |
| Warm-up Time | 15 seconds |
| Calibration Time | 12-24 hours |
| Response Time | 10-30 seconds |
| Recovery Time | 1-5 minutes |
| Power Consumption | ~150mA (with display) |

### I2C Communication Check

If you have an I2C scanner sketch, the SGP30 should appear at:
- **Address: 0x58** (88 decimal)

## Advanced Verification

### Memory Usage Check

Add to Serial Monitor output:
```cpp
Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
```

Expected: >200KB free heap

### Sensor Self-Test

The SGP30 has a built-in self-test. Add after `sgp.begin()`:
```cpp
if (sgp.IAQmeasureRaw()) {
  Serial.println("Self-test passed");
} else {
  Serial.println("Self-test failed");
}
```

## Success Criteria

Your setup is working correctly if:

- ✓ Display shows "VOC Monitor" title
- ✓ TVOC and eCO2 values update every second
- ✓ Values are in reasonable ranges (TVOC: 0-1000, eCO2: 400-2000)
- ✓ Air quality indicator shows appropriate color
- ✓ Serial monitor shows sensor serial number on startup
- ✓ Sensor responds to air quality changes
- ✓ No error messages in serial monitor

## Getting Help

If you continue to have issues:

1. Check GitHub Issues for similar problems
2. Provide the following information:
   - M5StickC Plus2 model/version
   - SGP30 sensor model
   - Library versions used
   - Serial Monitor output
   - Photo of wiring setup

## Next Steps

Once verified:
- Try the AdvancedVOC example for more features
- Customize display colors and layout
- Implement data logging to SD card
- Add WiFi connectivity for remote monitoring

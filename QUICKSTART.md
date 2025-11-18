# Quick Start Guide

Get your M5StickC Plus2 TVOC monitor running in 5 minutes!

## What You Need

- M5StickC Plus2 device
- SGP30 TVOC sensor module
- 4 jumper wires (if not using Grove connector)
- USB-C cable for programming

## Step 1: Wire the Sensor (2 minutes)

Connect SGP30 to M5StickC Plus2:

```
SGP30 → M5StickC Plus2
VCC   → 3.3V
GND   → GND
SDA   → GPIO 32
SCL   → GPIO 33
```

**Using Grove connector?** Just plug it in!

## Step 2: Install Software (2 minutes)

### Option A: PlatformIO (Recommended)

```bash
# Clone repository
git clone https://github.com/Skyggebjerg/M5StickCPlus_TVOC_SGP30.git
cd M5StickCPlus_TVOC_SGP30

# Build and upload
pio run --target upload
```

### Option B: Arduino IDE

1. Open Arduino IDE
2. Install libraries via Library Manager:
   - M5StickCPlus2
   - Adafruit SGP30 Sensor
   - Adafruit BusIO
3. Open: `M5StickCPlus_TVOC_SGP30/M5StickCPlus_TVOC_SGP30.ino`
4. Select board: **M5Stick-C**
5. Click **Upload**

## Step 3: Run (1 minute)

1. Wait for upload to complete
2. Device will restart automatically
3. You should see:
   - "M5StickC Plus2"
   - "TVOC SGP30"
   - "Initializing..."
4. Then live readings appear!

## What You Should See

```
┌──────────────────┐
│  VOC Monitor     │
│                  │
│  TVOC:           │
│  45 ppb          │
│                  │
│  eCO2:           │
│  456 ppm         │
│                  │
│       Excellent  │
└──────────────────┘
```

## Troubleshooting

### "Sensor Error!" displayed?

1. Check wiring (especially GPIO 32 and 33)
2. Verify 3.3V power connection
3. Try unplugging and replugging sensor

### Still having issues?

See [VERIFICATION.md](VERIFICATION.md) for detailed troubleshooting.

## Next Steps

- **Try Advanced Mode**: Upload `examples/AdvancedVOC/AdvancedVOC.ino` for graphs and statistics
- **Test the Sensor**: Bring rubbing alcohol near sensor and watch TVOC increase
- **Read the Docs**: Check [README.md](README.md) for all features

## Understanding Your Readings

| TVOC (ppb) | Air Quality | What It Means |
|------------|-------------|---------------|
| 0-65       | Excellent   | Clean air, great! |
| 66-220     | Good        | Normal indoor air |
| 221-660    | Moderate    | Some pollutants present |
| 661-2200   | Poor        | Significant pollutants |
| >2200      | Unhealthy   | High pollution, ventilate! |

## Tips

- **First Use**: Sensor needs 15 seconds to warm up
- **Best Results**: Let run for 12+ hours for accurate baseline
- **Calibration**: Expose to fresh air periodically
- **Testing**: Use hand sanitizer to test sensor response

## Common Questions

**Q: Why do readings start at zero?**
A: Sensor needs 15-30 seconds to warm up. This is normal.

**Q: Can I use it on battery?**
A: Yes! Expect 6-8 hours on internal battery, more with external.

**Q: How often should I calibrate?**
A: Automatic! The sensor self-calibrates every 12 hours.

**Q: Is it accurate?**
A: Very good for relative measurements. Not a replacement for certified lab equipment.

## Getting Help

- Check [VERIFICATION.md](VERIFICATION.md) for testing steps
- Check [WIRING.md](WIRING.md) for connection details  
- Open an [issue on GitHub](https://github.com/Skyggebjerg/M5StickCPlus_TVOC_SGP30/issues)

## Serial Monitor (Optional)

Want more data? Connect via USB and open Serial Monitor at **115200 baud**:

```
SGP30 TVOC Sensor Test
Found SGP30 serial #01234567
TVOC: 45 ppb    eCO2: 456 ppm
Raw H2: 12345   Raw Ethanol: 23456
```

---

**Enjoy your new air quality monitor! 🌿**

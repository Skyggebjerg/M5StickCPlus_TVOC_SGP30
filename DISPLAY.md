# Display Mockup and UI Reference

This document shows what you'll see on the M5StickC Plus2 display.

## Main Display Layout

```
╔════════════════════════════════════════╗
║  VOC Monitor                           ║  <- Title (Cyan, Size 2)
║                                        ║
║  TVOC:                                 ║  <- Label (White, Size 2)
║  45 ppb                                ║  <- Value (Green, Size 2)
║                                        ║
║  eCO2:                                 ║  <- Label (White, Size 2)
║  456 ppm                               ║  <- Value (Yellow, Size 2)
║                                        ║
║                           Excellent    ║  <- Air Quality (Green, Size 1)
╚════════════════════════════════════════╝
```

### Display Specifications
- **Resolution**: 240x135 pixels
- **Orientation**: Landscape (Rotation 1)
- **Background**: Black
- **Brightness**: 128 (50%)
- **Update Rate**: 1 second

## Color Scheme

### Air Quality Indicator Colors

| Air Quality | TVOC Range | Color Code | RGB Hex |
|-------------|------------|------------|---------|
| Excellent   | 0-65 ppb   | GREEN      | #00FF00 |
| Good        | 66-220 ppb | GREENYELLOW| #ADFF2F |
| Moderate    | 221-660 ppb| YELLOW     | #FFFF00 |
| Poor        | 661-2200 ppb| ORANGE    | #FFA500 |
| Unhealthy   | >2200 ppb  | RED        | #FF0000 |

### Text Colors
- **Title**: CYAN (#00FFFF)
- **Labels**: WHITE (#FFFFFF)
- **TVOC Value**: GREEN (#00FF00)
- **eCO2 Value**: YELLOW (#FFFF00)
- **Error Messages**: RED (#FF0000)

## Startup Sequence

### 1. Initialization Screen (1-2 seconds)
```
╔════════════════════════════════════════╗
║                                        ║
║  M5StickC Plus2                        ║
║  TVOC SGP30                            ║
║  Initializing...                       ║
║                                        ║
║                                        ║
║                                        ║
╚════════════════════════════════════════╝
```

### 2. Sensor Detection Success
Transitions to main display showing live readings.

### 3. Sensor Error Screen
```
╔════════════════════════════════════════╗
║                                        ║
║                                        ║
║  Sensor Error!                         ║  <- Red text
║  Check I2C                             ║  <- Red text
║                                        ║
║                                        ║
║                                        ║
╚════════════════════════════════════════╝
```

## Advanced Mode Displays

### Mode 1: Current Readings (Same as Main)
```
╔════════════════════════════════════════╗
║  Current                               ║
║                                        ║
║  TVOC:                                 ║
║  45 ppb                                ║
║                                        ║
║  eCO2:                                 ║
║  456 ppm                               ║
╚════════════════════════════════════════╝
```

### Mode 2: Graph View
```
╔════════════════════════════════════════╗
║  TVOC Graph                            ║
║         ╱╲                             ║
║        ╱  ╲      ╱╲                    ║
║       ╱    ╲    ╱  ╲                   ║
║      ╱      ╲  ╱    ╲                  ║
║     ╱        ╲╱      ╲                 ║
║────────────────────────────────────────║
╚════════════════════════════════════════╝
```

### Mode 3: Statistics View
```
╔════════════════════════════════════════╗
║  Statistics                            ║
║                                        ║
║  Samples: 1234                         ║
║                                        ║
║  Min TVOC: 12 ppb                      ║
║                                        ║
║  Max TVOC: 345 ppb                     ║
║                                        ║
║  Avg TVOC: 78 ppb                      ║
║                                        ║
║  Press B to reset                      ║
╚════════════════════════════════════════╝
```

## Example Reading Scenarios

### Scenario 1: Clean Indoor Air
```
╔════════════════════════════════════════╗
║  VOC Monitor                           ║
║                                        ║
║  TVOC:                                 ║
║  32 ppb                                ║
║                                        ║
║  eCO2:                                 ║
║  415 ppm                               ║
║                                        ║
║                           Excellent    ║  <- GREEN
╚════════════════════════════════════════╝
```

### Scenario 2: Normal Office Environment
```
╔════════════════════════════════════════╗
║  VOC Monitor                           ║
║                                        ║
║  TVOC:                                 ║
║  125 ppb                               ║
║                                        ║
║  eCO2:                                 ║
║  678 ppm                               ║
║                                        ║
║                           Good         ║  <- GREENYELLOW
╚════════════════════════════════════════╝
```

### Scenario 3: Elevated VOC (Cleaning Products)
```
╔════════════════════════════════════════╗
║  VOC Monitor                           ║
║                                        ║
║  TVOC:                                 ║
║  890 ppb                               ║
║                                        ║
║  eCO2:                                 ║
║  1234 ppm                              ║
║                                        ║
║                           Poor         ║  <- ORANGE
╚════════════════════════════════════════╝
```

### Scenario 4: High VOC (Poor Ventilation)
```
╔════════════════════════════════════════╗
║  VOC Monitor                           ║
║                                        ║
║  TVOC:                                 ║
║  2450 ppb                              ║
║                                        ║
║  eCO2:                                 ║
║  2100 ppm                              ║
║                                        ║
║                           Unhealthy    ║  <- RED
╚════════════════════════════════════════╝
```

## Physical Button Layout (M5StickC Plus2)

```
┌─────────────────┐
│    [Screen]     │
│                 │
└─────────────────┘
     │   │
   [A] [B] [PWR]
```

### Button Functions (Advanced Mode Only)
- **Button A**: Change display mode (Current → Graph → Stats → Current)
- **Button B**: Reset statistics
- **Power Button**: (Hold) Power on/off, (Press) Wake from sleep

### Main Application
Buttons are not used in the basic application, only in the AdvancedVOC example.

## Screen Regions

```
┌────────────────────────────────────────┐  Y: 0
│ Title Area (20, 5)                     │
├────────────────────────────────────────┤  Y: 30
│                                        │
│ TVOC Label (10, 35)                    │
│ TVOC Value (10, 55)                    │
│                                        │
├────────────────────────────────────────┤  Y: 80
│                                        │
│ eCO2 Label (10, 85)                    │
│ eCO2 Value (10, 105)                   │
│                                        │
├────────────────────────────────────────┤  Y: 120
│                  Air Quality (150,120) │
└────────────────────────────────────────┘  Y: 135
X: 0                                   240
```

## Typography

### Font Sizes
- **Size 1**: 8x6 pixels per character
- **Size 2**: 16x12 pixels per character (used for main text)
- **Size 3**: 24x18 pixels per character (optional, not used)

### Text Positioning
All text uses `setCursor(x, y)` for precise placement:
- Title: (20, 5) - Centered-ish
- TVOC Label: (10, 35) - Left margin
- TVOC Value: (10, 55) - Left margin
- eCO2 Label: (10, 85) - Left margin  
- eCO2 Value: (10, 105) - Left margin
- Air Quality: (150, 120) - Right side

## Refresh Strategy

The display uses `fillRect()` to clear the entire screen before each update:
```cpp
M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), BLACK);
```

This ensures:
- No ghosting of previous values
- Clean transitions between readings
- Proper number alignment

## Power Consumption Impact

| Setting | Current Draw | Battery Life |
|---------|--------------|--------------|
| Brightness 255 | ~180mA | ~3-4 hours |
| Brightness 128 | ~150mA | ~6-8 hours |
| Brightness 64  | ~120mA | ~10-12 hours |
| Display off    | ~50mA  | ~24+ hours |

Default brightness: **128** (good balance)

## Customization Tips

Want to customize the display? Edit `displayReadings()` function:

1. **Change colors**: Modify `setTextColor()` calls
2. **Adjust positions**: Update `setCursor(x, y)` coordinates
3. **Larger text**: Change `setTextSize()` value
4. **Add graphics**: Use `drawLine()`, `fillCircle()`, etc.
5. **Brightness**: Adjust `setBrightness(0-255)`

## Accessibility Notes

- High contrast (white/colored text on black background)
- Large, readable fonts (size 2)
- Color coding reinforced with text labels
- Clear visual hierarchy

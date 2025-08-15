# Required Libraries

To compile this project, you need to install the following Arduino libraries:

## Core Libraries (install via Arduino Library Manager)

1. **Adafruit GFX Library**
   - Author: Adafruit
   - Version: >= 1.11.0
   - Description: Core graphics library for displays

2. **Adafruit ST7735 and ST7789 Library**
   - Author: Adafruit
   - Version: >= 1.10.0
   - Description: Library for ST7789 TFT displays

3. **SHT3x-Arduino-Library**
   - Author: Risele
   - Version: >= 1.0.0
   - Description: Library for SHT30/SHT31/SHT35 temperature and humidity sensors

4. **PID**
   - Author: Brett Beauregard
   - Version: >= 1.2.1
   - Description: PID controller library for temperature control

5. **Encoder**
   - Author: Paul Stoffregen
   - Version: >= 1.4.1
   - Description: Library for reading quadrature encoders

## Installation Instructions

### Arduino IDE
1. Open Arduino IDE
2. Go to Tools → Manage Libraries
3. Search for each library by name and install the latest version

### PlatformIO
Use the included `platformio.ini` file which automatically manages dependencies.

## Board Configuration

**Target Board:** Arduino Nano 33 IoT
- Select "Arduino Nano 33 IoT" from Tools → Board
- Select appropriate COM port from Tools → Port

## Memory Optimization Features

This sketch includes several memory optimization techniques:

1. **PROGMEM Usage**: Constant strings stored in flash memory
2. **Efficient Data Types**: Using appropriate variable sizes
3. **Minimal Global Variables**: Reduced RAM usage
4. **Optimized Display Updates**: Reduced frequency to save processing time
5. **Local Variables**: Used where possible to reduce permanent RAM usage

## Pin Configuration

| Component | Pin | Notes |
|-----------|-----|-------|
| TFT CS | 10 | SPI Chip Select |
| TFT Reset | 9 | Display Reset |
| TFT DC | 8 | Data/Command |
| TFT MOSI | 11 | SPI Data |
| TFT SCLK | 13 | SPI Clock |
| Encoder A | 2 | Interrupt capable pin |
| Encoder B | 3 | Interrupt capable pin |
| Encoder Button | 4 | Digital input with pullup |
| Heater Relay | 5 | Digital output |
| Fan PWM | 6 | PWM output |
| Buzzer | 7 | Digital output |
| SHT30 SDA | A4 | I2C Data (default) |
| SHT30 SCL | A5 | I2C Clock (default) |

## Troubleshooting

### Compilation Errors
- Ensure all required libraries are installed
- Check board selection is "Arduino Nano 33 IoT"
- Verify library versions are compatible

### Memory Issues
- The sketch is optimized for Arduino Nano 33 IoT
- If memory issues persist, reduce string constants or optimize further

### Display Issues
- Check SPI connections
- Verify display is ST7789 240x240
- Check power supply is adequate

### Sensor Issues
- Verify I2C connections (SDA/SCL)
- Check sensor power supply (3.3V)
- Ensure proper pull-up resistors on I2C lines
# FilamentDryerController

An Arduino-based filament dryer controller with temperature/humidity monitoring, PID temperature control, and a user-friendly TFT interface.

## Features

- **Temperature & Humidity Monitoring**: SHT30 sensor with I2C interface
- **TFT Display**: 240x240 ST7789 color display with real-time status
- **PID Temperature Control**: Precise heating element control
- **Variable Fan Speed**: PWM-controlled fan for air circulation
- **Intuitive Menu System**: Rotary encoder with push button navigation
- **Memory Optimized**: Designed for Arduino Nano 33 IoT constraints
- **Safety Features**: Automatic heater shutoff and status monitoring

## Hardware Requirements

### Main Components
- **Arduino Nano 33 IoT** - Main controller
- **ST7789 TFT Display** - 240x240 pixel color display
- **SHT30 Sensor** - I2C temperature and humidity sensor
- **Rotary Encoder** - With integrated push button
- **Relay Module** - For heater control (5V or 3.3V compatible)
- **Fan** - 12V PC fan or similar with PWM control
- **Heating Element** - Appropriate for filament drying

### Pin Connections

| Component | Arduino Pin | Notes |
|-----------|-------------|-------|
| **ST7789 Display** | | |
| VCC | 3.3V | Power |
| GND | GND | Ground |
| CS | Pin 10 | SPI Chip Select |
| RESET | Pin 9 | Display Reset |
| DC | Pin 8 | Data/Command |
| SDA/MOSI | Pin 11 | SPI Data |
| SCL/SCLK | Pin 13 | SPI Clock |
| **SHT30 Sensor** | | |
| VCC | 3.3V | Power |
| GND | GND | Ground |
| SDA | A4 | I2C Data |
| SCL | A5 | I2C Clock |
| **Rotary Encoder** | | |
| + | 3.3V | Power |
| GND | GND | Ground |
| DT | Pin 2 | Encoder A |
| CLK | Pin 3 | Encoder B |
| SW | Pin 4 | Push Button |
| **Outputs** | | |
| Heater Relay | Pin 5 | Digital Output |
| Fan PWM | Pin 6 | PWM Output |
| Buzzer (Optional) | Pin 7 | Digital Output |

## Software Setup

### Arduino IDE
1. Install Arduino IDE 1.8.13 or newer
2. Install Arduino SAMD Boards package
3. Select "Arduino Nano 33 IoT" board
4. Install required libraries (see LIBRARIES.md)

### PlatformIO (Recommended)
1. Install PlatformIO
2. Open project folder
3. Build and upload (dependencies managed automatically)

### Required Libraries
See [LIBRARIES.md](LIBRARIES.md) for complete installation instructions.

## Usage

### Menu Navigation
- **Rotate Encoder**: Adjust values in setting modes
- **Press Button**: Cycle through menu options

### Menu Options
1. **Main Display** - Shows current temperature, humidity, and status
2. **Temperature Setting** - Adjust target temperature (20-80°C)
3. **Fan Setting** - Adjust fan speed (0-100%)
4. **System Toggle** - Enable/disable the dryer system

### Operation
1. Connect all hardware according to pin diagram
2. Upload sketch to Arduino Nano 33 IoT
3. Power on the system
4. Use encoder to set desired temperature
5. Adjust fan speed as needed
6. Press button to enable system
7. Monitor progress on display

## Safety Features

- **Temperature Limits**: Software limits prevent overheating
- **Sensor Monitoring**: System shuts down if sensor fails
- **Manual Override**: Easy system disable via button
- **Status Display**: Clear indication of system state

## Memory Optimization

The code is optimized for the limited memory of Arduino Nano 33 IoT:

- PROGMEM usage for string constants
- Efficient data types and structures
- Minimal global variables
- Optimized display update frequency
- Local variable usage where possible

## Troubleshooting

### Common Issues
1. **Compilation Errors**: Ensure all libraries are installed
2. **Display Not Working**: Check SPI connections and power
3. **Sensor Errors**: Verify I2C connections and addressing
4. **Memory Issues**: Code is pre-optimized for Nano 33 IoT

### Debug Output
Enable serial monitor at 115200 baud for debug information.

## License

This project is open source. See license file for details.

## Contributing

Contributions welcome! Please read contributing guidelines before submitting PRs.

## Support

For issues and questions, please use the GitHub issues tracker.
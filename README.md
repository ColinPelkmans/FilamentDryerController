# Filament Dryer Controller 🌡️🔥

**Turn your old Ender 3 into a professional filament dryer!**

If, just like me and many others, you have an old Ender 3 you don't use anymore, here's another fun project you can make with its old parts! Instead of letting that printer collect dust, transform it into a precision filament conditioning station.

## 🎯 Project Overview

This Arduino-based controller converts your retired 3D printer into a smart filament dryer with:

- **Professional temperature control** using your old heated bed
- **Precise timing** with multiple material presets (PLA, PETG, ABS, Nylon, TPU)
- **Beautiful ST7789 display** showing real-time status and progress
- **Rotary encoder interface** for easy navigation
- **Dual temperature monitoring** (chamber + bed sensors)
- **Smart fan control** for optimal air circulation

## 🔧 Hardware Requirements

### From Your Old Ender 3:
- Heated bed + MOSFET driver
- Stepper motor (for filament rotation - optional)
- Power supply (24V recommended)
- Cooling fans
- Frame and enclosure parts

### Additional Components:
- Arduino Uno/Nano
- ST7789 240x320 TFT Display
- Rotary encoder with button
- DS18B20 temperature sensor
- KY-028 temperature sensor
- Various MOSFETs for control

## 🚀 Features

### Smart Presets
- **PLA**: 45°C for 4 hours
- **PETG**: 65°C for 6 hours  
- **ABS**: 80°C for 4 hours
- **Nylon**: 70°C for 8 hours
- **TPU**: 45°C for 4 hours

### Professional Interface
- Real-time temperature monitoring
- Progress bar with time remaining
- Pause/resume functionality
- Material selection menu
- Visual status indicators

### Safety Features
- Temperature overshoot protection
- Automatic shutdown on completion
- Real-time sensor monitoring
- Emergency stop capability

## 📱 User Interface

The controller features a beautiful blue-themed interface with:
- Main dashboard showing all critical information
- Intuitive menu navigation with rotary encoder
- Clear progress visualization
- Professional status icons

## 🛠️ Installation

1. **Hardware Setup**: Connect components according to pin definitions in `globals.h`
2. **Library Installation**: Install required Arduino libraries:
   - Adafruit GFX Library
   - Adafruit ST7735 and ST7789 Library
   - OneWire
   - DallasTemperature
   - Adafruit BusIO
3. **Upload Code**: Flash the `FilamentDryerController.ino` to your Arduino
4. **Configuration**: Adjust presets in `presets.cpp` if needed

## 🎨 Customization

- Modify drying presets in `presets.cpp`
- Adjust UI colors in `colors.h` 
- Add custom icons in `icons.cpp`
- Fine-tune temperature control in `dryingController.cpp`

## 📋 Pin Configuration

```cpp
#define TFT_CS        10    // Display chip select
#define TFT_RST       9     // Display reset
#define TFT_DC        A1    // Display data/command
#define ENCODER_A     A2    // Rotary encoder A
#define ENCODER_B     A3    // Rotary encoder B
#define ENCODER_BTN   A4    // Encoder button
#define MOSFET_BED_PWM 8    // Heated bed control
#define MOSFET_FAN_PWM 6    // Fan speed control
#define DS18B20_PIN   7     // Chamber temperature
#define KY028_AO      A0    // Bed temperature sensor
```

## 🌟 Why This Project?

- **Eco-friendly**: Give new life to old hardware
- **Cost-effective**: Professional filament dryer for fraction of commercial price
- **Educational**: Learn Arduino programming and hardware interfacing
- **Practical**: Solve real 3D printing problems (wet filament)
- **Customizable**: Tailor to your specific needs and materials

## 🔮 Future Enhancements

- [ ] PID temperature control for precision
- [ ] WiFi connectivity for remote monitoring
- [ ] Data logging and analytics
- [ ] Mobile app integration
- [ ] Multiple spool support
- [ ] Humidity monitoring

## 👨‍💻 Author

**Colin Pelkmans** - Turning old 3D printers into new solutions!

---

*Transform your retired Ender 3 into a precision tool that'll make your 3D printing better than ever. Because every maker deserves dry filament!* 🎯

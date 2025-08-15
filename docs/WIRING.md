# Wiring and Circuit Documentation

## Pin Mapping Table

The following pin assignments match the definitions in `globals.h`:

| Arduino Pin | Component | Function | Signal Type | Notes |
|-------------|-----------|----------|-------------|-------|
| **Digital Pins** |
| D2 | DRV8825 | STEP | Digital Output | Stepper motor step pulses |
| D4 | DRV8825 | ENABLE | Digital Output | Motor driver enable (LOW = enabled) |
| D5 | TFT Display | Backlight (BLK) | PWM Output | Display brightness control |
| D6 | Fan MOSFET | PWM | PWM Output | Fan speed control |
| D7 | DS18B20 | Data | Digital I/O | 1-Wire temperature sensor |
| D8 | Heated Bed MOSFET | PWM | PWM Output | Heater power control |
| D9 | TFT Display | Reset (RST) | Digital Output | Display reset line |
| D10 | TFT Display | Chip Select (CS) | Digital Output | SPI chip select |
| D11 | TFT Display | MOSI | SPI Output | SPI data (implicit) |
| D12 | DRV8825 | DIR | Digital Output | Stepper direction control |
| D13 | TFT Display | SCK | SPI Output | SPI clock (implicit) |
| **Analog Pins** |
| A0 | KY-028 | Analog Out | Analog Input | Heatbed temperature |
| A1 | TFT Display | Data/Command (DC) | Digital Output | Display control |
| A2 | Rotary Encoder | Phase A | Digital Input | Encoder position |
| A3 | Rotary Encoder | Phase B | Digital Input | Encoder position |
| A4 | Rotary Encoder | Button | Digital Input | User button press |
| A5 | (Reserved) | - | - | Available for expansion |

## Circuit Schematic Descriptions

### Power Distribution Circuit

```
Main Power Supply (12V/24V)
    │
    ├── Thermal Fuse (100°C) ─── Heated Bed MOSFET ─── Heated Bed
    │
    ├── Blade Fuse (5A) ─── LM2596 Buck Converter ─── 5V Rail
    │                           │
    │                           ├── Arduino Uno (VIN)
    │                           ├── TFT Display (VCC)
    │                           └── Logic Circuits
    │
    └── Blade Fuse (5A) ─── Fan MOSFET ─── DC Fan
```

### Arduino Main Controller Connections

#### Power Connections
- **VIN**: 5V from LM2596 buck converter
- **GND**: Common ground for all circuits
- **5V**: Powers sensors and logic circuits
- **3.3V**: Available for 3.3V components (not used in this design)

#### SPI Display Connection (ST7789)
```
Arduino    ST7789 Display
D10     →  CS (Chip Select)
D11     →  SDA/MOSI (Data)
D13     →  SCL/SCK (Clock)
A1      →  DC (Data/Command)
D9      →  RST (Reset)
D5      →  BLK (Backlight, PWM)
5V      →  VCC
GND     →  GND
```

#### Temperature Sensors
```
DS18B20 (1-Wire):
Arduino Pin D7 → DS18B20 Data Pin
5V → DS18B20 VCC (Red wire)
GND → DS18B20 GND (Black wire)
4.7kΩ pullup resistor between Data and VCC

KY-028 Thermistor Module:
Arduino Pin A0 → KY-028 Analog Output
5V → KY-028 VCC
GND → KY-028 GND
```

#### Rotary Encoder Connections
```
Arduino    EC11 Encoder
A2      →  Phase A (CLK)
A3      →  Phase B (DT)
A4      →  Button (SW)
5V      →  VCC
GND     →  GND

Note: Internal pullup resistors enabled in software
```

### MOSFET Driver Configurations

#### Heated Bed MOSFET Circuit
```
Arduino D8 (PWM) → Gate
Source → Ground
Drain → Heated Bed Negative
Heated Bed Positive → +24V (via thermal fuse)

Gate Protection:
- 10kΩ pulldown resistor (Gate to Ground)
- Optional 330Ω gate resistor for noise immunity
```

#### Fan MOSFET Circuit
```
Arduino D6 (PWM) → Gate  
Source → Ground
Drain → Fan Negative
Fan Positive → +12V/24V (via fuse)

Gate Protection:
- 10kΩ pulldown resistor (Gate to Ground)
- Optional 330Ω gate resistor
```

#### MOSFET Selection Notes
- **IRFZ44N**: Logic-level N-channel MOSFET
- **Vgs(th)**: 2-4V (suitable for 5V Arduino)
- **Rds(on)**: Low resistance when fully on
- **Heat Sinking**: Required for continuous operation >5A

### Stepper Motor Driver (DRV8825)

#### Power Connections
```
VMOT: 12V or 24V motor supply
GND: Common ground
VDD: 5V logic supply (from Arduino)
```

#### Control Connections
```
Arduino    DRV8825
D2      →  STEP
D12     →  DIR
D4      →  ENABLE
GND     →  GND
```

#### Motor Connections (NEMA 17)
```
DRV8825    Stepper Motor
1A      →  Coil A+
1B      →  Coil A-
2A      →  Coil B+
2B      →  Coil B-
```

#### Microstepping Configuration
Default configuration (all MS pins unconnected) = Full step mode
For microstepping, connect MS1, MS2, MS3 pins as needed:
- MS1=L, MS2=L, MS3=L: Full step
- MS1=H, MS2=L, MS3=L: Half step
- MS1=L, MS2=H, MS3=L: 1/4 step
- MS1=H, MS2=H, MS3=L: 1/8 step
- MS1=H, MS2=H, MS3=H: 1/32 step

### Safety Circuit Implementation

#### Thermal Fuse Wiring (CRITICAL)
```
Main Power (+) → Thermal Fuse → Heated Bed MOSFET → Heated Bed (+)
```
**WARNING**: The thermal fuse MUST be in series with the heated bed power. Never bypass this safety device.

#### Overcurrent Protection
```
Power Supply (+) → Blade Fuse → Circuit Load
```
Use 5A fuses for both the Arduino power rail and fan circuit.

## Wiring Best Practices

### Wire Gauge Recommendations
- **Heated Bed Power**: 16 AWG minimum (12 AWG for >10A)
- **Motor Power**: 18 AWG
- **Arduino Power**: 20 AWG  
- **Signal Wires**: 22-24 AWG
- **Ground Connections**: Same gauge as power wires

### Connection Methods
1. **Permanent Installation**: Solder all connections
2. **Prototyping**: Use breadboard for initial testing only
3. **Maintenance Access**: Use screw terminals for user-serviceable connections
4. **Wire Management**: Use heat shrink tubing and cable ties

### Grounding Strategy
- **Single Point Ground**: Connect all ground wires to Arduino GND
- **Power Ground**: Use thick wire for high-current grounds
- **Shield Grounding**: Connect metal enclosures to safety ground
- **Noise Reduction**: Keep digital and analog grounds separate when possible

## Circuit Protection and Filtering

### Decoupling Capacitors
- **Power Rails**: 100µF electrolytic + 0.1µF ceramic near ICs
- **MOSFET Gates**: 0.1µF ceramic from gate to source
- **Motor Supply**: Large capacitor (1000µF+) for current spikes

### Flyback Diode Protection
- **MOSFET Circuits**: 1N4007 diode across inductive loads
- **Motor Circuits**: Built into DRV8825 driver
- **Relay Circuits**: 1N4148 fast diode (if using optional relay)

### EMI Suppression
- **Twisted Pair Wiring**: For encoder and sensor signals
- **Shielded Cable**: For long signal runs
- **Ferrite Cores**: On power and signal cables if needed

## Troubleshooting Guide

### Display Issues
- **Blank Screen**: Check power, SPI connections, reset line
- **Garbled Display**: Verify SPI timing, check wiring
- **No Backlight**: Check PWM signal on D5, backlight connection

### Temperature Reading Problems
- **DS18B20 No Reading**: Check 1-Wire pullup resistor (4.7kΩ)
- **KY-028 Incorrect**: Verify analog reference voltage
- **Sensor Drift**: Check for loose connections, sensor placement

### Motor Control Issues
- **No Movement**: Check enable pin (should be LOW), power supply
- **Wrong Direction**: Swap DIR signal or motor wiring
- **Stuttering**: Check step timing, current adjustment on DRV8825

### Power Control Problems
- **MOSFET Not Switching**: Check gate voltage, pulldown resistor
- **Overheating**: Verify heat sinking, current rating
- **Slow Response**: Check PWM frequency, gate drive strength

### Safety System Verification
1. **Thermal Fuse Test**: Heat to 100°C, verify circuit opens
2. **Overcurrent Test**: Create controlled overload, verify fuse opens
3. **Temperature Monitoring**: Compare sensor readings with calibrated meter
4. **Emergency Stop**: Verify immediate shutdown on button press

## Testing and Calibration Procedures

### Initial Power-Up Checklist
1. Verify all connections with multimeter
2. Check power supply voltages
3. Test safety systems before connecting heated bed
4. Verify sensor readings at room temperature
5. Test display and user interface
6. Calibrate temperature sensors if needed

### Operational Testing
1. **Temperature Control**: Verify heating and cooling cycles
2. **Motor Operation**: Test spool rotation in both directions  
3. **Safety Response**: Test thermal and overcurrent protection
4. **User Interface**: Test all menu functions and controls
5. **Long-term Operation**: Monitor for overheating or drift

## Advanced Modifications

### Optional Enhancements
- **PID Temperature Control**: Implement in software for precision
- **Multiple Temperature Zones**: Add more sensors and heaters
- **Humidity Monitoring**: Add DHT22 or SHT30 sensor
- **WiFi Connectivity**: Add ESP8266 or ESP32 module
- **Data Logging**: Add SD card module for temperature history

### Expansion Connections
- **A5 Pin**: Available for additional analog sensor
- **Unused Digital Pins**: Available for expansion
- **I2C Bus**: Use A4/A5 for I2C devices (conflicts with current encoder)
- **Additional Serial**: Software serial for WiFi module
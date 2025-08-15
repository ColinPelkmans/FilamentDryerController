# Hardware Documentation

## Component Specifications and Descriptions

### Main Controller
- **Arduino Uno**: Main microcontroller running the filament dryer system
  - Operating Voltage: 5V
  - Input Voltage: 7-12V (via VIN pin or DC jack)
  - Digital I/O Pins: 14 (6 provide PWM output)
  - Analog Input Pins: 6
  - Flash Memory: 32 KB

### Power Supply
- **Velleman LABPS3005D Bench Power Supply**
  - Output: 0-30V, 0-5A adjustable
  - Recommended setting: 12V or 24V for heated bed compatibility
  - Provides stable power for the entire system
  - **Safety**: Includes overcurrent protection and voltage regulation

### Display and User Interface
- **TFT Display (ST7789 SPI)**: 240x320 pixel color display
  - Interface: SPI (Serial Peripheral Interface)
  - Operating Voltage: 3.3V-5V
  - Viewing Area: Approximately 2.4 inches
  - Backlight: LED backlight with PWM control

- **EC11 Rotary Encoder with Button**: User input control
  - Mechanical rotary encoder with 20 detents per revolution
  - Integrated push button for selection
  - Operating Voltage: 5V
  - Output: Quadrature signals (A/B phases)

### Temperature Sensing
- **DS18B20 Waterproof Temperature Sensor**: Chamber temperature monitoring
  - Temperature Range: -55°C to +125°C
  - Accuracy: ±0.5°C (from -10°C to +85°C)
  - Interface: 1-Wire digital protocol
  - Waterproof probe suitable for chamber mounting
  - **Safety**: Provides accurate chamber temperature for overheat protection

- **KY-028 Thermistor Module**: Heatbed temperature sensing
  - NTC thermistor with onboard signal conditioning
  - Operating Temperature: -40°C to +125°C
  - Output: Analog voltage proportional to temperature
  - Used for direct heatbed temperature monitoring

### Power Control Components
- **IRFZ44N MOSFET (2x)**: Logic-level power switching
  - Type: N-Channel Enhancement Mode
  - Drain-Source Voltage: 55V
  - Continuous Drain Current: 49A
  - Gate Threshold Voltage: 2-4V (logic level compatible)
  - Used for fan and auxiliary heating control

- **Heated Bed MOSFET Module**: High-current switching for heated bed
  - Designed for 3D printer heated bed control
  - Typically includes flyback diode protection
  - Heat sinking provided for continuous operation
  - Input: 5V logic signal from Arduino
  - Output: Switches 12V/24V heated bed power

### Motor Control
- **DRV8825 Stepper Driver**: Controls filament spool rotation
  - Microstepping: Up to 1/32 step resolution
  - Operating Voltage: 8.2V to 45V
  - Current Control: Adjustable via potentiometer
  - Protection: Overcurrent, overtemperature, undervoltage

- **NEMA 17 Stepper Motor**: Rotates filament spool for even drying
  - Step Angle: 1.8° (200 steps per revolution)
  - Holding Torque: Typically 4.4-5.5 kg⋅cm
  - Operating Voltage: 12V or 24V
  - Used to slowly rotate spool during drying process

### Air Circulation
- **PWM DC Fan**: Provides air circulation within drying chamber
  - Operating Voltage: 12V or 24V
  - Speed Control: PWM (Pulse Width Modulation)
  - Recommended: High static pressure for enclosed chamber
  - **Safety**: Ensures even heat distribution and prevents hot spots

### Power Conversion and Distribution
- **LM2596 Buck Converter**: Steps down voltage for Arduino
  - Input Voltage: 4-40V
  - Output Voltage: 1.25-37V (adjustable)
  - Configuration: 12V/24V input → 5V output for Arduino
  - Efficiency: >85% typical
  - Current Capability: Up to 3A

### Safety and Protection Components
- **Auto Blade Fuses (5A, 2x)**: Overcurrent protection
  - Type: Automotive blade fuse
  - Rating: 5A, 32VDC
  - Fast-acting for equipment protection
  - **Critical Safety Component**: Protects against short circuits

- **Blade Fuse Holders (16AWG, Waterproof, 2x)**: Houses protection fuses
  - Wire Gauge: 16AWG for adequate current capacity
  - Waterproof design for safety in humid environments
  - Allows easy fuse replacement

- **Thermal Fuse (100°C TF/RY, 10A 250V)**: Ultimate overheat protection
  - Activation Temperature: 100°C
  - One-time use safety device
  - **CRITICAL SAFETY**: Permanently opens circuit if overheated
  - Must be wired in series with heated bed power

### Heat Source
- **12V or 24V Heated Bed**: Primary heat source for drying chamber
  - Typical Size: 220x220mm or 235x235mm
  - Power: 120-240W depending on voltage and size
  - Surface: Aluminum or glass with heating element
  - **Safety**: Must be used with thermal fuse protection

## Power Requirements and Calculations

### Total Power Consumption
- Heated Bed: 120-240W (depending on size and voltage)
- Arduino Uno: ~500mA @ 5V = 2.5W
- TFT Display: ~100mA @ 5V = 0.5W
- Stepper Motor: ~1A @ 12V = 12W (when active)
- DC Fan: ~200mA @ 12V = 2.4W
- **Total**: Approximately 140-260W

### Recommended Power Supply Sizing
- For 12V System: Minimum 15A capacity (180W + margin)
- For 24V System: Minimum 12A capacity (288W + margin)
- The Velleman LABPS3005D at 5A capacity limits total power to 150W

**Note**: For higher power heated beds, consider a dedicated 24V power supply with higher current capacity.

## Assembly Difficulty Level

**Skill Level**: Intermediate to Advanced

### Required Skills
- Basic electronics knowledge
- Soldering experience (for reliable connections)
- Understanding of electrical safety
- Arduino programming basics
- Mechanical assembly skills

### Estimated Assembly Time
- Electronics Assembly: 4-6 hours
- Enclosure Modification: 2-4 hours
- Software Configuration: 1-2 hours
- Testing and Calibration: 2-3 hours
- **Total**: 9-15 hours

### Required Tools
- Soldering iron and solder
- Wire strippers and crimpers
- Digital multimeter
- Screwdrivers and basic hand tools
- Heat gun or hair dryer (for heat shrink tubing)
- Safety glasses and work gloves

## Safety Considerations

⚠️ **IMPORTANT SAFETY WARNINGS** ⚠️

1. **Electrical Safety**: Always disconnect power when making connections
2. **Heat Protection**: Thermal fuse is mandatory - never bypass
3. **Overcurrent Protection**: Fuses must be properly rated and installed
4. **Insulation**: Ensure all high-voltage connections are properly insulated
5. **Ventilation**: Provide adequate ventilation for heat dissipation
6. **Testing**: Always test safety systems before first use

## Sourcing Recommendations

### Preferred Suppliers
- **Arduino Components**: Official Arduino distributors
- **Electronic Components**: DigiKey, Mouser, SparkFun
- **3D Printer Parts**: E3D, Prusa, local 3D printer suppliers
- **Power Supplies**: Meanwell, Velleman authorized dealers

### Budget Estimates (USD)
- Arduino Uno: $20-30
- Display and Encoder: $15-25
- Temperature Sensors: $10-15
- Power Components: $20-30
- Safety Components: $10-15
- Miscellaneous (wires, connectors): $15-20
- **Total Estimated Cost**: $90-135 (excluding heated bed and power supply)

## Quality and Reliability Notes

- Use automotive-grade fuses for reliability
- Select MOSFETs with adequate heat sinking
- Choose temperature sensors with appropriate probe lengths
- Ensure all connections are soldered (avoid breadboard for final assembly)
- Use heat shrink tubing for all splice connections
- Consider using terminal blocks for easy maintenance
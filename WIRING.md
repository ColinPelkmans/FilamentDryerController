# Wiring Diagram

## Arduino Nano 33 IoT Pinout

```
                    Arduino Nano 33 IoT
                    +---USB---+
                D13 |●        ●| VIN
                D12 |●        ●| GND
                D11 |●        ●| RST
                D10 |●        ●| 5V
                 D9 |●        ●| A7
                 D8 |●        ●| A6
                 D7 |●        ●| A5 (SCL)
                 D6 |●        ●| A4 (SDA)
                 D5 |●        ●| A3
                 D4 |●        ●| A2
                 D3 |●        ●| A1
                 D2 |●        ●| A0
                GND |●        ●| AREF
                RST |●        ●| 3V3
                RX0 |●        ●| D13
                TX1 |●________●| D12
                    +---------+
```

## Component Connections

### ST7789 TFT Display (240x240)
```
ST7789 Pin  →  Arduino Pin   →  Description
VCC         →  3.3V         →  Power (3.3V only!)
GND         →  GND          →  Ground
CS          →  D10          →  SPI Chip Select
RESET       →  D9           →  Display Reset
DC/RS       →  D8           →  Data/Command Select
SDA/MOSI    →  D11          →  SPI Data (MOSI)
SCL/SCLK    →  D13          →  SPI Clock
LED         →  3.3V         →  Backlight (optional resistor)
```

### SHT30 Temperature/Humidity Sensor
```
SHT30 Pin   →  Arduino Pin   →  Description
VCC         →  3.3V         →  Power
GND         →  GND          →  Ground
SDA         →  A4           →  I2C Data
SCL         →  A5           →  I2C Clock
ADDR        →  GND          →  I2C Address (0x44)
```

### Rotary Encoder with Button
```
Encoder Pin →  Arduino Pin   →  Description
+/VCC       →  3.3V         →  Power
GND         →  GND          →  Ground
DT          →  D2           →  Encoder A (interrupt pin)
CLK         →  D3           →  Encoder B (interrupt pin)
SW          →  D4           →  Push Button (active low)
```

### Output Controls
```
Component   →  Arduino Pin   →  Description
Heater Relay→  D5           →  Digital output (3.3V logic)
Fan PWM     →  D6           →  PWM output for fan speed
Buzzer      →  D7           →  Optional buzzer output
```

## Power Supply Recommendations

### Arduino Nano 33 IoT
- **Input Voltage:** 5V via USB or VIN pin
- **Logic Level:** 3.3V (DO NOT use 5V logic!)
- **Current Draw:** ~50-100mA

### Display Power
- **ST7789:** 3.3V, ~30-50mA (with backlight)
- **IMPORTANT:** ST7789 is 3.3V only - DO NOT connect to 5V!

### Total System Power
- **Logic Circuits:** ~100-150mA at 3.3V
- **Relay:** 20-50mA at 3.3V (depending on type)
- **Fan:** External 12V supply recommended

## Relay Module Connection

### For 3.3V Logic Level Relay
```
Relay Module →  Connection     →  Description
VCC          →  3.3V          →  Module power
GND          →  GND           →  Ground
IN           →  D5            →  Control signal
COM          →  AC Hot        →  Common (mains hot)
NO           →  Heater Hot    →  Normally Open (to heater)
```

### For Heater Element
```
AC Input → [Relay COM] [Relay NO] → Heater Element → AC Neutral
```
**⚠️ WARNING:** High voltage AC connections should be done by qualified personnel only!

## Fan Connection

### 12V PC Fan with PWM
```
Fan Wire    →  Connection     →  Description
Red (+12V)  →  12V Supply    →  Fan power
Black (GND) →  12V GND       →  Fan ground
Yellow (PWM)→  D6 + Level    →  PWM control (may need level shifter)
            →  Shifter       →  3.3V→5V conversion
```

### PWM Level Shifting (if needed)
Some 12V fans expect 5V PWM signals. Use a simple transistor circuit:
```
Arduino D6 → 1kΩ resistor → NPN transistor base
Transistor collector → Fan PWM wire
Transistor emitter → GND
```

## Safety Notes

1. **⚠️ HIGH VOLTAGE WARNING:** AC mains connections are dangerous
2. **Power Isolation:** Keep low voltage and AC circuits separated
3. **Logic Levels:** Arduino Nano 33 IoT is 3.3V - not 5V tolerant
4. **Current Limits:** Don't exceed pin current ratings
5. **Fusing:** Use appropriate fuses for AC circuits

## Testing Connections

1. **Power Test:** Verify 3.3V on all VCC pins
2. **I2C Test:** Use I2C scanner to detect SHT30 at 0x44
3. **SPI Test:** Check display initialization
4. **Encoder Test:** Verify encoder counting and button
5. **Output Test:** Test relay and fan control (low power first)

## Troubleshooting

| Problem | Check |
|---------|-------|
| Display not working | Power (3.3V!), SPI connections |
| Sensor not found | I2C wiring, pull-up resistors |
| Encoder erratic | Debouncing, power supply noise |
| Relay not switching | Logic level, relay module type |
| Fan not responding | PWM level, power supply |
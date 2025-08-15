# Safety Documentation

⚠️ **CRITICAL SAFETY INFORMATION** ⚠️

**READ THIS ENTIRE DOCUMENT BEFORE BUILDING OR OPERATING THE FILAMENT DRYER**

This device operates at temperatures up to 80°C (176°F) and uses significant electrical power. Improper construction or operation can result in fire, electrical shock, or injury. Follow all safety procedures outlined in this document.

## Primary Safety Systems

### 1. Thermal Fuse Protection (MANDATORY)

The thermal fuse is the primary overheat protection and **MUST NEVER BE BYPASSED**.

#### Specifications
- **Type**: TF/RY Thermal Fuse
- **Rating**: 100°C activation, 10A 250V
- **Response**: One-time use, permanently opens at 100°C
- **Location**: In series with heated bed power supply

#### Installation Requirements
```
Power Supply (+) → Thermal Fuse → Heated Bed MOSFET → Heated Bed
```

#### Critical Installation Notes
- Mount thermal fuse in direct thermal contact with heated bed
- Use thermal paste or thermally conductive adhesive
- Secure with metal clamp or heat-resistant tape
- **Never substitute with resetable devices**
- **Never bypass or remove during operation**

#### Testing Procedure
1. Heat thermal fuse to 100°C using controlled heat source
2. Verify circuit opens permanently
3. Replace fuse after each test
4. **Test before first operation and after any modifications**

### 2. Overcurrent Protection

#### Blade Fuse Configuration
- **Arduino/Logic Circuit**: 5A blade fuse
- **Fan Circuit**: 5A blade fuse  
- **Main Power**: Additional protection at power supply

#### Fuse Installation
```
Power Supply → Main Fuse → Distribution:
    ├── 5A Fuse → LM2596 → Arduino & Logic
    └── 5A Fuse → Fan MOSFET → Fan
```

#### Fuse Selection Criteria
- **Fast-acting type** for equipment protection
- **Automotive blade fuses** for reliability
- **Waterproof holders** for environmental protection
- **Proper amperage rating** - never oversize

### 3. Temperature Monitoring Safety

#### Dual Temperature Sensing
- **DS18B20**: Chamber air temperature monitoring
- **KY-028**: Heated bed surface temperature monitoring
- **Software Limits**: Programmable maximum temperatures

#### Software Safety Limits
```cpp
// Safety temperature limits (implemented in code)
#define MAX_CHAMBER_TEMP 90   // °C - Emergency shutdown
#define MAX_BED_TEMP 100      // °C - Emergency shutdown  
#define TEMP_SENSOR_TIMEOUT 5000  // ms - Sensor fault detection
```

#### Sensor Failure Response
- **Sensor Disconnection**: Immediate heater shutdown
- **Reading Out of Range**: Emergency stop sequence
- **Sensor Timeout**: Automatic safety shutdown
- **Invalid Data**: Default to safe state (heaters off)

## Electrical Safety Requirements

### 1. Proper Grounding Procedures

#### Equipment Grounding
- **Metal Enclosure**: Connect to safety ground
- **Power Supply**: Use 3-wire grounded power cord
- **Heated Bed**: Ground metal components to enclosure
- **High Current Paths**: Use proper gauge ground wires

#### Ground Fault Protection
- **GFCI Protection**: Recommended for workshop installation
- **Insulation Testing**: Verify no shorts to ground
- **Regular Inspection**: Check ground connections quarterly

### 2. Insulation and Wire Management

#### High Voltage Wire Requirements
- **Wire Rating**: Minimum 600V insulation for heated bed wiring
- **Temperature Rating**: Use wires rated >105°C near heated components
- **Strain Relief**: Proper strain relief at all connections
- **Wire Routing**: Keep high and low voltage wires separated

#### Connection Standards
- **Soldered Joints**: All permanent connections must be soldered
- **Heat Shrink Tubing**: Cover all splices with proper tubing
- **Terminal Blocks**: Use for user-serviceable connections
- **No Exposed Conductors**: All live parts must be covered

### 3. Component Derating

#### Power Component Safety Margins
- **MOSFETs**: Operate at <70% of maximum current rating
- **Fuses**: Size for 125% of normal operating current
- **Heat Sinks**: Size for continuous operation + 25% margin
- **Wire Capacity**: Use wire rated for >125% of circuit current

## Fire Prevention Measures

### 1. Heat Management

#### Thermal Design Requirements
- **Adequate Ventilation**: Minimum 2-inch clearance around hot components
- **Heat Sink Sizing**: Calculate for continuous operation
- **Thermal Monitoring**: Multiple temperature sensors required
- **Emergency Cooling**: Fan must operate during emergency shutdown

#### Hot Surface Protection
- **Insulation**: Heat-resistant insulation around heated bed
- **Guarding**: Physical barriers around hot surfaces
- **Warning Labels**: Clear marking of hot surfaces
- **Cool-down Procedures**: Forced cooling after operation

### 2. Component Selection

#### Fire-Resistant Materials
- **Enclosure**: Metal or UL94 V-0 rated plastic only
- **Wire Insulation**: Use only flame-retardant types
- **Thermal Insulation**: Use only rated insulation materials
- **Mounting Hardware**: Non-combustible materials only

### 3. Environmental Considerations

#### Operating Environment
- **Ambient Temperature**: 15-30°C recommended
- **Humidity**: <60% relative humidity
- **Ventilation**: Well-ventilated area required
- **Clearances**: Minimum 12 inches from combustible materials

## Emergency Procedures

### 1. Emergency Shutdown Sequence

#### Automatic Emergency Conditions
- Chamber temperature >90°C
- Bed temperature >100°C
- Sensor failure or disconnection
- Power supply fault
- User emergency stop activation

#### Emergency Response Actions
1. **Immediate**: Cut power to all heaters
2. **Secondary**: Activate cooling fan at maximum speed
3. **Tertiary**: Display emergency message
4. **Final**: Disable system until manual reset

### 2. Manual Emergency Procedures

#### Emergency Stop Button
- **Location**: Easily accessible red emergency stop button
- **Action**: Immediately cuts all power to heating elements
- **Reset**: Requires manual reset and system restart
- **Testing**: Test emergency stop weekly

#### Fire Emergency Response
1. **Disconnect Power**: Turn off main power immediately
2. **Evacuate**: Clear area of personnel
3. **Fire Suppression**: Use Class C fire extinguisher only
4. **Ventilation**: Provide adequate ventilation for smoke
5. **Investigation**: Do not restart until cause is determined

### 3. Fault Recovery Procedures

#### After Emergency Shutdown
1. **Cool Down**: Allow complete cool-down (>30 minutes)
2. **Inspection**: Visually inspect all components
3. **Testing**: Test all safety systems before restart
4. **Documentation**: Log incident and corrective actions
5. **Clearance**: Obtain clearance before restart

## Installation Safety Checklist

### Pre-Installation Requirements
- [ ] Read and understand all documentation
- [ ] Verify component specifications against BOM
- [ ] Prepare proper tools and safety equipment
- [ ] Ensure adequate workspace ventilation
- [ ] Have fire extinguisher readily available

### Electrical Installation Checklist
- [ ] All connections soldered and properly insulated
- [ ] Thermal fuse installed and tested
- [ ] Overcurrent protection installed and tested
- [ ] Ground connections verified with ohmmeter
- [ ] Insulation resistance tested (>1MΩ)
- [ ] No exposed high-voltage conductors
- [ ] Strain relief installed on all power connections
- [ ] Wire routing provides separation of high/low voltage

### Mechanical Installation Checklist
- [ ] Enclosure provides adequate protection
- [ ] Heat sinks properly mounted with thermal interface
- [ ] Thermal fuse in direct contact with heated bed
- [ ] Adequate clearances maintained
- [ ] All fasteners properly torqued
- [ ] No sharp edges exposed
- [ ] Warning labels applied

### Software Configuration Checklist
- [ ] Temperature limits properly configured
- [ ] Sensor calibration verified
- [ ] Emergency stop function tested
- [ ] Safety timeout values confirmed
- [ ] Fault detection algorithms enabled
- [ ] User interface safety features active

## Operational Safety Procedures

### Pre-Operation Checklist
- [ ] Visual inspection of all components
- [ ] Verify all connections secure
- [ ] Check for damaged wires or components
- [ ] Test emergency stop function
- [ ] Verify proper sensor readings
- [ ] Confirm adequate ventilation

### During Operation
- [ ] Never leave system unattended for >30 minutes
- [ ] Monitor temperature readings regularly
- [ ] Watch for unusual odors or sounds
- [ ] Keep fire extinguisher accessible
- [ ] Maintain log of operating parameters
- [ ] Respond immediately to any alarms

### Post-Operation Procedures
- [ ] Allow complete cool-down before handling
- [ ] Disconnect power if not used for >24 hours
- [ ] Clean and inspect components monthly
- [ ] Document any anomalies observed
- [ ] Schedule regular maintenance

## Maintenance and Testing

### Weekly Safety Checks
- [ ] Test emergency stop button
- [ ] Verify sensor readings at room temperature
- [ ] Check for loose connections
- [ ] Inspect wire insulation for damage
- [ ] Clean dust from heat sinks and fans

### Monthly Maintenance
- [ ] Thermal fuse visual inspection
- [ ] Calibrate temperature sensors
- [ ] Check fuse continuity
- [ ] Inspect heated bed for damage
- [ ] Test MOSFET heat sink temperatures

### Annual Safety Testing
- [ ] Complete thermal fuse testing and replacement
- [ ] Insulation resistance testing
- [ ] Ground continuity verification
- [ ] Load testing of all circuits
- [ ] Documentation review and update

## Training Requirements

### Operator Qualifications
- Basic understanding of electrical safety
- Familiarity with emergency procedures
- Ability to recognize normal vs. abnormal operation
- Training on proper maintenance procedures

### Required Training Topics
1. **Electrical Safety**: Basic electrical safety principles
2. **Fire Safety**: Fire prevention and emergency response
3. **Equipment Operation**: Proper operating procedures
4. **Maintenance**: Routine maintenance and inspection
5. **Emergency Response**: Emergency shutdown and recovery

## Documentation and Record Keeping

### Required Records
- Installation inspection checklist
- Safety system test results
- Maintenance logs and schedules
- Incident reports and corrective actions
- Training records for all operators

### Inspection Documentation
- Date and time of inspection
- Items inspected and test results
- Any deficiencies noted
- Corrective actions taken
- Inspector identification

## Regulatory Compliance

### Electrical Codes
- Installation must comply with local electrical codes
- Use only UL/CSA listed components where required
- Obtain electrical inspection if required by local code
- Maintain compliance documentation

### Safety Standards
- Follow NFPA guidelines for electrical installation
- Comply with local fire codes
- Consider UL 991 (Environmental Processing Equipment) guidelines
- Maintain insurance and liability considerations

---

**REMEMBER: Safety is not optional. When in doubt, consult a qualified professional. No filament is worth risking injury or property damage.**
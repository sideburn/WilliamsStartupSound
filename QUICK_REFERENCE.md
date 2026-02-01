# Quick Reference Card

## Essential Connections (4 wires only!)

```
ATtiny85 Pin 8 (VCC) ──→ Williams +5V
ATtiny85 Pin 4 (GND) ──→ Williams GND
ATtiny85 Pin 6 (PB1) ──→ Williams Pin 2 (Binary 1)
ATtiny85 Pin 7 (PB2) ──→ Williams Pin 4 (Binary 4)
```

## Current Configuration
- **Triggers:** Sound #5 (binary 00101 = 1+4)
- **Boot delay:** 1000ms (1 second)
- **Trigger duration:** 200ms
- **Power in sleep:** <10µA (microamps)

## Changing the Intro Sound

1. Calculate binary value of desired sound (1-31)
2. Determine which Williams pins to connect
3. Update pin assignments in code
4. Reflash ATtiny85

### Sound Selection Formula
```
Sound # = (Pin2×1) + (Pin3×2) + (Pin4×4) + (Pin5×8) + (Pin7×16)
```

## Common Sound Examples

| Sound # | Binary  | Pins Used | ATtiny Config |
|---------|---------|-----------|---------------|
| 1       | 00001   | 2         | PB1 → Pin 2   |
| 3       | 00011   | 2,3       | PB1 → 2, PB2 → 3 |
| 5       | 00101   | 2,4       | PB1 → 2, PB2 → 4 (CURRENT) |
| 7       | 00111   | 2,3,4     | PB1 → 2, PB2 → 3, PB3 → 4 |
| 15      | 01111   | 2,3,4,5   | All 4 low pins |
| 16      | 10000   | 7         | PB1 → Pin 7   |
| 31      | 11111   | All       | All 5 pins    |

## Arduino IDE Settings
- **Board:** ATtiny25/45/85
- **Processor:** ATtiny85  
- **Clock:** Internal 8 MHz
- **Programmer:** USBasp (or Arduino as ISP)

## Troubleshooting Quick Checks

**No intro sound?**
- ✓ Check all 4 wire connections
- ✓ Increase bootDelay to 2000ms
- ✓ Test Williams board with manual buttons first

**Wrong sound plays?**
- ✓ Double-check Williams connector pin numbers
- ✓ Verify binary calculation
- ✓ Check for crossed wires

**Manual buttons don't work?**
- ✓ Ensure code sets pins to INPUT after trigger
- ✓ Test with ATtiny disconnected
- ✓ Check for shorts

## Power Consumption
- **Active:** ~4-8mA for 1.2 seconds
- **Sleep:** <10µA (basically zero)
- **Impact:** Negligible on battery life

## Files in This Repository
- `WilliamsStartupSound.ino` - Main Arduino sketch
- `README.md` - Full documentation
- `CIRCUIT.md` - Circuit diagrams and schematics
- `QUICK_REFERENCE.md` - This file
- `CHANGELOG.md` - Version history
- `LICENSE` - MIT License

---
**Quick tip:** Print this reference card and keep it in your toolbox!

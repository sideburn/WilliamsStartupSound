# Quick Reference Card

## Essential Connections (7 wires)

```
ATtiny85 Pin 8 (VCC) ──→ Williams +5V
ATtiny85 Pin 4 (GND) ──→ Williams GND
ATtiny85 Pin 2 (PB3) ──→ Williams Pin 2 (Binary 1)
ATtiny85 Pin 3 (PB4) ──→ Williams Pin 3 (Binary 2)
ATtiny85 Pin 5 (PB0) ──→ Williams Pin 4 (Binary 4)
ATtiny85 Pin 6 (PB1) ──→ Williams Pin 5 (Binary 8)
ATtiny85 Pin 7 (PB2) ──→ Williams Pin 7 (Binary 16)
```

## Current Configuration
- **Triggers:** Sound #5 (default, easily changeable)
- **Boot delay:** 1000ms (1 second)
- **Trigger duration:** 200ms
- **Power in sleep:** <10µA (microamps)
- **Pin connections:** All 5 Williams sound pins connected (supports any sound 1-31)

## Changing the Intro Sound

1. Open `WilliamsStartupSound.ino`
2. Find the line: `const int introSound = 5;`
3. Change the number to your desired sound (1-31)
4. Reflash ATtiny85

**That's it!** The code automatically calculates which pins to activate.

## Common Sound Examples

Just change `const int introSound = X;` to any of these:

| Sound # | Example Use |
|---------|-------------|
| 1       | Single beep |
| 5       | Default (CURRENT) |
| 7       | Triple tone |
| 15      | Complex sound |
| 16      | Deep bass |
| 31      | All pins active |

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

# Circuit Diagram

## Complete System Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                        FX Box System                             │
│                                                                   │
│  ┌──────────────┐                                                │
│  │ 11.1V LiPo   │                                                │
│  │   Battery    │                                                │
│  │   (3S)       │                                                │
│  └──────┬───────┘                                                │
│         │                                                         │
│         │ 11.1V                                                   │
│         ├─────────────────┬──────────────────────────────────┐  │
│         │                 │                                   │  │
│    ┌────▼─────┐      ┌───▼────────────────────┐              │  │
│    │ DC-DC    │      │  Williams D-8224       │              │  │
│    │ Boost    │      │  Sound Board           │              │  │
│    │ ±12V     │      │                        │              │  │
│    └────┬─────┘      │  [5V Regulator]────────┼──→ 5V out   │  │
│         │            │  [Audio Amp]           │              │  │
│         │            └───┬────────────────────┘              │  │
│         │ ±12V           │ 5V                                │  │
│         │                │                                   │  │
│         ├────────────────┼─→ Williams ±12V in               │  │
│         │                │                                   │  │
│         │                ├──────────────┬──────────────┐     │  │
│         │                │              │              │     │  │
│         │           ┌────▼────────┐ ┌──▼───┐    ┌────▼──┐   │  │
│         │           │  Williams   │ │ATtiny│    │Manual │   │  │
│         │           │   Logic     │ │  85  │    │Button │   │  │
│         │           │   (5V)      │ │ (5V) │    │ Panel │   │  │
│         │           │             │ │      │    │       │   │  │
│         │           │  PB1 ◄──────┼─┼─Pin 2│    │       │   │  │
│         │           │  PB2 ◄──────┼─┼─Pin 4│    │       │   │  │
│         │           │             │ └──────┘    │       │   │  │
│         │           │  Pins 2-7◄──┼─────────────┼─Btns  │   │  │
│         │           │             │             └───────┘   │  │
│         │           │ Audio Out   │                         │  │
│         │           └─────┬───────┘                         │  │
│         │                 │                                 │  │
│      ┌──▼──────┐      ┌───▼───┐                            │  │
│      │ Speaker │◄─────┤Speaker│                            │  │
│      │  (Int.  │      │Connector                           │  │
│      │  Amp)   │      └───────┘                            │  │
│      └─────────┘                                            │  │
│                                                              │  │
│  GND ────────────────────────────────────────────────────────┤  │
│                                                              │  │
└──────────────────────────────────────────────────────────────┘
```

## ATtiny85 to Williams Board Connection

```
    ATtiny85                Williams D-8224
  ┌─────U─────┐           Connector Pins
  │           │           ┌────────────┐
  │1 RESET    │           │ 9 8 7 6 5 │
  │           │           │ ○ ○ ○ ○ ○ │
  │2 PB3      │           │           │
  │           │           │ 4 3 2 1   │
  │3 PB4      │           │ ○ ○ ○ *   │
  │           │           └────────────┘
  │4 GND ─────┼────────→ GND
  │           │
  │5 PB0      │
  │           │
  │6 PB1 ─────┼────────→ Pin 2 (Binary Value 1)
  │           │
  │7 PB2 ─────┼────────→ Pin 4 (Binary Value 4)
  │           │
  │8 VCC ─────┼────────→ Williams +5V (from onboard regulator)
  │           │
  └───────────┘

Note: Williams board regulates 11.1V battery to 5V internally.
ATtiny85 taps this regulated 5V supply.

Williams Connector Pins:
- Pin 1: No connection (marked with *)
- Pins 2-8: Sound select inputs
- Pin 9: Not used (not GND)
```

## Manual Button Interface

```
                Williams D-8224 Input Pins
                ┌──────────────────────┐
                │  2   3   4   5   7   │
                │  ○   ○   ○   ○   ○   │
                └──┬───┬───┬───┬───┬───┘
                   │   │   │   │   │
Button 1 (Value 1) ─┘   │   │   │   │
                        │   │   │   │
Button 2 (Value 2) ─────┘   │   │   │
                            │   │   │
Button 3 (Value 4) ─────────┘   │   │
                                │   │
Button 4 (Value 8) ─────────────┘   │
                                    │
Button 5 (Value 16)─────────────────┘

All button commons ──→ [FIRE Button] ──→ GND

Usage:
1. Hold one or more numbered buttons (1-5)
2. Press FIRE to ground the selection and trigger sound
3. Sound number = sum of held button values
```

## Sound Selection Examples

```
Held Buttons    Binary    Value    Sound #
────────────────────────────────────────────
Button 1        00001     1        Sound 1
Button 2        00010     2        Sound 2
Btns 1+2        00011     1+2=3    Sound 3
Button 3        00100     4        Sound 4
Btns 1+3        00101     1+4=5    Sound 5  ← Current ATtiny config
Btns 2+3        00110     2+4=6    Sound 6
Btns 1+2+3      00111     1+2+4=7  Sound 7
Button 4        01000     8        Sound 8
Btns 1+4        01001     1+8=9    Sound 9
...
Button 5        10000     16       Sound 16
All buttons     11111     31       Sound 31
```

## Power Distribution

```
11.1V LiPo Battery ──┬─→ Williams D-8224 Board ──→ Onboard 5V Regulator ──┬─→ Williams Logic
(3S)                 │                            (for logic circuits)     └─→ ATtiny85 VCC
                     │
                     └─→ DC-DC Boost Converter ──→ ±12V ──→ Williams Board ±12V Input
                                                             (for built-in audio amp)

                         Williams Audio Out ──→ Speaker

GND ─────────────────┴─→ Common Ground
```

**Power Architecture:**
- **11.1V Battery** → Williams board input (Williams regulates to 5V internally)
- **11.1V Battery** → ±12V boost converter → Williams board ±12V audio amp input
- **Williams 5V output** → Powers ATtiny85
- **Williams built-in audio amp** → Powered by ±12V, drives speaker directly
- **Common ground** for entire system

## Notes

- Williams board has internal pull-up resistors on input pins
- ATtiny uses high-impedance INPUT mode after triggering to avoid interference
- No isolation diodes needed in this simple configuration
- Manual buttons and ATtiny share the same input lines without conflict
- **Power Architecture:**
  - 11.1V LiPo battery (3S) feeds Williams board
  - Williams board has onboard 5V regulator for logic circuits
  - Williams board has built-in audio amplifier (powered by ±12V)
  - ATtiny85 powered from Williams 5V output
  - DC-DC boost converter provides ±12V from battery to Williams audio amp
  - Speaker connects directly to Williams audio output
- Total 5V current draw: Williams logic ~150mA, ATtiny ~4mA active / <0.01mA sleep
- ±12V current draw depends on volume (audio amp consumes most power)
- 11.1V battery capacity determines runtime (typical 3S LiPo: 2200-5000mAh)

## Optional Enhancements

### Status LED
```
PB0 ──[220Ω]──→|──→ GND
              LED
```

### Power Switch
```
Battery ──[SPST Switch]──→ System +5V
```

### Low Battery Indicator
```
Battery ─→ [Voltage Divider] ─→ (future microcontroller ADC)
```

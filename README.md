# Williams D-8224 FX Box Auto-Intro Sound Trigger

ATtiny85-based automatic intro sound trigger for Williams D-8224 arcade sound boards. Part of a larger FX sound box project that incorporates vintage arcade sound hardware into a portable, battery-powered device.

## Project Overview

This project uses an ATtiny85 microcontroller to automatically trigger a specific sound on a Williams D-8224 sound board (from 1980s arcade games like Defender and Stargate) when the FX box is powered on. After triggering the intro sound, the ATtiny enters deep sleep mode to conserve battery power.

The Williams D-8224 uses a 6802 CPU and software-based sound synthesis from ROM, making it perfect for creative repurposing in FX boxes and synthesizer projects.

## Features

- **Automatic intro sound** on power-up
- **Ultra-low power consumption** after triggering (microamps in sleep mode)
- **Non-interfering design** - doesn't affect manual button controls
- **Configurable timing** for different board variants
- **Simple 4-wire connection** to Williams board

## Hardware Requirements

- ATtiny85 microcontroller
- Williams D-8224 arcade sound board (complete with onboard 5V regulator and audio amplifier)
- 11.1V LiPo battery (3S)
- DC-DC boost converter (11.1V → ±12V)
- Speaker (connects to Williams board audio output)
- Optional: diodes if additional isolation needed

**Power Notes:**
- Williams board is a complete audio solution with built-in 5V regulator and audio amplifier
- Williams regulates 11.1V battery to 5V internally for logic circuits
- ATtiny85 is powered from Williams 5V output
- ±12V boost converter powers Williams built-in audio amplifier
- Speaker connects directly to Williams audio output

## Connections

### ATtiny85 Pinout
```
        ATtiny85
     ┌─────U─────┐
RESET│1         8│VCC (+5V)
  PB3│2         7│PB2 → Williams Pin 4
  PB4│3         6│PB1 → Williams Pin 2
  GND│4         5│PB0
     └───────────┘
```

### Wiring Table

| ATtiny85 Pin | Function | Williams Board Connection |
|--------------|----------|---------------------------|
| Pin 8 (VCC)  | Power    | +5V                       |
| Pin 4 (GND)  | Ground   | GND                       |
| Pin 6 (PB1)  | Output   | Connector Pin 2 (Binary 1)|
| Pin 7 (PB2)  | Output   | Connector Pin 4 (Binary 4)|

**Current Configuration:** Triggers Sound #5 (binary 00101 = 1+4)

## Williams D-8224 Sound Selection

The Williams board uses binary encoding on 5 input pins to select from up to 32 sounds:

| Connector Pin | Binary Value |
|---------------|--------------|
| Pin 2         | 1            |
| Pin 3         | 2            |
| Pin 4         | 4            |
| Pin 5         | 8            |
| Pin 7         | 16           |

Sounds are triggered by pulling the desired combination of pins LOW simultaneously.

### Changing the Intro Sound

To trigger a different sound, modify the pin assignments in the code:

**Example - Sound #7 (binary 00111 = 1+2+4):**
```cpp
const int connectorPin2 = 1;    // PB1 -> Pin 2 (value 1)
const int connectorPin3 = 2;    // PB2 -> Pin 3 (value 2)
const int connectorPin4 = 3;    // PB3 -> Pin 4 (value 4)
```

## Timing Parameters

```cpp
const int bootDelay = 2000;         // Williams boot time (2 seconds)
const int triggerDuration = 200;    // Trigger pulse width (200ms)
```

Adjust these if your board requires different timing:
- Increase `bootDelay` if intro sound doesn't trigger reliably
- Increase `triggerDuration` if sound doesn't play consistently

## Programming the ATtiny85

### Arduino IDE Setup

1. Install ATtiny board support:
   - **File → Preferences**
   - Add to "Additional Boards Manager URLs": 
     ```
     https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
     ```
   - **Tools → Board → Boards Manager**
   - Search for "attiny" and install

2. Select board settings:
   - **Board:** ATtiny25/45/85
   - **Processor:** ATtiny85
   - **Clock:** Internal 8 MHz
   - **Programmer:** USBasp (or your programmer)

3. Upload the sketch

### Using Arduino as ISP

If you don't have a dedicated programmer, you can use an Arduino Uno as an ISP programmer. See the [Arduino ISP tutorial](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP).

## Power Consumption

- **Active (trigger sequence):** ~4-8mA for ~2.2 seconds
- **Sleep mode:** <10µA (microamps)
- **Total power impact:** Negligible on battery-powered FX box

## Integration with Manual Controls

The FX box includes 5 manual buttons plus a "fire" button for user-triggered sounds. The ATtiny design uses high-impedance mode after triggering, ensuring it doesn't interfere with manual button operation.

### Manual Button Wiring
- Each of the 5 buttons connects to one Williams input pin (2, 3, 4, 5, 7)
- All buttons share a common line to the "fire" button
- Fire button connects to GND
- Users hold button combinations, then press fire to trigger

The ATtiny shares the same input pins but doesn't interfere because it returns to INPUT mode (high-Z) after the intro sequence.

## Troubleshooting

**Intro sound doesn't play:**
- Increase `bootDelay` to 3000ms or higher
- Check all 4 wire connections
- Verify ATtiny is receiving 5V power
- Test Williams board with manual buttons first

**Wrong sound plays:**
- Verify you're connecting to the correct Williams connector pins
- Check binary math for your desired sound number
- Ensure pins return to INPUT mode after triggering

**Manual buttons don't work:**
- Verify ATtiny code sets pins to INPUT mode after trigger
- Check for shorts or incorrect wiring
- Test manual buttons with ATtiny disconnected

## Related Projects

This is part of a larger Williams D-8224 FX box project that includes:
- Manual 5-button + fire interface
- Built-in speaker
- Rechargeable battery power
- Portable enclosure

Future plans include converting a Williams board into a MIDI-controlled synthesizer while preserving the original ROM synthesis routines.

## Technical Background

The Williams D-8224 is a software-based sound synthesis board from early 1980s arcade games. Unlike boards with dedicated sound chips, the D-8224 uses a 6802 CPU running synthesis routines from ROM. This makes it particularly well-suited for creative repurposing, as the authentic "arcade sound" character is preserved in software.

## License

MIT License - Feel free to use and modify for your own projects.

## Credits

Based on ATtiny85 laser gun trigger project. Williams D-8224 documentation from MAME project and arcade preservation community.

## Contributing

Have improvements or found bugs? Pull requests welcome!

---

**Happy arcade hacking!** 🎮🔊

# Changelog

All notable changes to this project will be documented in this file.

## [1.2.0] - 2026-02-07

### Changed
- **Cleaner sequential pin mapping** - PB0, PB1, PB2, PB3, PB4 in order
- Updated button connector to 6 pins (5 buttons + GND for FIRE button)
- Simplified PCB routing with logical button-to-pin correspondence

### Technical Details - New Mapping
- Button Pin 1 → PB0 (ATtiny pin 5) → Williams Pin 2 (Binary 1)
- Button Pin 2 → PB1 (ATtiny pin 6) → Williams Pin 3 (Binary 2)
- Button Pin 3 → PB2 (ATtiny pin 7) → Williams Pin 4 (Binary 4)
- Button Pin 4 → PB3 (ATtiny pin 2) → Williams Pin 5 (Binary 8)
- Button Pin 5 → PB4 (ATtiny pin 3) → Williams Pin 7 (Binary 16)
- Button Pin 6 → GND (for FIRE button)

## [1.1.0] - 2026-02-07

### Added
- **Full 5-pin support** - Now connects to all Williams sound input pins (2,3,4,5,7)
- **Automatic sound decoding** - Simply set `introSound` variable (1-31), code handles pin logic
- **Button panel connector** - 6-pin connector (5 buttons + GND for FIRE button)
- **PCB-friendly sequential mapping** - PB0-PB4 maps cleanly to button panel pins 1-5

### Changed
- **Default sound changed to #31** - Discovered this is the Williams startup sound (all pins grounded)
- **Sequential pin mapping** for cleaner PCB routing and intuitive button panel connection
- Simplified sound selection - no manual pin configuration needed
- Updated all documentation and diagrams for new pin mapping

### Technical Details
Pin Mapping (Sequential PB0-PB4):
- Williams Pin 2 → ATtiny Pin 5 (PB0) - Binary 1  → Button Panel Pin 1
- Williams Pin 3 → ATtiny Pin 6 (PB1) - Binary 2  → Button Panel Pin 2
- Williams Pin 4 → ATtiny Pin 7 (PB2) - Binary 4  → Button Panel Pin 3
- Williams Pin 5 → ATtiny Pin 2 (PB3) - Binary 8  → Button Panel Pin 4
- Williams Pin 7 → ATtiny Pin 3 (PB4) - Binary 16 → Button Panel Pin 5
- GND → Button Panel Pin 6 (for FIRE button)

Sound #31 (binary 11111) grounds all 5 pins for authentic Williams startup sound

## [1.0.0] - 2026-02-01

### Initial Release
- ATtiny85 auto-trigger for Williams D-8224 sound boards
- Triggers Sound #5 (pins 2+4, binary value 5) on power-up
- 1 second boot delay for Williams board initialization (optimized from 2 seconds)
- 200ms trigger pulse duration
- Ultra-low power sleep mode after triggering (<10µA)
- Non-interfering design compatible with manual button controls

### Features
- Configurable sound selection via pin assignments
- Adjustable timing parameters for different board variants
- Power-saving peripheral shutdown
- Based on proven laser gun trigger architecture

### Documentation
- Complete README with pinout diagrams
- Circuit documentation and schematics
- Troubleshooting guide
- Integration instructions for manual controls

## Future Plans

### Version 1.1 (Planned)
- [ ] Optional status LED on PB0
- [ ] Multiple intro sound sequences
- [ ] Configurable delay via hardware jumper

### Version 2.0 (Planned)
- [ ] Random intro sound selection
- [ ] Button-activated sound sequence (not just power-on)
- [ ] Low battery detection and warning

### Long-term Goals
- Williams D-8224 to MIDI synthesizer conversion
- Preserve original ROM synthesis routines
- External keyboard/MIDI input while maintaining authentic sound

## Notes

- Current configuration tested with Williams D-8224 from Defender/Stargate
- Boot delay of 1 second works reliably, may vary with different boards
- Manual button panel shares input pins without conflict
- ATtiny draws negligible power in sleep mode - excellent for battery operation

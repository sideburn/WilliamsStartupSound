# Changelog

All notable changes to this project will be documented in this file.

## [1.0.0] - 2026-02-01

### Initial Release
- ATtiny85 auto-trigger for Williams D-8224 sound boards
- Triggers Sound #5 (pins 2+4, binary value 5) on power-up
- 2 second boot delay for Williams board initialization
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
- Boot delay of 2 seconds works reliably, may vary with different boards
- Manual button panel shares input pins without conflict
- ATtiny draws negligible power in sleep mode - excellent for battery operation

/*
 * Williams D-8224 Sound Board Auto-Intro Trigger
 * ATtiny85 Implementation
 * 
 * Triggers a specific sound on the Williams D-8224 arcade sound board
 * on power-up, then goes to sleep to conserve battery.
 * 
 * Target: ATtiny85
 * 
 * Physical Connections (PCB routes with sequential PB0-PB4 mapping):
 * - Williams Pin 2 -> ATtiny Physical Pin 5 (PB0) - Binary value 1
 * - Williams Pin 3 -> ATtiny Physical Pin 6 (PB1) - Binary value 2
 * - Williams Pin 4 -> ATtiny Physical Pin 7 (PB2) - Binary value 4
 * - Williams Pin 5 -> ATtiny Physical Pin 2 (PB3) - Binary value 8
 * - Williams Pin 7 -> ATtiny Physical Pin 3 (PB4) - Binary value 16
 * - ATtiny VCC (pin 8) -> Williams +5V
 * - ATtiny GND (pin 4) -> Williams GND
 * 
 * Author: Tavis
 * Date: February 2026
 * Based on laser gun trigger project
 */

#include <avr/sleep.h>
#include <avr/power.h>

// ===== SOUND SELECTION - CHANGE THIS TO PICK YOUR INTRO SOUND =====
const int introSound = 22;  // Sound #31 = startup sound (all pins grounded)
// ==================================================================

// Pin assignments (Arduino pin numbers correspond to PBx port bits)
// Sequential mapping: PB0, PB1, PB2, PB3, PB4
const int williamsPin2 = 0;  // PB0 -> ATtiny physical pin 5 -> Williams pin 2 (binary 1)
const int williamsPin3 = 1;  // PB1 -> ATtiny physical pin 6 -> Williams pin 3 (binary 2)
const int williamsPin4 = 2;  // PB2 -> ATtiny physical pin 7 -> Williams pin 4 (binary 4)
const int williamsPin5 = 3;  // PB3 -> ATtiny physical pin 2 -> Williams pin 5 (binary 8)
const int williamsPin7 = 4;  // PB4 -> ATtiny physical pin 3 -> Williams pin 7 (binary 16)

// Timing parameters
const int bootDelay = 1000;         // Williams board boot time (ms)
const int triggerDuration = 200;    // How long to hold pins low (ms)

void setup() {
  // Disable unnecessary peripherals to save battery power
  power_adc_disable();
  power_usi_disable();
  power_timer1_disable();
  
  // Wait for Williams board to complete its boot sequence
  delay(bootDelay);
  
  // Configure all pins as high-impedance inputs initially
  pinMode(williamsPin2, INPUT);
  pinMode(williamsPin3, INPUT);
  pinMode(williamsPin4, INPUT);
  pinMode(williamsPin5, INPUT);
  pinMode(williamsPin7, INPUT);
  
  // CRITICAL: Set all pins LOW simultaneously using direct port manipulation
  // Williams board samples all 5 pins at once - they must all be LOW at the same instant!
  // introSound maps directly to port bits: bit 0=PB0, bit 1=PB1, bit 2=PB2, bit 3=PB3, bit 4=PB4
  
  uint8_t pinsToActivate = introSound & 0x1F;  // Mask to 5 bits (0-31)
  
  // Set pins as outputs atomically
  DDRB |= pinsToActivate;
  
  // Pull them all LOW atomically (single instruction!)
  PORTB &= ~pinsToActivate;
  
  // Hold trigger for specified duration
  delay(triggerDuration);
  
  // Release all pins back to high-impedance input mode atomically
  // This prevents interference with manual button controls
  DDRB &= ~0x1F;  // Set PB0-PB4 as inputs (all 5 pins at once)
  PORTB &= ~0x1F; // Disable pull-ups on PB0-PB4
  
  // PROGRAMMING SAFETY: Wait 5 seconds before sleeping
  // This gives you a window to reprogram if needed
  // Comment out this line once you're done testing
  delay(5000);
  
  // Enter deep sleep mode - job complete!
  // ATtiny will draw microamps in this state
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // Never reached - ATtiny sleeps forever after setup() completes
}

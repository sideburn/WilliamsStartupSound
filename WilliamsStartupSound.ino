/*
 * Williams D-8224 Sound Board Auto-Intro Trigger
 * ATtiny85 Implementation
 * 
 * Triggers a specific sound on the Williams D-8224 arcade sound board
 * on power-up, then goes to sleep to conserve battery.
 * 
 * Target: ATtiny85
 * 
 * Physical Connections:
 * - ATtiny85 PB1 (pin 6) -> Williams connector pin 2 (binary input 1)
 * - ATtiny85 PB2 (pin 7) -> Williams connector pin 4 (binary input 4)
 * - ATtiny85 VCC (pin 8) -> Williams +5V
 * - ATtiny85 GND (pin 4) -> Williams GND
 * 
 * This configuration triggers sound #5 (binary 00101 = pins 2+4 = 1+4)
 * 
 * Author: Tavis
 * Date: February 2026
 * Based on laser gun trigger project
 */

#include <avr/sleep.h>
#include <avr/power.h>

// Pin assignments (ATtiny85 port B pins)
const int connectorPin2 = 1;    // PB1 -> Williams connector pin 2 (binary value 1)
const int connectorPin4 = 2;    // PB2 -> Williams connector pin 4 (binary value 4)

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
  
  // Configure pins as outputs and pull LOW to trigger sound
  // Williams board has pull-up resistors, so LOW triggers the input
  pinMode(connectorPin2, OUTPUT);
  pinMode(connectorPin4, OUTPUT);
  digitalWrite(connectorPin2, LOW);
  digitalWrite(connectorPin4, LOW);
  
  // Hold trigger for specified duration
  delay(triggerDuration);
  
  // Release pins back to high-impedance input mode
  // This prevents interference with manual button controls
  pinMode(connectorPin2, INPUT);
  pinMode(connectorPin4, INPUT);
  
  // Enter deep sleep mode - job complete!
  // ATtiny will draw microamps in this state
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // Never reached - ATtiny sleeps forever after setup() completes
}

/*
 * ATtiny85 Williams Sound Board Auto-Intro Trigger
 * 
 * Triggers sound #5 (pins 1+3) on power-up, then sleeps forever.
 */

#include <avr/sleep.h>
#include <avr/power.h>

const int connectorPin2 = 1;    // PB1 -> Williams connector pin 2 (binary 1)
const int connectorPin4 = 2;    // PB2 -> Williams connector pin 4 (binary 4)
const int bootDelay = 2000;     // Williams board boot time (ms)
const int triggerDuration = 200; // How long to hold pins low (ms)

void setup() {
  // Disable unnecessary peripherals to save power
  power_adc_disable();
  power_usi_disable();
  power_timer1_disable();
  
  // Wait for Williams board to boot up
  delay(bootDelay);
  
  // Configure pins as outputs and pull LOW to trigger sound
  pinMode(input1Pin, OUTPUT);
  pinMode(input3Pin, OUTPUT);
  digitalWrite(input1Pin, LOW);
  digitalWrite(input3Pin, LOW);
  
  // Hold trigger
  delay(triggerDuration);
  
  // Release pins back to high-impedance (won't interfere with manual buttons)
  pinMode(input1Pin, INPUT);
  pinMode(input3Pin, INPUT);
  
  // Go to deep sleep forever - job done!
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // Never reached - ATtiny sleeps forever after setup()
}
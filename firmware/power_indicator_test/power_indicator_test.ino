/*
 * ==============================================================================
 * Project: StepCharge - Footstep Piezoelectric Energy Harvesting
 * Sketch: power_indicator_test.ino
 * Target Board: Arduino UNO R3 (ATmega328P)
 * Stage: Stage 7 - Battery 5V Power Output & Arduino Load Verification
 * Description:
 *   Verifies that the Arduino UNO is successfully powered by the 5V output
 *   from the DIY PowerBank module. It blinks an indicator LED on Pin D8
 *   (with a 200 Ohm series resistor) in a gentle breathing/heartbeat pattern.
 *
 * WIRING:
 *   PowerBank 5V Output  --> Arduino 5V pin (or USB Type-B plug)
 *   PowerBank GND        --> Arduino GND
 *   Arduino D8           --> 200 Ohm Resistor --> LED Anode (+)
 *   LED Cathode (-)      --> Arduino GND
 * ==============================================================================
 */

// --- PIN DEFINITIONS ---
const int STATUS_LED_PIN = 8;   // External LED with 200 Ohm resistor
const int ONBOARD_LED_PIN = 13; // Built-in LED

// --- TIMING PARAMETERS ---
const unsigned long HEARTBEAT_INTERVAL_MS = 1000;

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  Serial.begin(115200);
  delay(200);

  Serial.println(F("=================================================="));
  Serial.println(F("Stage 7: Power Indicator & System Alive Test"));
  Serial.println(F("System is successfully powered via 5V Power Output!"));
  Serial.println(F("=================================================="));
}

void loop() {
  // Double-blink heartbeat pattern
  // First pulse
  digitalWrite(STATUS_LED_PIN, HIGH);
  digitalWrite(ONBOARD_LED_PIN, HIGH);
  delay(80);
  digitalWrite(STATUS_LED_PIN, LOW);
  digitalWrite(ONBOARD_LED_PIN, LOW);
  delay(100);

  // Second pulse
  digitalWrite(STATUS_LED_PIN, HIGH);
  digitalWrite(ONBOARD_LED_PIN, HIGH);
  delay(80);
  digitalWrite(STATUS_LED_PIN, LOW);
  digitalWrite(ONBOARD_LED_PIN, LOW);

  // Heartbeat log
  unsigned long uptimeSeconds = millis() / 1000;
  Serial.print(F("[Alive] Uptime: "));
  Serial.print(uptimeSeconds);
  Serial.println(F(" s | Power status: Normal"));

  // Pause between heartbeats
  delay(HEARTBEAT_INTERVAL_MS);
}

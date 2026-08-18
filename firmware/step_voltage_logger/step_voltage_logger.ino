/*
 * ==============================================================================
 * Project: StepCharge - Footstep Piezoelectric Energy Harvesting
 * Sketch: step_voltage_logger.ino
 * Target Board: Arduino UNO R3 (ATmega328P)
 * Description:
 *   Reads analog voltage from the Piezo / Storage Capacitor stage,
 *   detects voltage peaks (footsteps), counts steps, and outputs data
 *   formatted for the Arduino IDE Serial Plotter / Serial Monitor.
 *
 * SAFETY NOTE:
 *   - NEVER connect raw unrectified Piezo directly to Arduino analog pins.
 *   - Ensure Piezo is rectified (Bridge) and buffered through a capacitor.
 *   - If voltage exceeds 5V, use a suitable Voltage Divider circuit.
 * ==============================================================================
 */

// --- PIN DEFINITIONS ---
const int ANALOG_PIN = A0;      // Analog pin connected to voltage source (or divider output)
const int LED_STEP_PIN = 13;    // Onboard LED blink on footstep detected

// --- VOLTAGE DIVIDER CALIBRATION ---
// If measuring directly (0 - 5.0V): R1 = 0, R2 = 1.0 (multiplier = 1.0)
// If using voltage divider for higher voltages (e.g. R1=10k, R2=10k -> multiplier = 2.0):
const float VOLTAGE_DIVIDER_RATIO = 1.0; // V_actual = V_measured * VOLTAGE_DIVIDER_RATIO
const float ARDUINO_VREF = 5.0;          // Reference voltage of Arduino UNO (typically 5.0V)

// --- THRESHOLD & PEAK DETECTION SETTINGS ---
const float STEP_THRESHOLD_VOLTAGE = 1.0; // Minimum voltage (V) to qualify as a step
const unsigned long DEBOUNCE_MS = 250;   // Minimum ms between consecutive steps

// --- GLOBAL VARIABLES ---
unsigned long stepCount = 0;
unsigned long lastStepTime = 0;
float currentVoltage = 0.0;
float peakVoltage = 0.0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_STEP_PIN, OUTPUT);
  digitalWrite(LED_STEP_PIN, LOW);

  // Wait for serial monitor to open (useful for native USB, safe for UNO)
  delay(500);

  Serial.println(F("=================================================="));
  Serial.println(F("StepCharge - Piezoelectric Voltage & Step Logger"));
  Serial.println(F("Format for Serial Plotter: Voltage, Peak, Steps"));
  Serial.println(F("=================================================="));
}

void loop() {
  // Read analog value (0 - 1023)
  int rawADC = analogRead(ANALOG_PIN);

  // Convert raw ADC to measured voltage at pin
  float pinVoltage = (rawADC * ARDUINO_VREF) / 1023.0;

  // Calculate actual source voltage based on divider ratio
  currentVoltage = pinVoltage * VOLTAGE_DIVIDER_RATIO;

  // Track maximum peak voltage
  if (currentVoltage > peakVoltage) {
    peakVoltage = currentVoltage;
  }

  // Step detection with threshold and software debounce
  unsigned long now = millis();
  if (currentVoltage >= STEP_THRESHOLD_VOLTAGE && (now - lastStepTime > DEBOUNCE_MS)) {
    stepCount++;
    lastStepTime = now;

    // Visual pulse on LED
    digitalWrite(LED_STEP_PIN, HIGH);
  }

  // Turn off LED 50ms after step
  if (now - lastStepTime > 50) {
    digitalWrite(LED_STEP_PIN, LOW);
  }

  // Decay peak voltage slowly over time for dynamic visualization
  peakVoltage *= 0.995;

  // Output formatted for Arduino Serial Plotter (label:value)
  Serial.print(F("Voltage_V:"));
  Serial.print(currentVoltage, 2);
  Serial.print(F(" "));
  Serial.print(F("Peak_V:"));
  Serial.print(peakVoltage, 2);
  Serial.print(F(" "));
  Serial.print(F("StepCount:"));
  Serial.println(stepCount);

  delay(20); // ~50Hz sampling rate
}

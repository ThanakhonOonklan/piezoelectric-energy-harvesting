// --- PIN DEFINITIONS ---
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int LED_PIN = 8;

// --- SETTINGS ---
const float DISTANCE_THRESHOLD_CM = 50.0; // Trigger LED if distance < 50 cm
const unsigned long TIMEOUT_US = 25000; // Timeout for pulseIn (~4 meters range)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  delay(200);

  Serial.println(F("=================================================="));
  Serial.println(F("Future Scope: HC-SR04 Distance Trigger Test"));
  Serial.print(F("Threshold: "));
  Serial.print(DISTANCE_THRESHOLD_CM);
  Serial.println(F(" cm"));
  Serial.println(F("=================================================="));
}

float measureDistanceCm() {
  // Clear trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10 microsecond HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration in microseconds
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);

  if (duration == 0) {
    // Timeout or out of range
    return -1.0;
  }

  // Speed of sound: ~343 m/s = 0.0343 cm/us -> Distance = (duration * 0.0343) /
  // 2
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}

void loop() {
  float distance = measureDistanceCm();

  if (distance > 0 && distance < DISTANCE_THRESHOLD_CM) {
    // Object detected within threshold
    digitalWrite(LED_PIN, HIGH);
    Serial.print(F("[TRIGGER] Distance: "));
    Serial.print(distance, 1);
    Serial.println(F(" cm -> LED ON"));
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print(F("[IDLE]    Distance: "));
    if (distance < 0) {
      Serial.println(F("Out of range -> LED OFF"));
    } else {
      Serial.print(distance, 1);
      Serial.println(F(" cm -> LED OFF"));
    }
  }

  delay(100); // 10Hz sampling
}

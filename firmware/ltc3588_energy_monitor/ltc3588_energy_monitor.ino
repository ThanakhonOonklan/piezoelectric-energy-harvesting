const int PIN_VIN = A0;
const int PIN_VCC = A1;
const int PIN_EN  = 2;
const int PIN_LED = 13;

const float UVLO_RISING_V = 5.00;

int burstCount = 0;
bool isDischarging = false;
unsigned long lastPrintTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_EN, INPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  delay(300);
  Serial.println(F("--- LTC3588 Energy Monitor Ready ---"));
}

void loop() {
  float vIn  = (analogRead(PIN_VIN) * 5.0) / 1023.0;
  float vOut = (analogRead(PIN_VCC) * 5.0) / 1023.0;
  int enSignal = digitalRead(PIN_EN);

  int percent = (vIn / UVLO_RISING_V) * 100;
  if (percent > 100) percent = 100;
  if (percent < 0) percent = 0;

  if ((vOut > 2.5 || enSignal == HIGH) && !isDischarging) {
    burstCount++;
    isDischarging = true;
    digitalWrite(PIN_LED, HIGH);
    Serial.println(F("💥 [ ปล่อยไฟ 3.3V แล้ว! ]"));
  }

  if (vOut < 1.0 && enSignal == LOW) {
    isDischarging = false;
    digitalWrite(PIN_LED, LOW);
  }

  unsigned long now = millis();
  if (now - lastPrintTime >= 100) {
    lastPrintTime = now;

    Serial.print(vIn, 2);
    Serial.print(F(" / 5.00 V   ("));
    Serial.print(percent);
    Serial.print(F("%)   |   รอบปล่อยไฟ: "));
    Serial.println(burstCount);
  }

  delay(20);
}

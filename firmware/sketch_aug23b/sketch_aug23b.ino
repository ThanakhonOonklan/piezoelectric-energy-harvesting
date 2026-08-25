/*
 * StepCharge - Piezo Voltage & Step Counter (Serial Output)
 * บอร์ด: Arduino UNO R3
 * ขาเชื่อมต่อ: A0 (ไฟบวก Piezo), GND (ไฟลบ Piezo)
 */

const int PIEZO_PIN = A0;   // ขาต่อรับแรงดันจาก Piezo
const int LED_PIN = 13;     // ไฟ LED บนบอร์ด Arduino (กะพริบเวลานับก้าว)

int steps = 0;              // ตัวแปรนับจำนวนก้าว
bool detected = false;      // ตัวแปรเช็คสถานะการกด
unsigned long lastStepTime = 0;
const unsigned long DEBOUNCE_MS = 200; // ป้องกันการนับเบิ้ลซ้ำใน 200ms

void setup() {
  Serial.begin(9600);       // ตั้งค่า Baud Rate สำหรับ Serial
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("==================================");
  Serial.println(" StepCharge: Voltage & Step Count ");
  Serial.println("==================================");
}

void loop() {
  // 1. อ่านค่าแรงดัน Analog (0 - 1023)
  int rawValue = analogRead(PIEZO_PIN);
  
  // 2. แปลงเป็นค่าโวลต์จริง (0.0 - 5.0V)
  float voltage = (rawValue / 1023.0) * 5.0;

  // 3. ตรวจจับการกด (ถ้าแรงดันมากกว่า 0.5V ให้เริ่มนับก้าว)
  unsigned long currentTime = millis();
  if (voltage > 0.5 && !detected && (currentTime - lastStepTime > DEBOUNCE_MS)) {
    steps++;
    detected = true;
    lastStepTime = currentTime;
    
    // เปิดไฟ LED บนบอร์ดกระพริบเพื่อแสดงว่านับ 1 ก้าวแล้ว
    digitalWrite(LED_PIN, HIGH);
  }

  // รีเซ็ตสถานะเมื่อแรงดันลดลงต่ำกว่าเกณฑ์
  if (voltage < 0.2) {
    detected = false;
    digitalWrite(LED_PIN, LOW);
  }

  // 4. ส่งข้อมูลออกทาง Serial Monitor และ Serial Plotter
  Serial.print("Voltage:");
  Serial.print(voltage, 2);
  Serial.print("V | ");
  Serial.print("Steps:");
  Serial.println(steps);

  delay(50); // อัปเดตทุกๆ 50ms (แสดงผลลื่นไหล)
}

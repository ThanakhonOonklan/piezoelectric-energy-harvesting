# ⚡ StepCharge: Footstep Piezoelectric Energy Harvesting System

ระบบต้นแบบเก็บเกี่ยวพลังงานจากการเหยียบ (Footstep Piezoelectric Energy Harvesting Prototype) เปลี่ยนแรงกดเชิงกลจากการก้าวเดินเป็นพลังงานไฟฟ้า จัดการและกักเก็บพลังงานลงในแบตเตอรี่ 18650 Li-ion และจ่ายไฟออก 5V เพื่อนำกลับมาใช้งานกับ Arduino UNO, LED และโหลดภายนอก

---

## 📁 โครงสร้างโปรเจกต์ (Project Structure)

```text
piezoelectric-energy-harvesting/
├── firmware/                           # โค้ด Arduino UNO (เปิดใน Arduino IDE ได้ทันที)
│   ├── step_voltage_logger/            # โค้ดวัดแรงดัน Piezo / นับก้าวส่งออก Serial Plotter
│   │   └── step_voltage_logger.ino
│   ├── power_indicator_test/           # โค้ดทดสอบ Load 5V (LED Blink Heartbeat)
│   │   └── power_indicator_test.ino
│   └── future_distance_trigger/        # โค้ดระยะถัดไป (HC-SR04 Ultrasonic + LED Trigger)
│       └── future_distance_trigger.ino
│
├── hardware/                           # ข้อมูลสเปก Pinout และไดอะแกรมการต่อวงจร
│   ├── modules/                        # สเปกโมดูล LTC3588, TP4056, PowerBank Module
│   │   ├── ltc3588.md
│   │   ├── tp4056.md
│   │   └── powerbank_module.md
│   └── wiring/                         # แผนผังการต่อสายไฟของแต่ละ Stage
│       └── stage_wiring_guide.md
│
├── experiments/                        # ตารางและเทมเพลตบันทึกผลการทดลองจริง
│   ├── stage1_piezo_characterization.md# บันทึกผล Stage 1 (Piezo 4 ตัว + Rectifier + 470µF)
│   └── stage2_series_vs_parallel.md    # บันทึกผล Stage 2 (Series vs Parallel)
│
├── doc/                                # เอกสารและ Roadmap ความปลอดภัย
│   ├── step-charge-ai-context.md       # Master AI Knowledge Base & Context
│   └── safety-guidelines.md            # กฎความปลอดภัย Li-ion & Voltage Protection
│
└── image/                              # รูปภาพประกอบและรูปภาพวงจรจริง
```

---

## 🛠️ รายการอุปกรณ์และฮาร์ดแวร์ (Hardware Inventory)

| หมวดหมู่ | อุปกรณ์ | จำนวน | รายละเอียด |
|---|---|:---:|---|
| **Power Generation** | Piezoelectric Disc 35mm | 10 ตัว | แหล่งกำเนิดไฟฟ้าจากแรงกด |
| | 1N4007 Diode | 20 ตัว | ไดโอดสำหรับ Bridge Rectifier |
| | 470µF Electrolytic Capacitor | 2 ตัว | Smoothing / Energy Buffer |
| **Storage & Management**| 18650 Li-ion Battery | 2 ก้อน | Nominal 3.7V, Flat Top |
| | 18650 2-Cell Parallel Holder | 1 อัน | รางถ่านแบบขนาน (1S2P) |
| | LTC3588 Energy Harvester Module | 1 บอร์ด | Nanopower Piezo Harvester & Buck |
| | TP4056 USB-C Charger | 1 บอร์ด | ชาร์จ Li-ion CC/CV พร้อม Protection |
| | DIY PowerBank Module | 1 บอร์ด | 1S Input -> 5V 2A Boost Output |
| **Logic & Indicators** | Arduino UNO R3 | 2 บอร์ด | บอร์ดประมวลผลหลักและสำรอง |
| | LED หลากสี | 20 ตัว | ไฟแสดงสถานะ |
| | ตัวต้านทาน 200Ω | - | จำกัดกระแส LED |
| **Tools & Accessories** | Breadboard ขนาดกลาง | 2 อัน | สำหรับต่อวงจรทดลอง |
| | Jumper Wire / Hookup Wire 22AWG | - | สายไฟทดลอง (แดง/ดำ) |
| | Digital Multimeter | 1 เครื่อง | เครื่องมือวัด V, I, R |
| | อุปกรณ์และตะกั่วบัดกรี | 1 ชุด | |

---

## 🚀 ลำดับขั้นตอนการพัฒนาและการทดลอง (Development Stages)

- [ ] **Stage 1 — Piezo Characterization:** วัดแรงดัน $V_{peak}$, $V_{cap}$ ($470\mu\text{F}$) และอัตราการคายประจุจาก Piezo 4 ตัว
- [ ] **Stage 2 — Series vs Parallel Comparison:** เปรียบเทียบประสิทธิภาพการต่อ Piezo แบบอนุกรมและขนาน
- [ ] **Stage 3 — LTC3588 Harvesting:** ทดสอบโมดูล LTC3588 ในการแปลงและควบคุมแรงดัน
- [ ] **Stage 4 — Battery Baseline Test:** ทดสอบชาร์จ 18650 ผ่าน TP4056 ด้วยไฟ USB 5V ปกติ
- [ ] **Stage 5 — Storage Integration:** ประเมินและส่งพลังงานเข้าสู่ Battery System
- [ ] **Stage 6 — Battery to 5V Output:** ทดสอบ DIY PowerBank Module แปลงไฟจาก 18650 เป็น 5V
- [ ] **Stage 7 — Arduino & LED Verification:** นำไฟ 5V มาเลี้ยงบอร์ด Arduino UNO รันโค้ด `power_indicator_test.ino`
- [ ] **Future Scope — Distance Sensor:** เพิ่ม HC-SR04 รันโค้ด `future_distance_trigger.ino`

---

## 💻 วิธีการเปิดโค้ดใน Arduino IDE

1. ติดตั้ง **Arduino IDE** (เวอร์ชัน 2.x หรือ 1.8.x)
2. เปิดโฟลเดอร์ Firmware ที่ต้องการทดสอบ เช่น:
   - โค้ดวัดแรงดันและนับก้าว: เปิดไฟล์ [step_voltage_logger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/step_voltage_logger/step_voltage_logger.ino)
   - โค้ดทดสอบสถานะไฟ 5V: เปิดไฟล์ [power_indicator_test.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/power_indicator_test/power_indicator_test.ino)
   - โค้ดเซนเซอร์ระยะทาง: เปิดไฟล์ [future_distance_trigger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/future_distance_trigger/future_distance_trigger.ino)
3. เลือกบอร์ดเป็น **Arduino Uno** และเลือก COM Port ให้ตรงกับที่เชื่อมต่อ
4. กดปุ่ม **Verify (✓)** เพื่อตรวจสอบไวยากรณ์ และกด **Upload (➔)** เพื่ออัปโหลดลงบอร์ด
5. เปิด **Tools -> Serial Monitor** หรือ **Serial Plotter** (ตั้ง Baud Rate เป็น `115200`)

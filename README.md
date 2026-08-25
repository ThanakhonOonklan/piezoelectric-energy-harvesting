# ⚡ StepCharge: Footstep Piezoelectric Energy Harvesting System

ระบบต้นแบบเก็บเกี่ยวพลังงานจากการเหยียบ (Footstep Piezoelectric Energy Harvesting Prototype) เปลี่ยนแรงกดเชิงกลจากการก้าวเดินเป็นพลังงานไฟฟ้า จัดการและกักเก็บพลังงานลงในแบตเตอรี่ 18650 Li-ion และจ่ายไฟออก 5V เพื่อนำกลับมาใช้งานกับ Arduino UNO, LED และโหลดภายนอก

---

## 📁 โครงสร้างโปรเจกต์ (Project Structure)

```text
piezoelectric-energy-harvesting/
├── firmware/                           # โค้ด Arduino UNO (เปิดใน Arduino IDE ได้ทันที)
│   ├── ltc3588_energy_monitor/         # โค้ดวัดระดับพลังงานสะสม (mJ, %) และนับรอบ Burst ของ LTC3588
│   │   └── ltc3588_energy_monitor.ino
│   ├── step_voltage_logger/            # โค้ดวัดแรงดัน Piezo / นับก้าวส่งออก Serial Plotter
│   │   └── step_voltage_logger.ino
│   ├── power_indicator_test/           # โค้ดทดสอบ Load 5V (LED Blink Heartbeat)
│   │   └── power_indicator_test.ino
│   └── future_distance_trigger/        # โค้ดระยะถัดไป (HC-SR04 Ultrasonic + LED Trigger)
│       └── future_distance_trigger.ino
│
├── hardware/                           # ข้อมูลสเปก Pinout และไดอะแกรมการต่อวงจร
│   ├── modules/                        # สเปกอุปกรณ์แต่ละตัว (จากฮาร์ดแวร์จริง)
│   │   ├── battery_18650.md            # GLINK 18650 2600mAh & 1S2P Holder
│   │   ├── capacitor.md                # 470µF 16V Electrolytic Buffer Capacitor
│   │   ├── ltc3588.md                  # CJMCU LTC3588-1 Nanopower Harvester & Buck
│   │   ├── piezo_disc.md               # 35mm Piezoelectric Disc
│   │   ├── powerbank_module.md         # DIY PowerBank 5V 2A Boost & 2.4A Charger
│   │   └── tp4056.md                   # TP4056 USB-C Charger (Dual Protection)
│   └── wiring/                         # แผนผังการต่อสายไฟของแต่ละ Stage
│       └── stage_wiring_guide.md
│
├── experiments/                        # ตารางและเทมเพลตบันทึกผลการทดลองจริง
│   ├── stage1_piezo_characterization.md# บันทึกผล Stage 1 (Piezo 4 ตัว + Rectifier + 470µF 16V)
│   └── stage2_series_vs_parallel.md    # บันทึกผล Stage 2 (Series vs Parallel)
│
├── doc/                                # เอกสารและ Roadmap ความปลอดภัย
│   ├── step-charge-ai-context.md       # Master AI Knowledge Base & Context
│   └── safety-guidelines.md            # กฎความปลอดภัย Li-ion & Voltage Protection
│
└── image/                              # รูปภาพประกอบและรูปภาพวงจรจริง
    ├── battery_18650/                  # รูปแบตเตอรี่ GLINK และรางถ่าน 1S2P
    ├── ltc3588_harvester/              # รูปบอร์ด CJMCU LTC3588-1, Pinout และวงจร
    ├── powerbank_module/               # รูปโมดูล PowerBank 5V 2A, Wiring, และกราฟประสิทธิภาพ
    ├── system_diagrams/                # แผนผังระบบรวมและภาพถ่าย Breadboard วงจรจริง
    └── tp4056_charger/                 # รูปโมดูล TP4056 Type-C และ Pinout
```

---

## 🛠️ รายการอุปกรณ์และฮาร์ดแวร์ (Hardware Inventory)

| หมวดหมู่ | อุปกรณ์ | จำนวน | รายละเอียด / สเปกจริง |
|---|---|:---:|---|
| **Power Generation** | [35mm Piezo Disc](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/piezo_disc.md) | 10 ตัว | แผ่นทองเหลือง 35mm เคลือบ PZT Ceramic |
| | 1N4007 Diode | 20 ตัว | 1A 1000V ไดโอดสำหรับ Full-Bridge Rectifier |
| | [470µF Capacitor](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/capacitor.md) | 2 ตัว | **16V** Electrolytic Capacitor (Buffer) |
| **Storage & Management**| [GLINK 18650](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/battery_18650.md) | 2 ก้อน | **3.7V 2600mAh (Flat Top)** รวม 5200mAh |
| | [1S2P Battery Holder](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/battery_18650.md) | 1 อัน | รางถ่านแบบขนาน 2 ช่อง — **สายไฟถูกต้องแล้ว (แดง=+ / ดำ=-)** *(แก้ไขการบัดกรีสายสลับขั้วจากโรงงานเรียบร้อย 2026-08-22)* |
| | [CJMCU LTC3588-1](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/ltc3588.md) | 1 บอร์ด | Harvester & Buck (1.8V, 2.5V, 3.3V, 3.6V) |
| | [TP4056 Type-C](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/tp4056.md) | 1 บอร์ด | ชาร์จ CC/CV 1A พร้อม DW01A + 8205A |
| | [DIY PowerBank Module](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/powerbank_module.md) | 1 บอร์ด | ชาร์จ 2.4A / บูสต์ไฟออก 5V 2A (Efficiency >95%) |
| **Logic & Indicators** | Arduino UNO R3 | 2 บอร์ด | บอร์ดประมวลผลหลักและสำรอง |
| | LED หลากสี | 20 ตัว | ไฟแสดงสถานะ |
| | ตัวต้านทาน 200Ω | - | จำกัดกระแส LED |
| **Tools & Accessories** | Breadboard ขนาดกลาง | 2 อัน | สำหรับต่อวงจรทดลอง |
| | Jumper Wire / Hookup Wire 22AWG | - | สายไฟทดลอง (แดง/ดำ) |
| | Digital Multimeter | 1 เครื่อง | เครื่องมือวัด V, I, R |
| | อุปกรณ์และตะกั่วบัดกรี | 1 ชุด | |

---

## 🚀 ลำดับขั้นตอนการพัฒนาและการทดลอง (Development Stages)

> **อัปเดตล่าสุด: 2026-08-25**

### ✅ เสร็จสิ้นแล้ว (Completed)

- [x] **Stage 1 — Piezo Characterization:**
  - ต่อวงจร Piezo 4 ตัว (Parallel) + Full-Bridge Rectifier (1N4007 × 4) + 470µF Buffer Capacitor บน Breadboard เสร็จสมบูรณ์
  - ทดสอบกดด้วยมือ: Piezo 1 ตัว ≈ 1V / Piezo 4 ตัวรวม ≈ 4V (Parallel)
  - LED ติดสว่างได้ยืนยันว่าวงจรทำงานได้
  - ทดสอบ Series vs Parallel เบื้องต้น (ต่อ Piezo 4 ตัว Series สังเกตพฤติกรรมแล้ว)

- [x] **Stage 3 — LTC3588 Harvesting:**
  - ได้รับบอร์ด CJMCU LTC3588-1 และทดสอบเรียบร้อย (2026-08-24)
  - ต่อ Piezo → PZ1/PZ2 → LTC3588 → VCC ออก **3.3V** ยืนยันด้วยมิเตอร์แล้ว
  - ไฟกระพริบแบบ UVLO Burst Mode = พฤติกรรมปกติของชิป ✅
  - ต่อ LED สีน้ำเงินที่ขา VCC ยืนยันการทำงานด้วยตาเปล่าได้

- [x] **Stage 4 — Battery Baseline Test:**
  - ชาร์จ GLINK 18650 ผ่าน PowerBank Module Type-C จากไฟบ้าน USB 5V สำเร็จ
  - **การต่อสายรางถ่าน (แก้ไขครั้งสุดท้าย 2026-08-25 — ถูกต้องสมบูรณ์แล้ว):**
    - สายสีแดง = ขั้วบวก (+) → ต่อเข้า `BAT+` บนบอร์ด PowerBank ✅
    - สายสีดำ = ขั้วลบ (-) → ต่อเข้า `BAT-` บนบอร์ด PowerBank ✅
  - *(ปัญหาสลับขั้วจากโรงงานได้รับการแก้ไขโดยบัดกรีใหม่ถูกต้องแล้ว)*

- [x] **Stage 6 — Battery to 5V Output:**
  - ใส่ถ่าน 18650 ลงรางถ่านที่ต่อกับ PowerBank Module
  - PowerBank Module จ่ายไฟ 5V ออกทาง USB-A ได้สำเร็จ
  - ทดสอบการชาร์จมือถือและ Load ผ่าน USB-A แล้ว ✅

- [x] **Stage 7 — Arduino & LED Verification:**
  - ต่อสาย USB จาก PowerBank Module เข้า Arduino UNO ได้สำเร็จ
  - อัปโหลดโค้ด `step_voltage_logger.ino` แสดงแรงดัน Piezo ผ่าน Serial Monitor ได้จริง
  - Arduino ทำงานจากพลังงานแบตเตอรี่ 18650 โดยไม่ต้องเสียบ USB คอมพิวเตอร์ ✅

### 🔄 กำลังดำเนินการ / รอดำเนินการ (In Progress / Pending)

- [ ] **Stage 2 — Series vs Parallel Comparison (บันทึกผลตัวเลขจริง):**
  - ทดสอบต่อ Piezo 4 ตัว แบบ Series และ Parallel วัด $V_{peak}$, $V_{cap}$ และบันทึกผลใน [stage2_series_vs_parallel.md](file:///d:/Github-project/piezoelectric-energy-harvesting/experiments/stage2_series_vs_parallel.md)

- [ ] **Stage 1 ต่อ — บันทึกผลตัวเลขจริงใน Experiment Log:**
  - กรอกผลการวัด $V_{peak}$, $V_{cap}$, และเวลาคายประจุจริงลงใน [stage1_piezo_characterization.md](file:///d:/Github-project/piezoelectric-energy-harvesting/experiments/stage1_piezo_characterization.md)

- [ ] **Stage 5 — Full System Integration (รอซื้อ Boost Converter):**
  - ปัญหา: LTC3588 ปล่อย 3.3V แต่ TP4056 ต้องการ 4.5V–5.5V จึงไม่สามารถชาร์จแบตจาก Piezo โดยตรงได้
  - **แผน:** ซื้อ **MT3608 Boost Module** (~15-25 บาท) มาต่อระหว่าง LTC3588 กับ TP4056
  - เส้นทางสมบูรณ์เมื่อได้ Boost:
    ```
    [ Piezo ] → [ LTC3588 (3.3V) ] → [ MT3608 Boost (5V) ] → [ TP4056 ] → [ 18650 ]
                                                                                 ↓
                                                                     [ PowerBank Module ]
                                                                                 ↓
                                                                        5V → Arduino / มือถือ
    ```

### 🔭 Future Scope

- [ ] **Distance Sensor:** เพิ่ม HC-SR04 รันโค้ด `future_distance_trigger.ino`
- [ ] **Stage 1 Bonus — ทดสอบ Capacitor 2 ตัวขนาน (940µF):** เปรียบเทียบ $V_{cap}$ และอัตราการคายประจุ

---

## 💻 วิธีการเปิดโค้ดใน Arduino IDE

1. ติดตั้ง **Arduino IDE** (เวอร์ชัน 2.x หรือ 1.8.x)
2. เปิดโฟลเดอร์ Firmware ที่ต้องการทดสอบ:
   - โค้ดวัดแรงดันและนับก้าว: [step_voltage_logger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/step_voltage_logger/step_voltage_logger.ino)
   - โค้ดทดสอบสถานะไฟ 5V: [power_indicator_test.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/power_indicator_test/power_indicator_test.ino)
   - โค้ดเซนเซอร์ระยะทาง: [future_distance_trigger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/future_distance_trigger/future_distance_trigger.ino)
3. เลือกบอร์ดเป็น **Arduino Uno** และเลือก COM Port
4. กด **Upload (➔)** และเปิด **Serial Plotter** ที่ Baud rate `115200`

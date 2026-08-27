# ⚡ StepCharge: Footstep Piezoelectric Energy Harvesting System

> 🎉 **สถานะโครงการ: เสร็จสิ้นและผ่านการทดสอบครบวงจร 100% (Project Completed & Verified)**  
> **วันที่บันทึกผลสำเร็จ:** 2026-08-27  
> **ผู้พัฒนา/ทดลอง:** Thanakhon Oonklan

ระบบต้นแบบเก็บเกี่ยวพลังงานจากการเหยียบ (Footstep Piezoelectric Energy Harvesting Prototype) เปลี่ยนแรงกดเชิงกลจากการก้าวเดินเป็นพลังงานไฟฟ้า จัดการและกักเก็บพลังงานลงในแบตเตอรี่ 18650 Li-ion และจ่ายไฟออก 5V เพื่อนำกลับมาใช้งานกับ Arduino UNO, LED และชาร์จโทรศัพท์มือถือได้อย่างสมบูรณ์แบบโดยไม่ต้องพึ่งพาไฟจากคอมพิวเตอร์ (Standalone Operation)

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
│   ├── modules/                        # สเปกอุปกรณ์แต่ละตัว (จากฮาร์ดแวร์จริงที่ใช้ในระบบ)
│   │   ├── battery_18650.md            # GLINK 18650 2600mAh & 1S2P Holder
│   │   ├── capacitor.md                # 470µF 16V Electrolytic Buffer Capacitor
│   │   ├── ltc3588.md                  # CJMCU LTC3588-1 Nanopower Harvester & Buck
│   │   ├── mt3608_boost.md             # MT3608 DC-DC 2A Step-Up Converter (จูนไว้ที่ 5.20V)
│   │   ├── piezo_disc.md               # 35mm Piezoelectric Disc
│   │   ├── powerbank_module.md         # DIY PowerBank 5V 2A Boost & 2.4A Charger
│   │   └── tp4056.md                   # TP4056 USB-C Charger (Dual Protection)
│   └── wiring/                         # แผนผังการต่อสายไฟของแต่ละ Stage
│       └── stage_wiring_guide.md
│
├── experiments/                        # ตารางและผลบันทึกการทดลองจริง
│   ├── stage1_piezo_characterization.md# บันทึกผล Stage 1 (Piezo + Rectifier + 470µF)
│   ├── stage2_series_vs_parallel.md    # บันทึกผล Stage 2 (Series vs Parallel vs Hybrid)
│   └── stage5_full_system_integration.md# บันทึกผล Stage 5 (ทดสอบครบวงจร Standalone ~4.0V)
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

## 🛠️ รายการอุปกรณ์และฮาร์ดแวร์ที่ใช้จริง (Hardware Inventory)

| หมวดหมู่ | อุปกรณ์ | จำนวน | รายละเอียด / สเปกจริง |
|---|---|:---:|---|
| **Power Generation** | [35mm Piezo Disc](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/piezo_disc.md) | 4-10 ตัว | แผ่นทองเหลือง 35mm เคลือบ PZT Ceramic ผลิตไฟพัลส์จากการเหยียบ |
| | 1N4007 Diode | 4 ตัว | ไดโอดสำหรับ Full-Bridge Rectifier แปลง AC เป็น DC |
| | [470µF Capacitor](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/capacitor.md) | 1-2 ตัว | **16V** Electrolytic Capacitor ทำหน้าที่เป็น Buffer Storage |
| **Harvester & Regulators**| [CJMCU LTC3588-1](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/ltc3588.md) | 1 บอร์ด | Nanopower Energy Harvester ตั้งค่า Buck VOUT = **3.3V** |
| | [MT3608 Boost Module](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/mt3608_boost.md) | 1 บอร์ด | Step-Up Converter ปรับตั้งค่าไฟออกไว้ที่ **5.20V DC** |
| **Storage & Charging** | [TP4056 Type-C](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/tp4056.md) | 1 บอร์ด | โมดูลชาร์จแบตเตอรี่ Li-ion CC/CV พร้อม DW01A Protection |
| | [GLINK 18650](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/battery_18650.md) | 2 ก้อน | **3.7V 2600mAh (Flat Top)** รวมความจุ 5200mAh |
| | [1S2P Battery Holder](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/battery_18650.md) | 1 อัน | รางถ่านแบบขนาน 2 ช่อง — สายไฟถูกต้องแล้ว (แดง=+ / ดำ=-) |
| **Output Stage** | [DIY PowerBank Module](file:///d:/Github-project/piezoelectric-energy-harvesting/hardware/modules/powerbank_module.md) | 1 บอร์ด | บูสต์ไฟออก 5V 2A ผ่านพอร์ต USB-A เลี้ยงโหลดภายนอก |
| **Controller & Display** | Arduino UNO R3 | 2 บอร์ด | ประมวลผล อ่านค่าระดับพลังงาน และตรวจจับการก้าวเดิน |
| | Mini Digital Voltmeter | 1 ตัว | จอดิจิทัล LED แสดงระดับแรงดันแบตเตอรี่ |
| **Tools & Accessories** | Multimeter SPA YX-961TR | 1 เครื่อง | เครื่องมือวัดหลักในการจูนแรงดันและตรวจสอบระบบ |
| | Breadboard + Jumper Wires | 2 อัน | สำหรับประกอบและทดสอบวงจร |

---

## 🚀 สรุปผลการพัฒนาและการทดลองทุกขั้นตอน (Development Stages Summary)

```text
================================================================================================
  [ Piezo Array ] ──► [ LTC3588 ] ──► [ MT3608 Boost ] ──► [ TP4056 ] ──► [ แบตเตอรี่ 18650 ]
   (เหยียบกด)         (3.3V Burst)        (5.20V DC)         (CC/CV)          (~4.0V ชาร์จจริง)
                                                                                     │
                                                                                     ▼
                                      [ Arduino UNO / โหลด 5V ] ◄── [ PowerBank Module ]
                                      (รันโค้ดวัดระดับพลังงาน)        (บูสต์ไฟออก 5.0V นิ่ง)
================================================================================================
```

### ✅ สำเร็จสมบูรณ์ทุกขั้นตอน (All Stages Completed 100%)

- [x] **Stage 1 — Piezo Characterization:**
  - ต่อ Piezo 4 ตัว (Parallel) + Full-Bridge Rectifier (1N4007) + 470µF 16V Buffer Capacitor
  - ทดสอบกดด้วยมือ: Piezo 1 ตัว ≈ 1V / Piezo 4 ตัวรวม ≈ 4V ยืนยันหลอด LED ติดสว่างได้จริง
- [x] **Stage 2 — Configuration Analysis (Series vs Parallel):**
  - เปรียบเทียบการต่อ: Series ให้แรงดันสูง (~4V–8V+) เหมาะกับการกระตุ้น LTC3588, Parallel ให้กระแสสูง
  - ทดสอบการต่อแบบ Hybrid (2S2P) กระจายแรงกดสม่ำเสมอ
- [x] **Stage 3 — LTC3588 Nanopower Harvesting:**
  - ติดตั้งบอร์ด CJMCU LTC3588-1 รับสัญญาณ Piezo เข้าขา PZ1/PZ2
  - ตั้งค่า $V_{OUT} = 3.3\text{V}$ (D1=HIGH, D0=LOW) และตรวจพบการทำงานแบบ UVLO Burst Mode (สะสมถึง 4.6V - 5.0V แล้วปล่อยไฟออก 3.3V)
  - เขียนโค้ด `ltc3588_energy_monitor.ino` มอนิเตอร์ระดับพลังงานสะสม (mJ, %) และนับรอบ Burst ได้แบบ Real-time
- [x] **Stage 4 — Battery Baseline & Charger Test:**
  - แก้ไขการต่อสายรางถ่าน 1S2P ให้ถูกต้องตามขั้ว (แดง=+ / ดำ=-)
  - ทดสอบการชาร์จถ่าน 18650 ผ่านโมดูลชาร์จอย่างปลอดภัย
- [x] **Stage 5 — Full Standalone System Integration (ระบบปิดครบวงจร):**
  - ติดตั้งโมดูล **MT3608 Boost Converter** เชื่อมระหว่าง LTC3588 (3.3V) และ TP4056 (5.20V)
  - ทำการ Calibration ปรับจูน Trimpot จาก 18.0V ลงมาอยู่ที่ **5.20V DC** พอดี
  - **ผลสำเร็จ:** เมื่อเหยียบ Piezo พลังงานถูกส่งผ่าน LTC3588 -> MT3608 -> TP4056 และสามารถชาร์จถ่าน 18650 ที่แรงดันประมาณ **~4.00V** ได้จริง
- [x] **Stage 6 — Battery to 5V Output:**
  - ถ่าน 18650 จ่ายไฟเข้า PowerBank Module และบูสต์ไฟออกทางพอร์ต USB-A ได้ 5.0V 2A เสถียร
  - ทดสอบชาร์จโทรศัพท์มือถือและจ่ายไฟให้อุปกรณ์ภายนอกสำเร็จ
- [x] **Stage 7 — Arduino Verification & Energy Monitoring:**
  - ใช้ไฟ 5V จาก PowerBank เลี้ยง Arduino UNO R3 ทำงานแบบ Standalone ไม่ต้องเสียบสายคอมพิวเตอร์
  - รันโค้ดอ่านค่าแรงดันและนับก้าวได้อย่างแม่นยำ

---

## 💻 วิธีการเปิดโค้ดใน Arduino IDE

1. ติดตั้ง **Arduino IDE** (เวอร์ชัน 2.x หรือ 1.8.x)
2. เปิดโฟลเดอร์ Firmware ที่ต้องการ:
   - โค้ดวัดระดับพลังงานสะสมและนับรอบปล่อยไฟ: [ltc3588_energy_monitor.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/ltc3588_energy_monitor/ltc3588_energy_monitor.ino)
   - โค้ดวัดแรงดันและนับก้าว: [step_voltage_logger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/step_voltage_logger/step_voltage_logger.ino)
   - โค้ดทดสอบสถานะไฟ 5V: [power_indicator_test.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/power_indicator_test/power_indicator_test.ino)
   - โค้ดเซนเซอร์ระยะทาง: [future_distance_trigger.ino](file:///d:/Github-project/piezoelectric-energy-harvesting/firmware/future_distance_trigger/future_distance_trigger.ino)
3. เลือกบอร์ดเป็น **Arduino Uno** และเลือก COM Port ให้ตรง
4. ตั้งค่า Serial Monitor Baud rate ให้ตรงกับโค้ด (**115200** สำหรับ LTC3588 Monitor และ **9600** สำหรับ Step Logger)

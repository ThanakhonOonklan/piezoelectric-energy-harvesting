# Stage-by-Stage Wiring Guide (คู่มือการต่อวงจรทีละสเต็ป)

เอกสารนี้รวบรวมแผนผังการต่อวงจร (Wiring Diagram) ตั้งแต่ **Stage 1 ถึง Stage 7** เพื่อให้สามารถทดลองและตรวจสอบระบบได้อย่างปลอดภัย เป็นลำดับขั้นตอน

---

## 🌟 ภาพรวมระบบ Energy Harvesting จาก Piezo

![Piezo Energy Harvesting Overview](/d:/Github-project/piezoelectric-energy-harvesting/image/system_diagrams/piezo_energy_harvesting_system_overview.png)

---

## 📸 ภาพตัวอย่างการต่อวงจรต้นแบบบน Breadboard

![Breadboard Prototype Wiring](/d:/Github-project/piezoelectric-energy-harvesting/image/system_diagrams/prototype_breadboard_wiring.jpg)

---

## Stage 1 — Piezo Characterization (วัดคุณลักษณะ Piezo 4 ตัว)

**เป้าหมาย:** วัดสัญญาณ AC/Pulse ที่ผ่าน Bridge Rectifier และประจุลง Capacitor $470\mu\text{F}$ 16V

```text
  [Piezo 1..4 Array]
   (+)          (-)
    │            │
    ▼            ▼
 ┌──────────────────┐
 │  1N4007 Bridge   │
 │   Rectifier      │
 └────────┬─────────┘
          │ (+)        (-)
          ├─────────────┐
          ▼             ▼
     [ +  470µF 16V  - ]
          │             │
          ▼             ▼
     [ Multimeter / Oscilloscope / Safe Voltage Divider to Arduino ]
```

---

## Stage 2 — Piezo Configuration Comparison (เปรียบเทียบ Series vs Parallel)

### การต่อ 4-Piezo Series (อนุกรม)
```text
  Piezo 1(+) ─── Piezo 1(-)
                   │
  Piezo 2(+) ──────┘
  Piezo 2(-)
    │
  Piezo 3(+) ─── Piezo 3(-)
                   │
  Piezo 4(+) ──────┘
  Piezo 4(-) ──> Rectifier Input AC2
  Piezo 1(+) ──> Rectifier Input AC1
```

### การต่อ 4-Piezo Parallel (ขนาน)
```text
  Piezo 1(+) ──┬── Piezo 2(+) ──┬── Piezo 3(+) ──┬── Piezo 4(+) ──> AC1
               │                │                │
  Piezo 1(-) ──┴── Piezo 2(-) ──┴── Piezo 3(-) ──┴── Piezo 4(-) ──> AC2
```

---

## Stage 3 — LTC3588 Harvester Experiment

**เป้าหมาย:** ให้ LTC3588 รับสัญญาณ Piezo แล้วแปลงเป็นแรงดัน Buck คงที่

```text
  Piezo Array ──> [ PZ1 , PZ2 ] (LTC3588 Input)
                         │
                  [ LTC3588 Board ]
                  ├── D0, D1 : Jumper เลือก VOUT (เช่น 3.3V)
                  ├── CAP    : Storage Cap ภายใน
                  └── VIN    : 470µF 16V Buffer Cap
                         │
                  [ VCC/VOUT , GND ]
                         │
                         ▼
                  [ Multimeter / Load Test ]
```

---

## Stage 4 — Battery Baseline Test (TP4056 + GLINK 18650)

**เป้าหมาย:** ทดสอบชาร์จ 18650 ด้วยไฟ USB 5V ปกติเพื่อยืนยันสภาพแบตเตอรี่

```text
  5V USB-C Charger
         │
         ▼
  [ TP4056 Module ]
     B+ ──────────> (+) 18650 Battery (1S2P Holder สายแดง)
     B- ──────────> (-) 18650 Battery (1S2P Holder สายดำ)
```

---

## Stage 6 & 7 — Battery to 5V & Arduino Indicator Test

**เป้าหมาย:** นำไฟจาก 18650 ผ่าน PowerBank Module แปลงเป็น 5V เลี้ยง Arduino UNO และ LED

```text
  18650 1S2P Battery
         │
         ▼
  [ BAT+ , BAT- ]
  [ DIY PowerBank Module ]
         │
      5V USB Output / + 5V - Pads
         │
         ├─────────────────────────────────────────┐
         ▼                                         ▼
  Arduino UNO USB Port / 5V Pin              Arduino GND
         │
      [Pin D8]
         │
      [200Ω Resistor]
         │
     [LED Anode (+)]
     [LED Cathode (-)] ────────────────────────────┘
```

---

## Stage 5 — Full Standalone System (ระบบสมบูรณ์ ไม่ต้องต่อคอม)

> **อัปเดต: 2026-08-25** | ⏳ รอซื้อ MT3608 Boost Module

**เป้าหมาย:** ระบบทำงานครบวงจรโดยไม่ต้องต่อ USB คอมพิวเตอร์ เหยียบแผ่น Piezo → ชาร์จแบต → จ่ายไฟออก Arduino / มือถือ ได้โดยอัตโนมัติ

### 🗺️ แผนผังระบบเต็ม (Full System Diagram):

```text
══════════════════════════════════════════════════════════
  BLOCK 1: ผลิตและแปลงพลังงาน (Energy Generation)
══════════════════════════════════════════════════════════

  [ Piezo Disc × 4 ต่อขนาน ]
     แดง(+) รวม → PZ1
     ดำ(-)  รวม → PZ2
                   ↓
           [ LTC3588 Board (บอร์ดแดง) ]
              D1 = HIGH , D0 = LOW  (เลือก VCC = 3.3V)
                   ↓
            VCC = 3.3V  |  GND

══════════════════════════════════════════════════════════
  BLOCK 2: บูสต์แรงดัน (MT3608 Boost — ตัวใหม่ที่ต้องซื้อ)
══════════════════════════════════════════════════════════

           LTC3588 VCC (3.3V) → MT3608 IN+
           LTC3588 GND        → MT3608 IN-
                   ↓
           [ MT3608 Boost Module ]
             ปรับ Trimpot จนได้ OUT = 5.0V
                   ↓
           MT3608 OUT+ (5V)  |  OUT- (GND)

══════════════════════════════════════════════════════════
  BLOCK 3: ชาร์จแบตเตอรี่ (TP4056 Charger)
══════════════════════════════════════════════════════════

           MT3608 OUT+ (5V) → TP4056 IN+
           MT3608 OUT- (GND)→ TP4056 IN-
                   ↓
           [ TP4056 Module ]
             LED แดง = กำลังชาร์จ
             LED น้ำเงิน = ชาร์จเต็ม
                   ↓
           B+ → สายแดง รางถ่าน (+)
           B- → สายดำ  รางถ่าน (-)

══════════════════════════════════════════════════════════
  BLOCK 4: เก็บพลังงาน (18650 Battery Storage)
══════════════════════════════════════════════════════════

           [ GLINK 18650 × 2 ก้อน ในรางถ่าน 1S2P ]
             สายแดง = BAT+ → PowerBank BAT+
             สายดำ  = BAT- → PowerBank BAT-

══════════════════════════════════════════════════════════
  BLOCK 5: จ่ายไฟออก (PowerBank Module → 5V Output)
══════════════════════════════════════════════════════════

           [ DIY PowerBank Module ]
             กด K 1 ครั้ง → เปิดจ่ายไฟ 5V
                   ↓ USB-A (5V, 2A)
           ┌───────┴───────┐
           ▼               ▼
    [ Arduino UNO ]   [ มือถือ / โหลดภายนอก ]
     รันโค้ด          ชาร์จได้ปกติ
     step_voltage_logger.ino
     (ดูแรงดัน Piezo ผ่าน Serial Monitor)
```

---

### 📌 ตารางสรุปการต่อสายระบบเต็ม:

| จาก | ไปที่ | สีสาย |
|---|---|:---:|
| Piezo (+) รวม | LTC3588 **PZ1** | 🔴 แดง |
| Piezo (-) รวม | LTC3588 **PZ2** | ⚫ ดำ |
| LTC3588 **VCC** | MT3608 **IN+** | 🔴 แดง |
| LTC3588 **GND** | MT3608 **IN-** | ⚫ ดำ |
| MT3608 **OUT+** (5V) | TP4056 **IN+** | 🔴 แดง |
| MT3608 **OUT-** (GND) | TP4056 **IN-** | ⚫ ดำ |
| TP4056 **B+** | รางถ่าน **สายแดง (+)** | 🔴 แดง |
| TP4056 **B-** | รางถ่าน **สายดำ (-)** | ⚫ ดำ |
| รางถ่าน **สายแดง (+)** | PowerBank **BAT+** | 🔴 แดง |
| รางถ่าน **สายดำ (-)** | PowerBank **BAT-** | ⚫ ดำ |
| PowerBank **USB-A** | Arduino UNO / มือถือ | 🔵 USB |

---

### ⚠️ ข้อควรระวัง:
- ปรับ MT3608 ให้ได้ **5.0V พอดี** ก่อนต่อเข้า TP4056 ทุกครั้ง
- TP4056 และ PowerBank Module ต่อกับแบตพร้อมกันได้ (ชาร์จเข้า-จ่ายออกพร้อมกันได้)
- **อย่าต่อ LTC3588 VCC เข้า TP4056 โดยตรง** (3.3V ต่ำกว่า 4.5V ที่ TP4056 ต้องการ)

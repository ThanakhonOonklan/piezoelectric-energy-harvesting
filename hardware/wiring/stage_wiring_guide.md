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

# piezoelectric-energy-harvesting — AI Project Context / Technical Handoff

> ไฟล์นี้จัดทำขึ้นเพื่อใช้เป็น **Project Context / Knowledge Base สำหรับให้ AI ตัวอื่นเรียนรู้โปรเจกต์ StepCharge** ก่อนช่วยวิเคราะห์ ออกแบบวงจร เขียนโค้ด ทำ Wiring Diagram หรือช่วยวางแผนการทดลอง
>
> AI ที่นำไฟล์นี้ไปใช้ควรอ่าน **ทั้งไฟล์ก่อนเสนอวิธีต่อวงจร** และควรแยกให้ชัดเจนระหว่าง “สิ่งที่ยืนยันแล้วจาก Hardware จริง” กับ “สิ่งที่ยังเป็นสมมติฐาน/ต้องทดลอง”

---

# 1. Project Identity

## Project Name

**piezoelectric-energy-harvesting**

ชื่อ Repository บน GitHub:

```text
piezoelectric-energy-harvesting
```

## Project Type

**Footstep Piezoelectric Energy Harvesting System**

เป็นต้นแบบระบบที่นำแรงกดจากการเหยียบมาเปลี่ยนเป็นพลังงานไฟฟ้า จากนั้นจัดการพลังงาน เก็บไว้ในแบตเตอรี่ และนำไฟที่เก็บไว้กลับมาใช้กับ Arduino / LED / USB output

## Core Concept

```text
Footstep
   ↓
Mechanical Pressure
   ↓
Piezoelectric Disc
   ↓
Electrical Pulse
   ↓
Rectification / Power Conditioning
   ↓
Energy Storage
   ↓
18650 Li-ion Battery
   ↓
5V Power Output
   ↓
Arduino / LED / USB Load
```

---

# 2. Main Goal

เป้าหมายของ Prototype คือพิสูจน์ว่า:

1. การเหยียบสามารถสร้างพลังงานไฟฟ้าจาก Piezoelectric Disc ได้จริง
2. พลังงานที่ได้สามารถถูก Rectify และเก็บไว้ใน Capacitor ได้
3. สามารถนำพลังงานเข้าสู่ระบบ Energy Harvesting / Power Management ได้อย่างเหมาะสม
4. สามารถเก็บพลังงานไว้ใน 18650 Li-ion ได้โดยใช้วงจรชาร์จที่ถูกต้อง
5. Battery สามารถจ่ายไฟผ่าน PowerBank / Boost Module ออกมาเป็น 5V ได้
6. 5V ที่ได้สามารถนำไปเลี้ยง Arduino และอุปกรณ์ภายนอกได้
7. ในระยะถัดไปสามารถนำ HC-SR04 มาใช้วัดระยะและควบคุม LED ได้

---

# 3. Current Scope

## Scope ตอนนี้

โฟกัสหลักอยู่ที่ **Energy Harvesting และ Battery System**

ยังไม่ใช่การทำระบบ IoT และยังไม่เน้นการส่งข้อมูล Wi-Fi

ระบบควบคุมใน Prototype เบื้องต้นมีเพียง:

```text
Battery / 5V
   ↓
Arduino UNO
   ↓
LED
```

## Future Scope

ภายหลังสามารถเพิ่ม:

```text
Arduino UNO
   ↓
HC-SR04
   ↓
Distance
   ↓
Threshold
   ↓
LED ON / OFF
```

และถ้าต้องการขยายระบบในอนาคตจึงค่อยเพิ่ม:

```text
Arduino / ESP32
   ↓
Wi-Fi
   ↓
Dashboard / Data Logging
```

แต่สิ่งเหล่านี้ **ไม่ใช่แกนหลักของ Prototype ปัจจุบัน**

---

# 4. Important Project Understanding

## สิ่งสำคัญที่สุดเกี่ยวกับ Piezo

Piezoelectric Disc ไม่ใช่ Power Supply 5V แบบ USB

เมื่อถูกกด Piezo จะสร้างแรงดันไฟฟ้าที่มีลักษณะเป็น:

- Pulse
- Transient
- เปลี่ยนแปลงตามแรงกด
- มี Peak Voltage สูงได้
- กระแสที่สามารถจ่ายได้มักต่ำ
- พลังงานรวมไม่ได้เท่ากับดูจาก Voltage อย่างเดียว

ดังนั้น:

```text
5V Peak
```

ไม่ได้แปลว่า:

```text
5V × 1A = 5W
```

ต้องรู้ทั้ง:

```text
Voltage
Current
Power
Energy
```

โดย:

```text
Power = Voltage × Current
```

---

# 5. Existing Hardware

## Power Generation

### Piezoelectric Disc
- จำนวน: **10 ตัว**
- ขนาด: ประมาณ **35 mm**
- หน้าที่: เปลี่ยนแรงกดเป็นพลังงานไฟฟ้า
- เริ่มต้นการทดลองควรใช้ **4 ตัวก่อน**
- สามารถขยายเป็น 6 / 8 / 10 ตัวภายหลัง
- ต้องทดลองทั้งการต่อ Series และ Parallel ก่อนตัดสินใจใช้ Final

### 1N4007
- จำนวน: **20 ตัว**
- ใช้ทำ Bridge Rectifier
- Bridge Rectifier 1 ชุดใช้ 4 ตัว

### 470µF Capacitor
- จำนวน: **2 ตัว**
- ใช้เป็น Energy Buffer / Smoothing Capacitor
- ค่าแรงดันของตัวที่ใช้งานต้องตรวจสอบจากตัวจริงก่อนต่อ

### Hookup Wire
- 22 AWG
- สีแดง / ดำ
- ใช้สำหรับสาย Power และการต่อส่วนที่เป็นพลังงาน

---

# 6. Battery Hardware

## 18650 Li-ion Battery

- จำนวน: **2 ก้อน**
- ชนิด: Li-ion
- Nominal Voltage: ประมาณ 3.7V
- หัว: Flat Top
- ปัจจุบันตั้งใจใช้เป็น **1S2P** ผ่าน Holder แบบขนาน

## Battery Holder

- จำนวน: **1**
- รองรับ 18650 จำนวน 2 ก้อน
- ต่อแบบขนาน

Concept:

```text
Cell 1 + ─┐
          ├── BAT+
Cell 2 + ─┘

Cell 1 - ─┐
          ├── BAT-
Cell 2 - ─┘
```

เมื่อเป็น 1S2P:

- Voltage ยังอยู่ประมาณระดับ 3.7V nominal
- Capacity จะเพิ่มตามความจุของ cell ที่ขนานกัน

### Battery Safety Constraint

ก่อนต่อแบตเตอรี่ขนาน:

- ควรเป็นแบตเตอรี่ชนิดเดียวกัน
- รุ่น/ความจุใกล้เคียงกัน
- แรงดันเริ่มต้นใกล้กัน
- ไม่มี cell ที่บวม บุบ หรือฉนวนเสียหาย

---

# 7. Power Management / Charging Modules

ใน Project นี้มีหลาย module และต้องแยกหน้าที่ให้ชัดเจน

## 7.1 LTC3588 Energy Harvester

มีอยู่:

```text
LTC3588 Energy Harvester Module ×1
```

### หน้าที่

ใช้สำหรับศึกษา/ทดลอง:

```text
Piezo
   ↓
Energy Harvesting
   ↓
Energy Storage / Regulated Output
```

LTC3588-1 ถูกออกแบบมาสำหรับ energy harvesting จากแหล่งพลังงานลักษณะ impedance สูง เช่น Piezo และมี rectifier อยู่ใน IC ตาม architecture ของชิป

### IMPORTANT

อย่าถือว่า:

```text
LTC3588 → 18650
```

เป็น Li-ion CC/CV charger โดยอัตโนมัติ

ต้องตรวจสอบ **module ที่ซื้อจริง** และดู:

- VIN
- VOUT
- Storage capacitor
- PGOOD
- การตั้งค่า output
- วิธีรองรับ battery

---

## 7.2 TP4056 USB-C

มีอยู่:

```text
TP4056 Type-C ×1
```

### หน้าที่

ชาร์จ Li-ion 1 cell จากไฟ 5V:

```text
USB-C 5V
   ↓
TP4056
   ↓
1S Li-ion Battery
```

TP4056 เป็น Battery Charger ไม่ใช่ Piezo Energy Harvester

ดังนั้นไม่ควรคิดว่า:

```text
Piezo → TP4056 → Battery
```

จะเหมาะสมโดยอัตโนมัติ

---

## 7.3 DIY PowerBank Module

มีอยู่:

```text
DIY PowerBank Module
5V 2A
Type-C
1S 3.7V
```

### หน้าที่หลัก

ขึ้นกับรุ่นจริง แต่ตั้งใจใช้เพื่อ:

```text
18650 Battery
   ↓
PowerBank Module
   ├── Charge/Input
   └── Boost
        ↓
      5V USB Output
```

ใช้เป็นส่วนของระบบ Battery → 5V Output

### ต้องตรวจสอบจากบอร์ดจริงก่อนใช้งาน

- USB-C เป็น Input หรือ Input/Output
- รองรับ 1S2P หรือไม่
- มี Battery Protection หรือไม่
- Output 5V 2A เป็นเงื่อนไขใด
- มี Charging Circuit ในตัวหรือไม่
- มี Low Voltage Cutoff หรือไม่

### สำคัญ

ห้ามสมมติว่า:

```text
TP4056 + PowerBank Module
```

สามารถต่อขนานกันเพื่อชาร์จ Battery พร้อมกันโดยไม่มีการออกแบบ power-path

ในการทดลองให้เลือกเส้นทางชาร์จอย่างชัดเจน

---

# 8. Arduino Hardware

## Arduino UNO R3

มี:

```text
Arduino UNO R3 ×2
```

ใช้หนึ่งตัวเป็นตัวหลัก และอีกหนึ่งตัวเป็นสำรอง / ใช้ทดสอบในอนาคต

### Current Prototype

ยังไม่ต้องใช้ UNO สองตัวสื่อสารกัน

ระบบปัจจุบันใช้ UNO ตัวเดียวได้:

```text
5V
 ↓
Arduino UNO
 ↓
LED
```

## LED

- มีประมาณ 20 ตัว
- ใช้แสดงสถานะระบบ

## Resistor

มี:

```text
200Ω
```

ใช้จำกัดกระแส LED เช่น:

```text
Arduino D8
 ↓
200Ω
 ↓
LED
 ↓
GND
```

ถ้าจำเป็นต้องใช้หลายค่าความต้านทาน ควรมี resistor kit เพิ่ม แต่ไม่จำเป็นต่อการเริ่มต้น LED circuit

---

# 9. Other Hardware

- Breadboard ขนาดกลาง ×2
- Jumper Wire Male-to-Male 10cm
- Jumper Wire Male-to-Female มีอยู่บางส่วน
- Multimeter
- อุปกรณ์บัดกรี
- ตะกั่วบัดกรี

---

# 10. Current Architecture

สถาปัตยกรรมที่ต้องการศึกษาคือ:

```text
                    FOOTSTEP
                       │
                       ▼
                ┌─────────────┐
                │ Piezo ×4+   │
                └─────────────┘
                       │
                       ▼
                ┌─────────────┐
                │ Rectifier   │
                │ 1N4007 ×4   │
                └─────────────┘
                       │
                       ▼
                ┌─────────────┐
                │ 470µF       │
                │ Capacitor   │
                └─────────────┘
                       │
                       ▼
                ┌─────────────┐
                │ LTC3588     │
                │ Energy      │
                │ Harvester   │
                └─────────────┘
                       │
                       ▼
                ┌─────────────┐
                │ 18650 1S    │
                │ 2 cells     │
                │ Parallel    │
                └─────────────┘
                       │
                       ▼
                ┌─────────────┐
                │ PowerBank   │
                │ Module      │
                └─────────────┘
                       │
                    5V USB
                       │
                       ▼
                ┌─────────────┐
                │ Arduino UNO │
                └─────────────┘
                       │
                       ▼
                      LED
```

---

# 11. Correct Development Strategy

AI ที่เข้ามาช่วยโปรเจกต์นี้ควร **ไม่แนะนำให้ต่อทุกอย่างพร้อมกันในครั้งแรก**

ให้พัฒนาแบบทีละ Stage

---

## Stage 1 — Piezo Characterization

เป้าหมาย:

> รู้ว่า Piezo 4 ตัวผลิตพลังงานได้เท่าไร

Circuit:

```text
Piezo ×4
   ↓
1N4007 Bridge
   ↓
470µF
   ↓
Multimeter
```

ต้องวัดอย่างน้อย:

- Vpeak
- Voltage บน capacitor
- Voltage decay
- Current ภายใต้โหลด
- Power โดยประมาณ

---

## Stage 2 — Compare Piezo Configurations

ทดลอง:

```text
4 Piezo Series
```

เทียบกับ:

```text
4 Piezo Parallel
```

และภายหลัง:

```text
6 / 8 / 10 Piezo
```

### สิ่งที่ต้องเปรียบเทียบ

- Voltage
- Current
- Power
- Energy per footstep
- ความเสถียร

ไม่ควรตัดสิน Series/Parallel จาก Voltage เพียงอย่างเดียว

---

## Stage 3 — LTC3588 Experiment

หลังรู้พฤติกรรมของ Piezo:

```text
Piezo
 ↓
LTC3588
 ↓
Storage / Output
```

วัด:

- Input voltage
- Output voltage
- Capacitor charging
- Load behavior

ห้ามข้าม Stage นี้แล้วนำต่อ Battery ทันทีโดยไม่ตรวจ topology ของโมดูล

---

## Stage 4 — Battery Charging Test

ทดสอบ TP4056 แยก:

```text
USB-C 5V
 ↓
TP4056
 ↓
18650
```

เป้าหมาย:

- ตรวจว่า TP4056 ทำงาน
- ตรวจ Charging LED
- ตรวจ Battery voltage
- ตรวจว่าชาร์จ 1S Li-ion ได้ตามปกติ

ส่วนนี้ใช้เป็น baseline/control experiment

---

## Stage 5 — Energy Harvesting Storage

เมื่อ Stage 3 ผ่าน:

```text
Piezo
 ↓
Energy Harvester
 ↓
Storage
```

จากนั้นค่อยประเมินว่าสามารถส่งต่อเข้า Battery charging stage ที่เหมาะสมได้หรือไม่

---

## Stage 6 — Battery → 5V

```text
18650
 ↓
DIY PowerBank Module
 ↓
5V USB
```

ทดสอบกับ load ง่าย ๆ ก่อน เช่น Arduino + LED

ยังไม่ควรเริ่มด้วย Smartphone เป็น load หลัก

---

## Stage 7 — Arduino

```text
5V
 ↓
Arduino UNO
 ↓
D8
 ↓
200Ω
 ↓
LED
```

ทดสอบว่า Battery-to-5V stage สามารถเลี้ยง Arduino ได้จริง

---

# 12. Future Distance Sensor

เมื่อ Power System เสถียรแล้วค่อยเพิ่ม:

```text
Arduino UNO
   ↓
HC-SR04
   ↓
Distance
   ↓
Threshold
   ↓
LED
```

ตัวอย่าง:

```cpp
if (distance < 50) {
    digitalWrite(LED_PIN, HIGH);
} else {
    digitalWrite(LED_PIN, LOW);
}
```

ไม่มีความจำเป็นต้องเพิ่ม UNO ตัวที่ 2 ใน scope นี้

---

# 13. Data to Record During Experiment

ควรมีตารางบันทึก:

| Test | Piezo Count | Configuration | Vpeak | Vcap | Current | Power | Notes |
|---|---:|---|---:|---:|---:|---:|---|
| A | 4 | Series | | | | | |
| B | 4 | Parallel | | | | | |
| C | 6 | Series | | | | | |
| D | 8 | Series | | | | | |
| E | 10 | Series | | | | | |

และควรบันทึกจำนวนครั้งที่เหยียบ เช่น:

```text
10 steps
20 steps
50 steps
100 steps
```

เพื่อดูว่า capacitor และ storage เพิ่มพลังงานอย่างไร

---

# 14. Important Safety Constraints

นี่เป็นส่วนสำคัญที่ AI ตัวอื่นต้องอ่านก่อนแนะนำการต่อวงจร

## Battery Safety

- ห้ามต่อ Piezo เข้ากับ 18650 โดยตรง
- ห้ามใช้แบตเตอรี่ที่บวม/บุบ/ฉนวนฉีก
- ห้ามต่อ cell ที่แรงดันต่างกันมากแบบขนาน
- ห้ามชาร์จ Li-ion ด้วยวงจรที่ไม่ได้ออกแบบสำหรับ Li-ion
- อย่าชาร์จแบตเตอรี่ด้วยสอง charger พร้อมกันโดยไม่มี power-path ที่เหมาะสม
- ตรวจ polarity ก่อนทุกครั้ง

## Capacitor

- ตรวจขั้ว + / -
- ใช้ voltage rating สูงกว่าค่าที่คาด
- ไม่ควรสรุปว่า 470µF สามารถควบคุมการชาร์จ Li-ion ได้

## Piezo

- Piezo สามารถเกิด voltage spike สูงกว่าค่า peak ที่วัดได้ภายใต้เงื่อนไขหนึ่ง
- ไม่ควรต่อเข้าขา Arduino โดยตรงหากยังไม่จำกัดแรงดัน
- ไม่ควรดูเฉพาะ Voltage

---

# 15. Known Facts vs Unknowns

## Confirmed / Known

- มี Piezo 35mm จำนวน 10 ตัว (นำมาต่อขนาน 4 ตัว ทดสอบจริงได้ ~1V ต่อตัว รวม ~4V ผ่าน Rectifier)
- วงจร Breadboard: 1N4007 Bridge Rectifier + 470µF 16V Capacitor + Resistor 200Ω + LED สีเหลือง ประกอบและทดสอบกดติดสว่างได้จริงแล้ว (2026-08-23)
- รางถ่าน 1S2P สลับสีสายไฟจากโรงงาน: แก้ไขโดยบัดกรีสายดำเข้า `BAT+` และสายแดงเข้า `BAT-` บนบอร์ด PowerBank เรียบร้อย
- DIY PowerBank Module ทดสอบผ่านสาย Type-C ติดไฟสีฟ้า บอร์ดไม่ร้อน ทำงานปกติ
- มี 18650 จำนวน 2 ก้อน (GLINK 2600mAh)
- มี TP4056 USB-C (สำหรับทดสอบ Stage 4)
- มี Arduino UNO R3 (2 บอร์ด)
- มี Multimeter (Analog YX-961TR & Digital DT-9205M)
- LTC3588-1 อยู่ระหว่างรอขนส่งมาส่ง

## ยังไม่ยืนยัน

- กระแสจริงที่ Piezo 4/10 ตัวสามารถจ่ายได้
- Power จริงต่อการเหยียบ
- Energy ต่อหนึ่ง step
- Series หรือ Parallel ให้ output ที่เหมาะสมกว่า
- LTC3588 module ที่มีอยู่ต่อ Battery topology แบบใด
- PowerBank Module ที่มีอยู่มี charging circuit/protection ในตัวแบบใด
- 18650 แต่ละก้อนมีความจุจริงเท่าไร
- 18650 เป็น protected หรือ unprotected
- สามารถใช้ LTC3588 → Battery topology ปัจจุบันได้หรือไม่

AI ควรถือข้อมูลกลุ่มนี้เป็น **Unknowns** และไม่ควรแต่งตัวเลขขึ้นเอง

---

# 16. What NOT to Assume

AI ไม่ควรสรุปว่า:

```text
5V Peak = 5W
```

หรือ:

```text
470µF = Battery Charger
```

หรือ:

```text
TP4056 = Energy Harvester
```

หรือ:

```text
PowerBank Module = Piezo Energy Harvester
```

หรือ:

```text
LTC3588 = TP4056
```

อุปกรณ์เหล่านี้มีหน้าที่ต่างกัน

---

# 17. Recommended Mental Model

ให้มองระบบเป็น 4 Layer

## Layer 1 — Energy Generation

```text
Footstep
 ↓
Piezo
```

## Layer 2 — Energy Conditioning

```text
Rectification
 ↓
Capacitor
 ↓
Energy Harvesting / Power Management
```

## Layer 3 — Energy Storage

```text
18650 Battery
```

## Layer 4 — Energy Delivery

```text
PowerBank / Boost
 ↓
5V
 ↓
Arduino / USB Load
```

---

# 18. Definition of Success

Prototype รอบแรกถือว่าสำเร็จเมื่อสามารถแสดงให้เห็นได้ว่า:

```text
1. เหยียบจริง
       ↓
2. Piezo สร้างไฟ
       ↓
3. วัดแรงดัน/กระแสได้
       ↓
4. พลังงานสะสมเพิ่มขึ้น
       ↓
5. Battery system รับพลังงานผ่าน charging architecture ที่ปลอดภัย
       ↓
6. Battery จ่าย 5V ได้
       ↓
7. Arduino และ LED ทำงาน
```

สิ่งที่ต้องพิสูจน์ด้วยการวัด ไม่ใช่การสมมติจาก Voltage peak

---

# 19. Current Shopping / Hardware Status

## มีแล้ว

```text
Piezoelectric Disc 35mm ×10
1N4007 ×20
Resistor 200Ω
Jumper Wire M-M
Hookup Wire 22AWG Red/Black
Breadboard ×2
Arduino UNO R3 ×2
470µF Capacitor ×2
18650 Li-ion ×2
18650 2-cell Parallel Holder ×1
DIY PowerBank Module ×1
TP4056 USB-C ×1
LTC3588 Energy Harvester ×1
LED ×20
Multimeter ×1
Soldering equipment
Solder
```

## ยังอาจต้องเพิ่มในอนาคต

```text
HC-SR04 ×1
Additional resistor values
Heat-shrink / insulation
Suitable terminals/connectors
```

ไม่จำเป็นต้องซื้อเพิ่มเติมจนกว่าจะรู้ผลการวัดจาก Stage 1

---

# 20. How Another AI Should Help This Project

เมื่อ AI ตัวอื่นได้รับ context นี้ ให้ทำตามหลัก:

1. **ยึด Hardware ที่มีอยู่จริงเป็นหลัก**
2. **ถาม/ตรวจสอบ datasheet ของ module ก่อนแนะนำการต่อ**
3. **แยก Energy Harvesting, Battery Charging และ 5V Boost ออกจากกัน**
4. **อย่าแนะนำ Piezo → 18650 โดยตรง**
5. **อย่า assume ว่า TP4056 รับ Piezo pulse ได้**
6. **อย่า assume ว่า PowerBank module เป็น energy harvester**
7. **ถ้าข้อมูลไม่พอ ให้ระบุว่าเป็น Unknown**
8. **แนะนำการทดลองทีละ Stage**
9. **ให้วัด V/I/P ก่อนตัดสินใจซื้อ module ราคาแพง**
10. **เมื่อพูดถึง Li-ion ให้ prioritize safety over convenience**

---

# 21. Short Project Summary for AI

ถ้า AI ต้องการสรุปโปรเจกต์ในข้อความสั้น:

> piezoelectric-energy-harvesting เป็น Prototype ระบบ Footstep Piezoelectric Energy Harvesting ที่ใช้ Piezoelectric Disc หลายตัวรับแรงกดจากการเหยียบและสร้างพลังงานไฟฟ้าแบบ pulse จากนั้นผ่าน Rectification และ Capacitor เพื่อจัดการพลังงาน ก่อนนำเข้าสู่ Energy Harvesting / Power Management เช่น LTC3588 และศึกษาการเก็บพลังงานเข้าสู่ 18650 Li-ion จากนั้นใช้ DIY PowerBank Module เพื่อสร้าง 5V USB สำหรับจ่ายให้ Arduino UNO และ LED โดยมี TP4056 USB-C เป็นชุดชาร์จภายนอกสำหรับทดสอบ Battery แยกต่างหาก ระบบยังอยู่ในระยะ Prototype และค่ากระแส/กำลัง/พลังงานต่อการเหยียบยังต้องวัดจาก Hardware จริงก่อนตัดสินใจ Final Architecture

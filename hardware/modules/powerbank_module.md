# DIY PowerBank 5V 2A Boost & 2.4A Charger Module

เอกสารสเปก Pinout ประสิทธิภาพการแปลงพลังงาน และการต่อใช้งานโมดูล **DIY PowerBank 5V 2A Boost & Type-C Charger (Black PCB 2R2)**

---

## 1. ภาพรวมโมดูล (Overview & Layout)

![PowerBank Module Front](/d:/Github-project/piezoelectric-energy-harvesting/image/powerbank_module/powerbank_module_front_overview.png)

โมดูลนี้ทำหน้าที่ 2 ระบบในบอร์ดเดียว (Bi-directional Power Management):
1. **วงจรชาร์จแบตเตอรี่ (Step-Down Charger):** รับไฟเข้าทางพอร์ต **Type-C 5V** ชาร์จแบตเตอรี่ 3.7V สูงสุด **2.4A**
2. **วงจรจ่ายไฟบูสต์ (Step-Up Boost Converter):** ดึงไฟจากแบตเตอรี่ 18650 แปลงเป็น **5V DC สูงสุด 2A** ทางช่อง USB-A และจุดบัดกรี `+ 5V -`

---

## 2. ตารางข้อมูลจำเพาะทางเทคนิค (Technical Specifications)

| พารามิเตอร์ | ค่าสเปก | หมายเหตุ |
|---|---|---|
| **แรงดันไฟชาร์จเข้า (Input Charging)** | **5V DC (ผ่านพอร์ต Type-C)** | รองรับกระแสชาร์จสูงสุด **2.4A (MAX)** |
| **แรงดันไฟจ่ายออก (Output Boost)** | **5V DC (5.0V – 5.15V)** | ทางพอร์ต USB-A และจุดบัดกรี `+ 5V -` |
| **กระแสจ่ายออกสูงสุด (Max Output Current)** | **2.0 A (MAX)** | เลี้ยง Arduino UNO (~50mA) และโหลดเสริมได้สบาย |
| **แรงดันแบตเตอรี่ที่รองรับ (Battery Compatibility)** | **3.7V Li-ion / 18650 / Li-Po (1S หรือ 1S2P ขนาน)** | รางถ่าน GLINK 1S2P ต่อได้โดยตรง |
| **ไฟบอกระดับแบตเตอรี่ (Battery LED Indicator)** | **LED 4 ดวง** | แสดงระดับ **25%, 50%, 75%, 100%** |
| **แรงดันตัดการชาร์จเริ่มต้น (Default Charge Cutoff)** | **4.20V** | สำหรับถ่าน 18650 ปกติ (มี Pad สลับเป็น 4.35V ได้) |

---

## 3. ประสิทธิภาพการแปลงพลังงาน (Conversion Efficiency)

![Efficiency Table](/d:/Github-project/piezoelectric-energy-harvesting/image/powerbank_module/powerbank_conversion_efficiency_table.png)

| Input Voltage (จากแบต) | Input Current | Output Voltage | Output Current (ไปยังโหลด) | ประสิทธิภาพการแปลง (Efficiency) |
|:---:|:---:|:---:|:---:|:---:|
| **3.837 V** | 0.685 A | **5.039 V** | **0.5 A** | **95.90 %** |
| **3.758 V** | 1.427 A | **5.138 V** | **1.0 A** | **95.80 %** |
| **3.673 V** | 2.225 A | **5.146 V** | **1.5 A** | **94.50 %** |
| **3.580 V** | 3.086 A | **5.112 V** | **2.0 A** | **92.50 %** |

> [!TIP]
> ประสิทธิภาพเฉลี่ยสูงกว่า **92% - 96%** ทำให้สูญเสียพลังงานในรูปความร้อนต่ำมากเมื่อจ่ายไฟให้ Arduino UNO

---

## 4. แผนผังการต่อสายและฟังก์ชันปุ่มกด (Wiring & Key Function)

![Wiring Diagram](/d:/Github-project/piezoelectric-energy-harvesting/image/powerbank_module/powerbank_module_wiring_diagram.png)

### จุดบัดกรีบนบอร์ด:
- **`+` (BAT+):** ต่อเข้า **สายสีแดง (+)** จากรางถ่าน 1S2P ✅ *(แก้ไขบัดกรีถูกต้องแล้ว 2026-08-25 — สายสีแดง = ขั้วบวกจริง)*
- **`-` (BAT-):** ต่อเข้า **สายสีดำ (-)** จากรางถ่าน 1S2P ✅ *(สายสีดำ = ขั้วลบจริง)*
- **`+ 5V -`:** จุดบัดกรีไฟออก 5V จ่ายตรงเข้า Arduino (5V / GND)
- **พอร์ต USB-A:** เสียบสาย USB เข้า Arduino UNO ได้โดยตรง

### ฟังก์ชันปุ่มกด (Key Switch Pad `K`):
- **กด 1 ครั้ง:** เปิดการจ่ายไฟ 5V Output และเปิดไฟแสดงระดับแบตเตอรี่ 4 ดวง
- **กด 2 ครั้งติดกัน (Double Click):** สั่งปิดการจ่ายไฟ 5V (เข้าสู่ Standby Sleep Mode)

---

## 5. การปรับแรงดันชาร์จแบตเตอรี่ (Charge Voltage Adjustment)

![Charge Voltage Setting](/d:/Github-project/piezoelectric-energy-harvesting/image/powerbank_module/powerbank_charge_voltage_setting.png)

- **ค่าเริ่มต้น (Default):** **4.20V** (เหมาะสำหรับแบตเตอรี่ GLINK 18650 ที่ใช้งานอยู่)
- **ปรับเป็น 4.35V:** ทำได้โดยการแต้มตะกั่วเชื่อม Pad 4.35V (ใช้สำหรับถ่าน LiHV เท่านั้น — **ในโปรเจกต์นี้ห้ามแต้ม ให้ใช้ 4.2V ตามเดิม**)

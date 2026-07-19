# PLC + IoT ด้วย AI โดยใช้ Industrial ESP32 
https://www.uncle-engineer.com/course/plc-iot-esp32/

ผู้เรียนสามารถพัฒนาระบบควบคุมอัตโนมัติและระบบ Industrial IoT ได้จริง โดยใช้ ESP32 Industrial Controller เป็นแพลตฟอร์มหลักในการเรียนรู้ ตั้งแต่การเชื่อมต่อเซนเซอร์ การควบคุมอุปกรณ์ การสื่อสารข้อมูล การเชื่อมต่อ Cloud การสร้าง Dashboard และการนำ AI มาประยุกต์ใช้เนื้อหาทั้งหมดเน้นการนำไปใช้งานจริง พร้อมตัวอย่างโครงงานที่สามารถต่อยอดสู่ Smart Factory, Smart Farm และ Smart Building ได้
- ในคอร์สใช้ภาษาซีในการเขียนร่วมกับ AI ผ่าน Ardunio IDE
- อุปกรณ์ที่ใช้ประกอบการสอนเป็น ESP32 PLC ของ erqos.com รุ่น EQSP32C-X แต่สามารถใช้กับ PLC รุ่นอื่น ๆ ที่ใช้ภาษาซีเขียนได้มี Library ให้

ระยะเวลา จำนวน 10 สัปดาห์ (2-3 ชั่วโมง/สัปดาห์)

## Week 1
-รู้จัก PLC, Industrial IoT และ AI
-แนวคิดระบบอัตโนมัติในอุตสาหกรรม
-PLC คืออะไร
-Industrial IoT คืออะไร
-Industry 4.0 และ Smart Factory
-AI กับงานระบบอัตโนมัติ
-แนะนำฮาร์ดแวร์ ESP32
-การติดตั้งเครื่องมือสำหรับพัฒนาโปรแกรม

## Week 2
-การควบคุม Digital Input และ Output
-หลักการทำงานของ Digital Signal
-การเชื่อมต่อ Push Button และ Switch
-การเชื่อมต่อ Sensor แบบ NPN และ PNP
-การควบคุม Relay และ Actuator
-การสร้างระบบ Start-Stop
-หลักการ Interlock และ Safety Logic

## Week 3
-พื้นฐานการเขียนโปรแกรม PLC
-PLC Scan Cycle
-ลำดับการทำงานของโปรแกรม
-การใช้งาน Timer
-การใช้งาน Counter
-State Machine
-การออกแบบ Logic ควบคุมเครื่องจักร

## Week 4
-การเชื่อมต่อ Analog Sensor
-หลักการของ Analog Signal
-สัญญาณ 0-10V
-สัญญาณ 4-20mA
-การแปลงสเกลข้อมูล
-การสอบเทียบเซนเซอร์
-การวัดอุณหภูมิ ระดับน้ำ และแรงดัน

## Week 5
-การสื่อสารอุตสาหกรรมด้วย RS485, Modbus RTU และ CAN Bus
-แนวคิดระบบสื่อสารในงานอุตสาหกรรม
-พื้นฐาน RS485
-Modbus RTU Protocol
-Master และ Slave
-การอ่านข้อมูลจาก Energy Meter
-การเชื่อมต่ออุปกรณ์ภาคสนามผ่าน Modbus
-หลักการทำงานของ CAN Bus
-CAN Frame และ Arbitration
-การเชื่อมต่อเครือข่าย CAN Bus
-การรับส่งข้อมูลระหว่างอุปกรณ์
-การประยุกต์ใช้ CAN Bus ในเครื่องจักรและยานยนต์

## Week 6
-Industrial IoT และ MQTT
-พื้นฐาน MQTT
-Broker และ Client
-Publish และ Subscribe
-การส่งข้อมูลขึ้น Cloud
-การรับข้อมูลจากอุปกรณ์ภาคสนาม
-การออกแบบระบบ IoT

## Week 7
-การสร้าง Dashboard ด้วย Node-RED
-การติดตั้ง Node-RED
-การเชื่อมต่อ MQTT
-การสร้าง Dashboard
-การแสดงผลข้อมูลแบบ Real-Time
-การควบคุมอุปกรณ์ผ่าน Web Interface
-การสร้างระบบ Monitoring

## Week 8
-การจัดเก็บข้อมูลและวิเคราะห์ข้อมูลอุตสาหกรรม
-Data Logging
-Time-Series Database
-การใช้งาน InfluxDB
-การสร้าง Dashboard
-การวิเคราะห์ข้อมูลย้อนหลัง
-การสร้างรายงานและกราฟสถิติ

## Week 9
-การประยุกต์ใช้ AI ในงาน PLC และ Industrial IoT
-พื้นฐาน AI สำหรับวิศวกร
-Prompt Engineering
-การใช้ ChatGPT ช่วยเขียนโปรแกรม
-การสร้างเอกสารอัตโนมัติ
-การวิเคราะห์ข้อมูลเซนเซอร์ด้วย AI
-การสร้างระบบแจ้งเตือนอัจฉริยะ
-AI Assistant สำหรับงานซ่อมบำรุง

## Week 10
โครงงาน PLC และ Industrial IoT ด้วย AI
-การออกแบบระบบ Smart Home
-การติดตามสถานะเครื่องจักร
-การตรวจวัดพลังงานไฟฟ้า
-การวิเคราะห์ข้อมูลด้วย AI
-การสร้าง Dashboard แบบครบวงจร
-การเชื่อมต่อข้อมูลจาก Sensor, Modbus RTU, CAN Bus และ MQTT เข้าสู่ระบบเดียวกัน

### สิ่งที่ผู้เรียนจะได้รับ
-เอกสารประกอบการเรียน
-ตัวอย่าง Source Code
-ตัวอย่างโปรเจกต์ Industrial IoT
-ไฟล์ Dashboard และ Flow ตัวอย่าง

### โครงงานที่สามารถต่อยอดได้
-Smart Factory Monitoring
-Energy Monitoring System
-Smart Pump Control
-Smart Irrigation System
-Predictive Maintenance System
-Machine Data Acquisition System
-Industrial Gateway (Modbus RTU + CAN Bus + MQTT)
-AI-Powered Industrial Dashboard

<img width="1122" height="1402" alt="image" src="https://github.com/user-attachments/assets/bf501a89-2d03-4eaf-95f5-1b6fe14180bd" />

## อุปกรณ์หลักที่ใช้ (EQSP32C-X – Industrial IoT)
https://erqos.com/product/eqsp32c-x-industrial-iot-esp32-plc-external-antenna/

<img width="2560" height="1920" alt="image" src="https://github.com/user-attachments/assets/82835240-31ae-4187-a15b-0e56a7bfbe04" />

## อุปกรณ์ทางเลือก (ESP32-S3)
<img width="1254" height="1254" alt="image" src="https://github.com/user-attachments/assets/95683a7e-86ce-49d7-b380-73f0e41611cf" />



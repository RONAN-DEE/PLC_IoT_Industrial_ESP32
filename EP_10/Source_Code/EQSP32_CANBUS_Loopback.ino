#include <EQSP32.h>


EQSP32 eqsp32;

// ตัวแปรสำหรับจับเวลาส่งสัญญาณ
unsigned long lastTxTime = 0;
const unsigned long txInterval = 2000; // ส่งเฟรมข้อมูลทุกๆ 2 วินาที (2000ms)
uint8_t messageCounter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; } // รอการเชื่อมต่อ Serial Port
  
  Serial.println("\n Starting EQSP32 CAN Bus Loopback Test (Mode 2)...");
  
  // เริ่มต้นระบบหลักของ EQSP32
  eqsp32.begin(); 

  /**
   * คอนฟิกตัวระบบ CAN Bus ในรูปแบบ Demo Configuration 2
   * พารามิเตอร์: 
   * 1. ความเร็ว: CAN_500K (500 kbps)
   * 2. ฟิลเตอร์ไอดี: 0 (ยอมรับและรับสัญญาณทุก ID)
   * 3. ลูปแบ็ก: true (เปิดระบบส่ง-รับข้อมูลตัวเองโดยไม่ต้องต่อบอร์ดอื่น)
   */
  Serial.println("🔧 Mode 2: Accept All + Loopback");
  if (eqsp32.configCAN(CAN_500K, 0, true)) {
    Serial.println("✅ CAN interface initialized successfully.");
  } else {
    Serial.println("❌ Failed to initialize CAN interface.");
    while (true); // สั่งหยุดโปรแกรมหากเปิดระบบไม่สำเร็จ
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. ส่วนการส่งสัญญาณ (TRANSMIT SECTION) จะทำงานทุกๆ 2 วินาที
  if (currentMillis - lastTxTime >= txInterval) {
    lastTxTime = currentMillis;

    CanMessage txMsg = {};
    txMsg.identifier = 0x120;           // ตัวระบุมาตรฐาน 11-bit ID
    txMsg.data_length_code = 4;        // ระบุขนาดข้อมูล 4 ไบต์ (DLC=4)
    txMsg.data[0] = messageCounter++;  // ข้อมูลจำลองไบต์ที่ 0 สั่งนับเลขขึ้นเรื่อยๆ
    txMsg.data[1] = 0x11;              // ข้อมูลจำลองไบต์ที่ 1
    txMsg.data[2] = 0x22;              // ข้อมูลจำลองไบต์ที่ 2
    txMsg.data[3] = 0x33;              // ข้อมูลจำลองไบต์ที่ 3

    // สั่งส่ง Frame ข้อมูลออกไป
    if (eqsp32.transmitCANFrame(txMsg)) {
      Serial.printf("✉🡆\tTX: ID=0x%03X\tData=[ %02X %02X %02X %02X ]\n", 
                    txMsg.identifier, txMsg.data[0], txMsg.data[1], txMsg.data[2], txMsg.data[3]);
    } else {
      Serial.println("⚠ Failed to send CAN message.");
    }
  }

  // 2. ส่วนการดักรับข้อมูล (RECEIVE SECTION) ด้วยระบบ Loopback ข้อมูลที่ส่งจะเด้งกลับมาฝั่งนี้ทันที
  CanMessage rxMsg;
  if (eqsp32.receiveCANFrame(rxMsg)) {
    Serial.printf("🡄✉\tRX: ID=0x%03X\tData=[ ", rxMsg.identifier);
    for (int i = 0; i < rxMsg.data_length_code; ++i) {
      Serial.printf("%02X ", rxMsg.data[i]);
    }
    Serial.printf("]\tDLC=%d\n", rxMsg.data_length_code);
  }

  delay(1); 
}

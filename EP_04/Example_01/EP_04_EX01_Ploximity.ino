// โจทย์ที่ 1: นับจำนวนชิ้นงานโลหะ 10 ชิ้นแล้วหยุดสายพาน เปิดไฟเตือน 5 วินาที
const int PIN_START = 4; // X0
const int PIN_STOP  = 5; // X1
const int PIN_PX1   = 6; // X2 (Inductive Proximity)

const int PIN_M1    = 7; // Y0 (Motor)
const int PIN_LAMP  = 8; // Y1 (Lamp)

bool m1_state = false;
bool lamp_state = false;
int counter = 0;

bool last_px1_state = HIGH; 
unsigned long lamp_start_time = 0;
bool timer_active = false;

void setup() {
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_STOP, INPUT_PULLUP);
  pinMode(PIN_PX1, INPUT_PULLUP);
  
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_LAMP, OUTPUT);
  
  digitalWrite(PIN_M1, LOW);
  digitalWrite(PIN_LAMP, LOW);
}

void loop() {
  // อ่านค่า Input (PLC ปกติเป็น Active High แต่ ESP32 ใช้ Pull-up จึงต้องกลับลอจิกด้วย !)
  bool start_btn = !digitalRead(PIN_START);
  bool stop_btn  = !digitalRead(PIN_STOP);
  bool px1_state = !digitalRead(PIN_PX1);

  // 1. วงจร Start / Stop และ Interlock ด้วย Counter (C0) และ Timer (T0)
  if (start_btn && !stop_btn && (counter < 10) && !timer_active) {
    m1_state = true;
  }
  if (stop_btn || (counter >= 10)) {
    m1_state = false;
  }

  // 2. ส่วนนับจำนวนชิ้นงาน (Counter) ตรวจจับขอบขาขึ้น (Rising Edge)
  if (px1_state == HIGH && last_px1_state == LOW && m1_state) {
    delay(20); // ป้องกันสัญญาณ Debounce 
    counter++;
  }
  last_px1_state = px1_state;

  // 3. ส่วนควบคุมเวลาไฟเตือน 5 วินาที (Timer)
  if (counter >= 10 && !timer_active) {
    lamp_state = true;
    lamp_start_time = millis();
    timer_active = true;
  }

  if (timer_active) {
    if (millis() - lamp_start_time >= 5000) { // ครบ 5 วินาที (5000 ms)
      lamp_state = false;
      timer_active = false;
      counter = 0; // รีเซ็ตตัวนับ (RST C0)
    }
  }

  // ขับเอาต์พุตออกขาขาสัญญาณ
  digitalWrite(PIN_M1, m1_state);
  digitalWrite(PIN_LAMP, lamp_state);
}

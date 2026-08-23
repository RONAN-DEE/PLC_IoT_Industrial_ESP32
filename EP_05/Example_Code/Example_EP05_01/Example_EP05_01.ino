#define ANALOG_PIN 1        // เลือกใช้ขา GPIO 1 ของ ESP32-S3
#define MAX_ADC_VALUE 4095  // ESP32-S3 มี ADC ความละเอียด 12-bit
#define MAX_VOLTAGE 3.3     // แรงดันอ้างอิงของ ESP32-S3

// ค่าตัวต้านทานที่ใช้จริง (เปลี่ยนตามค่าที่คุณใช้วิธีที่ 2)
const float R1 = 20000.0;   // 20 kOhm
const float R2 = 10000.0;   // 10 Ohm

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // ตั้งค่าความละเอียด ADC เป็น 12-bit
}

void loop() {
  int adcValue = analogRead(ANALOG_PIN);
  
  // 1. แปลงค่า ADC เป็นแรงดันไฟฟ้าที่ขา ESP32-S3 ได้รับจริง (0 - 3.3V)
  float measuredVoltage = (adcValue / (float)MAX_ADC_VALUE) * MAX_VOLTAGE;
  
  // 2. คำนวณกลับไปเป็นแรงดันต้นทางของเซ็นเซอร์ (0 - 10V)
  // หากใช้วิธีที่ 2 (Voltage Divider):
  float sensorVoltage = measuredVoltage * ((R1 + R2) / R2);
  
  // หากใช้วิธีที่ 1 (โมดูลสำเร็จรูปที่มีการปรับจูนเป๊ะๆ แล้ว):
  // float sensorVoltage = (measuredVoltage / 3.3) * 10.0;

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | ESP32 Volt: ");
  Serial.print(measuredVoltage, 2);
  Serial.print(" V | Sensor Volt: ");
  Serial.print(sensorVoltage, 2);
  Serial.println(" V");

  delay(1000);
}

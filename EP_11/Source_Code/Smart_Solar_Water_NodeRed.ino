#include "EQSP32.h" 
EQSP32 eqsp32; 

#define PIN_BOILER_TEMP 1 
#define PIN_PANEL_TEMP 2 
#define PIN_HEATER 3 
#define PIN_PUMP 4 

std::string haBoilerTemp = "Boiler Temperature"; 
std::string haPanelTemp = "Panel Temperature"; 
std::string haHeater = "Electric Heater"; 
std::string haPump = "Circulation Pump"; 
std::string haHeaterControl = "Heater Control"; 

void setup() { 
  EQSP32Configs cfg; 
  cfg.devSystemID = "SolarHeaterV1"; 
  eqsp32.begin(cfg, true); // เปิดใช้งาน MQTT ร่วมกับ EQConnect
  
  // ตั้งค่าพินเซนเซอร์อุณหภูมิ NTC
  eqsp32.pinMode(PIN_BOILER_TEMP, TIN); 
  eqsp32.configTIN(PIN_BOILER_TEMP, 3988, 10000); 
  eqsp32.pinMode(PIN_PANEL_TEMP, TIN); 
  eqsp32.configTIN(PIN_PANEL_TEMP, 3988, 10000); 
  
  // ตั้งค่าพินรีเลย์เอาต์พุต
  eqsp32.pinMode(PIN_HEATER, RELAY); 
  eqsp32.configRELAY(PIN_HEATER, 500, 1000); 
  eqsp32.pinMode(PIN_PUMP, RELAY); 
  eqsp32.configRELAY(PIN_PUMP, 500, 1000); 
  
  // สร้าง Entity ส่งค่าเข้า MQTT (Node-RED จะมาดึงจากตรงนี้)
  createDisplay_Sensor(haBoilerTemp, 1, "°C", "mdi:thermometer", "temperature"); 
  createDisplay_Sensor(haPanelTemp, 1, "°C", "mdi:thermometer", "temperature"); 
  createDisplay_BinarySensor(haHeater, "mdi:heating-coil"); 
  createDisplay_BinarySensor(haPump, "mdi:water-pump"); 
  createControl_Switch(haHeaterControl, "mdi:toggle-switch"); 
} 

void loop() { 
  // 1. อ่านค่าจากเซนเซอร์ฮาร์ดแวร์
  float boilerTemp = eqsp32.readPin(PIN_BOILER_TEMP) / 10.0; 
  float panelTemp = eqsp32.readPin(PIN_PANEL_TEMP) / 10.0; 
  
  // 2. อัปเดตค่าส่งขึ้น MQTT Broker ให้ Node-RED เห็น
  updateDisplay_Sensor(haBoilerTemp, boilerTemp); 
  updateDisplay_Sensor(haPanelTemp, panelTemp); 
  updateDisplay_BinarySensor(haHeater, eqsp32.readPin(PIN_HEATER) > 0); 
  updateDisplay_BinarySensor(haPump, eqsp32.readPin(PIN_PUMP) > 0); 
  
  delay(1000); // อัปเดตข้อมูลทุกๆ 1 วินาที
}

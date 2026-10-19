#include "EQSP32.h" 
EQSP32 eqsp32; 

#define PIN_BOILER_TEMP 1 
#define PIN_PANEL_TEMP 2 
#define PIN_HEATER 3 
#define PIN_PUMP 4 

const float HYSTERESIS = 2.0; 
const float TEMP_DIFF_ON = 10.0; 
const float BOILER_MAX_TEMP = 60.0; 
const float HEATER_ON_TEMP = 35.0; 
const float HEATER_OFF_TEMP = 45.0; 

std::string haBoilerTemp = "Boiler Temperature"; 
std::string haPanelTemp = "Panel Temperature"; 
std::string haHeater = "Electric Heater"; 
std::string haPump = "Circulation Pump"; 
std::string haHeaterControl = "Heater Control"; 
std::string haHeatLimit = "Heat Limit"; 

void setup() { 
  EQSP32Configs cfg; 
  cfg.devSystemID = "SolarHeaterV1"; 
  eqsp32.begin(cfg, true); 
  
  eqsp32.pinMode(PIN_BOILER_TEMP, TIN); 
  eqsp32.configTIN(PIN_BOILER_TEMP, 3988, 10000); 
  eqsp32.pinMode(PIN_PANEL_TEMP, TIN); 
  eqsp32.configTIN(PIN_PANEL_TEMP, 3988, 10000); 
  
  eqsp32.pinMode(PIN_HEATER, RELAY); 
  eqsp32.configRELAY(PIN_HEATER, 500, 1000); 
  eqsp32.pinMode(PIN_PUMP, RELAY); 
  eqsp32.configRELAY(PIN_PUMP, 500, 1000); 
  
  createDisplay_Sensor(haBoilerTemp, 1, "°C", "mdi:thermometer", "temperature"); 
  createDisplay_Sensor(haPanelTemp, 1, "°C", "mdi:thermometer", "temperature"); 
  createDisplay_BinarySensor(haHeater, "mdi:heating-coil"); 
  createDisplay_BinarySensor(haPump, "mdi:water-pump"); 
  createDisplay_BinarySensor(haHeatLimit, "mdi:alert", "heat"); 
  createControl_Switch(haHeaterControl, "mdi:toggle-switch"); 
  
  eqsp32.pinValue(PIN_HEATER, 0); 
  eqsp32.pinValue(PIN_PUMP, 0); 
  
  updateDisplay_Sensor(haBoilerTemp, 0); 
  updateDisplay_Sensor(haPanelTemp, 0); 
  updateDisplay_BinarySensor(haHeater, false); 
  updateDisplay_BinarySensor(haPump, false); 
  updateDisplay_BinarySensor(haHeatLimit, false); 
  updateControl_Switch(haHeaterControl, false); 
} 

void loop() { 
  float boilerTemp = eqsp32.readPin(PIN_BOILER_TEMP) / 10.0; 
  float panelTemp = eqsp32.readPin(PIN_PANEL_TEMP) / 10.0; 
  bool manualHeater = readControl_Switch(haHeaterControl); 
  bool pumpRunning = (eqsp32.readPin(PIN_PUMP) > 0); 
  
  // ระบบควบคุมปั๊มหมุนเวียน (Circulation Pump)
  if (boilerTemp < BOILER_MAX_TEMP - HYSTERESIS) { 
    if (panelTemp > boilerTemp + TEMP_DIFF_ON + HYSTERESIS) { 
      eqsp32.pinValue(PIN_PUMP, 1000); 
    } else if (panelTemp < boilerTemp + TEMP_DIFF_ON) { 
      eqsp32.pinValue(PIN_PUMP, 0); 
    } 
  } else if (boilerTemp > BOILER_MAX_TEMP) { 
    eqsp32.pinValue(PIN_PUMP, 0); 
  } 
  
  // ระบบควบคุมฮีตเตอร์สำรอง (Resistive Heater) ทำงานสัมพันธ์กับปั๊ม
  if (manualHeater && !pumpRunning) { 
    if (boilerTemp > HEATER_OFF_TEMP) { 
      eqsp32.pinValue(PIN_HEATER, 0); 
    } else if (boilerTemp < HEATER_ON_TEMP - HYSTERESIS) { 
      eqsp32.pinValue(PIN_HEATER, 1000); 
    } 
  } else { 
    eqsp32.pinValue(PIN_HEATER, 0); 
  } 
  
  // อัปเดตสถานะไปยัง Home Assistant
  bool heatLimitActive = (manualHeater && !pumpRunning && boilerTemp > HEATER_OFF_TEMP) || (boilerTemp > BOILER_MAX_TEMP && panelTemp > boilerTemp + TEMP_DIFF_ON + HYSTERESIS); 
  
  updateDisplay_Sensor(haBoilerTemp, boilerTemp); 
  updateDisplay_Sensor(haPanelTemp, panelTemp); 
  updateDisplay_BinarySensor(haHeater, eqsp32.readPin(PIN_HEATER) > 0); 
  updateDisplay_BinarySensor(haPump, eqsp32.readPin(PIN_PUMP) > 0); 
  updateDisplay_BinarySensor(haHeatLimit, heatLimitActive); 
}

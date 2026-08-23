#include "HX711.h" // Include the HX711 library

// Define pins for HX711
#define DT 40  // ESP32-S3 GPIO connected to HX711 DAT
#define SCK 39 // ESP32-S3 GPIO connected to HX711 CLK

HX711 scale; // Create an instance of the HX711 class

void setup() {
  Serial.begin(115200); // Initialize serial communication
  scale.begin(DT, SCK); // Initialize the HX711 with the defined pins
  Serial.println("HX711 Load Cell Example");
  
  // Calibrate the scale (adjust the factor based on your setup)
  scale.set_scale(2280.f); // Set the scale factor (calibration value)
  scale.tare(); // Reset the scale to zero
}

void loop() {
  // Read the weight from the load cell
  if (scale.is_ready()) {
    float weight = scale.get_units(); // Get the weight in units
    // ใส่ตรงนี้สมการปรับค่า
    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" kg");
  } else {
    Serial.println("HX711 not ready. Check wiring.");
  }
  delay(500); // Wait for 500ms before the next reading
}

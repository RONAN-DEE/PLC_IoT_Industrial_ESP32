// Define the analog pin connected to the LDR
#define ANALOG_PIN 1 

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(11520);
}

void loop() {
  // Read the analog value from the LDR
  int ldrValue = analogRead(ANALOG_PIN);

  // Convert the analog value to a voltage (assuming 5V reference)
  float voltage = ldrValue * (3.3 / 4095.0);
  

  // Print the LDR value and voltage to the Serial Monitor
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  // Add a small delay to avoid flooding the Serial Monitor
  delay(500);
}

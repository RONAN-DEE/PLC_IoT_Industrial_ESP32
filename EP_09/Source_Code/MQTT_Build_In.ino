#include <EQSP32.h>

EQSP32 eqsp32;

// MQTT Entity Names
std::string di1Name = "DI1";
std::string di2Name = "DI2";
std::string di3Name = "DI3";
std::string di4Name = "DI4";

std::string ai5Name = "AI5";
std::string ai6Name = "AI6";
std::string ai7Name = "AI7";
std::string ai8Name = "AI8";

std::string relay9Name  = "Relay9";
std::string relay10Name = "Relay10";
std::string relay11Name = "Relay11";
std::string relay12Name = "Relay12";
std::string relay13Name = "Relay13";
std::string relay14Name = "Relay14";
std::string relay15Name = "Relay15";
std::string relay16Name = "Relay16";

void setup()
{
    Serial.begin(115200);

    // Uses EQConnect provisioning and built-in MQTT
    eqsp32.begin();

    // Inputs
    for(int pin=1; pin<=4; pin++)
        eqsp32.pinMode(pin, DIN);

    for(int pin=5; pin<=8; pin++)
        eqsp32.pinMode(pin, AIN);

    // Relay outputs
    for(int pin=9; pin<=16; pin++)
    {
        eqsp32.pinMode(pin, RELAY);
        eqsp32.pinValue(pin, 0);
    }

    // Publish-only values
    createSensor_Value(di1Name, "mdi:toggle-switch");
    createSensor_Value(di2Name, "mdi:toggle-switch");
    createSensor_Value(di3Name, "mdi:toggle-switch");
    createSensor_Value(di4Name, "mdi:toggle-switch");

    createSensor_Value(ai5Name, "mdi:gauge");
    createSensor_Value(ai6Name, "mdi:gauge");
    createSensor_Value(ai7Name, "mdi:gauge");
    createSensor_Value(ai8Name, "mdi:gauge");

    // Relay controls
    createControl_Switch(relay9Name,  "mdi:relay");
    createControl_Switch(relay10Name, "mdi:relay");
    createControl_Switch(relay11Name, "mdi:relay");
    createControl_Switch(relay12Name, "mdi:relay");
    createControl_Switch(relay13Name, "mdi:relay");
    createControl_Switch(relay14Name, "mdi:relay");
    createControl_Switch(relay15Name, "mdi:relay");
    createControl_Switch(relay16Name, "mdi:relay");
}

void loop()
{
    // Read inputs
    updateSensor_Value(di1Name, eqsp32.readPin(1));
    updateSensor_Value(di2Name, eqsp32.readPin(2));
    updateSensor_Value(di3Name, eqsp32.readPin(3));
    updateSensor_Value(di4Name, eqsp32.readPin(4));

    updateSensor_Value(ai5Name, eqsp32.readPin(5));
    updateSensor_Value(ai6Name, eqsp32.readPin(6));
    updateSensor_Value(ai7Name, eqsp32.readPin(7));
    updateSensor_Value(ai8Name, eqsp32.readPin(8));

    // Read MQTT switch commands and drive relays
    eqsp32.pinValue(9,  readControl_Switch(relay9Name)  ? 1000 : 0);
    eqsp32.pinValue(10, readControl_Switch(relay10Name) ? 1000 : 0);
    eqsp32.pinValue(11, readControl_Switch(relay11Name) ? 1000 : 0);
    eqsp32.pinValue(12, readControl_Switch(relay12Name) ? 1000 : 0);
    eqsp32.pinValue(13, readControl_Switch(relay13Name) ? 1000 : 0);
    eqsp32.pinValue(14, readControl_Switch(relay14Name) ? 1000 : 0);
    eqsp32.pinValue(15, readControl_Switch(relay15Name) ? 1000 : 0);
    eqsp32.pinValue(16, readControl_Switch(relay16Name) ? 1000 : 0);

    delay(10);
}
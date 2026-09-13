#include <EQSP32.h>
#include <ModbusIP_ESP8266.h>

EQSP32 eqsp32;
ModbusIP mb;

// Discrete Inputs
const uint16_t DI_1 = 0;
const uint16_t DI_2 = 1;
const uint16_t DI_3 = 2;
const uint16_t DI_4 = 3;

// Input Registers
const uint16_t AI_5 = 0;
const uint16_t AI_6 = 1;
const uint16_t AI_7 = 2;
const uint16_t AI_8 = 3;

// Coils
const uint16_t DO_9  = 0;
const uint16_t DO_10 = 1;
const uint16_t DO_11 = 2;
const uint16_t DO_12 = 3;
const uint16_t DO_13 = 4;
const uint16_t DO_14 = 5;
const uint16_t DO_15 = 6;
const uint16_t DO_16 = 7;

void setup()
{
    Serial.begin(115200);

    // --------------------------------------------------
    // Static Network Configuration
    // --------------------------------------------------
    EQSP32Configs cfg;

    cfg.wifiSSID     = "YOUR_WIFI_SSID";
    cfg.wifiPassword = "YOUR_WIFI_PASSWORD";

    cfg.staticIP = "192.168.1.200";
    cfg.subnet   = "255.255.255.0";
    cfg.gateway  = "192.168.1.1";
    cfg.DNS      = "8.8.8.8";

    eqsp32.begin(cfg);

    // Configure Inputs
    eqsp32.pinMode(1, DIN);
    eqsp32.pinMode(2, DIN);
    eqsp32.pinMode(3, DIN);
    eqsp32.pinMode(4, DIN);

    eqsp32.pinMode(5, AIN);
    eqsp32.pinMode(6, AIN);
    eqsp32.pinMode(7, AIN);
    eqsp32.pinMode(8, AIN);

    // Configure Outputs
    for (int pin = 9; pin <= 16; pin++)
    {
        eqsp32.pinMode(pin, POUT);
        eqsp32.pinValue(pin, 0);
    }

    // Wait for network
    while (!eqsp32.isDeviceOnline())
    {
        delay(100);
    }

    Serial.println();
    Serial.print("Modbus TCP IP Address: ");
    Serial.println(eqsp32.localIP());

    // Start Modbus TCP server (Port 502)
    mb.server();

    // Discrete Inputs (10001-10004)
    for (int i = 0; i < 4; i++)
        mb.addIsts(i);

    // Input Registers (30001-30004)
    for (int i = 0; i < 4; i++)
        mb.addIreg(i);

    // Coils (00001-00008)
    for (int i = 0; i < 8; i++)
        mb.addCoil(i);

    Serial.println("Modbus TCP Server Ready");
}

void loop()
{
    mb.task();

    // Read Digital Inputs 1-4
    mb.Ists(DI_1, eqsp32.readPin(1));
    mb.Ists(DI_2, eqsp32.readPin(2));
    mb.Ists(DI_3, eqsp32.readPin(3));
    mb.Ists(DI_4, eqsp32.readPin(4));

    // Read Analog Inputs 5-8
    mb.Ireg(AI_5, eqsp32.readPin(5));
    mb.Ireg(AI_6, eqsp32.readPin(6));
    mb.Ireg(AI_7, eqsp32.readPin(7));
    mb.Ireg(AI_8, eqsp32.readPin(8));

    // Write Outputs 9-16 from Coils
    eqsp32.pinValue(9,  mb.Coil(DO_9)  ? 1000 : 0);
    eqsp32.pinValue(10, mb.Coil(DO_10) ? 1000 : 0);
    eqsp32.pinValue(11, mb.Coil(DO_11) ? 1000 : 0);
    eqsp32.pinValue(12, mb.Coil(DO_12) ? 1000 : 0);
    eqsp32.pinValue(13, mb.Coil(DO_13) ? 1000 : 0);
    eqsp32.pinValue(14, mb.Coil(DO_14) ? 1000 : 0);
    eqsp32.pinValue(15, mb.Coil(DO_15) ? 1000 : 0);
    eqsp32.pinValue(16, mb.Coil(DO_16) ? 1000 : 0);

    delay(10);
}

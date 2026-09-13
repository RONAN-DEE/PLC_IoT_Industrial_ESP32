#include <EQSP32.h>
#include <ModbusIP_ESP8266.h>

EQSP32 eqsp32;
ModbusIP mb;

void setup()
{
    Serial.begin(115200);

    // --------------------------------------------------
    // Static Network Configuration
    // --------------------------------------------------
    EQSP32Configs cfg;

    cfg.wifiSSID     = "YourWiFiSSID";
    cfg.wifiPassword = "YourWiFiPassword";

    cfg.staticIP = "192.168.1.200";
    cfg.subnet   = "255.255.255.0";
    cfg.gateway  = "192.168.1.1";
    //cfg.dns      = "8.8.8.8";

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

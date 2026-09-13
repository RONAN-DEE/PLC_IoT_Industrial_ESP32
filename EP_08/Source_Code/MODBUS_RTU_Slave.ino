#include <EQSP32.h>
#include <ModbusRTU.h>

EQSP32 eqsp32;
ModbusRTU mb;

// RS485 pins
int rs485TX;
int rs485RX;
int rs485EN;

// Modbus slave address
const uint8_t MODBUS_ID = 1;

void setup()
{
    Serial.begin(115200);

    eqsp32.begin();

    //--------------------------------------------------
    // Configure Inputs
    //--------------------------------------------------

    eqsp32.pinMode(1, DIN);
    eqsp32.pinMode(2, DIN);
    eqsp32.pinMode(3, DIN);
    eqsp32.pinMode(4, DIN);

    eqsp32.pinMode(5, AIN);
    eqsp32.pinMode(6, AIN);
    eqsp32.pinMode(7, AIN);
    eqsp32.pinMode(8, AIN);

    //--------------------------------------------------
    // Configure Outputs
    //--------------------------------------------------

    for (int pin = 9; pin <= 16; pin++)
    {
        eqsp32.pinMode(pin, POUT);
        eqsp32.pinValue(pin, 0);
    }

    //--------------------------------------------------
    // RS485 Setup
    //--------------------------------------------------

    rs485TX = eqsp32.getPin(EQ_RS485_TX);
    rs485RX = eqsp32.getPin(EQ_RS485_RX);
    rs485EN = eqsp32.getPin(EQ_RS485_EN);

    pinMode(rs485EN, OUTPUT);
    digitalWrite(rs485EN, LOW);

    Serial2.begin(
        9600,
        SERIAL_8N1,
        rs485RX,
        rs485TX
    );

    //--------------------------------------------------
    // Modbus RTU Slave
    //--------------------------------------------------

    mb.begin(&Serial2, rs485EN);
    mb.slave(MODBUS_ID);

    // Coils (Outputs 9-16)
    for(uint16_t i = 0; i < 8; i++)
    {
        mb.addCoil(i);
    }

    // Discrete Inputs (Pins 1-4)
    for(uint16_t i = 0; i < 4; i++)
    {
        mb.addIsts(i);
    }

    // Input Registers (Pins 5-8)
    for(uint16_t i = 0; i < 4; i++)
    {
        mb.addIreg(i);
    }

    Serial.println("Modbus RTU Slave Started");
}

void loop()
{
    //--------------------------------------------------
    // Process Modbus Requests
    //--------------------------------------------------

    mb.task();

    //--------------------------------------------------
    // Update Digital Inputs
    //--------------------------------------------------

    mb.Ists(0, eqsp32.readPin(1));
    mb.Ists(1, eqsp32.readPin(2));
    mb.Ists(2, eqsp32.readPin(3));
    mb.Ists(3, eqsp32.readPin(4));

    //--------------------------------------------------
    // Update Analog Inputs
    //--------------------------------------------------

    mb.Ireg(0, eqsp32.readPin(5));
    mb.Ireg(1, eqsp32.readPin(6));
    mb.Ireg(2, eqsp32.readPin(7));
    mb.Ireg(3, eqsp32.readPin(8));

    //--------------------------------------------------
    // Drive Outputs from Modbus Coils
    //--------------------------------------------------

    eqsp32.pinValue(9,  mb.Coil(0) ? 1000 : 0);
    eqsp32.pinValue(10, mb.Coil(1) ? 1000 : 0);
    eqsp32.pinValue(11, mb.Coil(2) ? 1000 : 0);
    eqsp32.pinValue(12, mb.Coil(3) ? 1000 : 0);
    eqsp32.pinValue(13, mb.Coil(4) ? 1000 : 0);
    eqsp32.pinValue(14, mb.Coil(5) ? 1000 : 0);
    eqsp32.pinValue(15, mb.Coil(6) ? 1000 : 0);
    eqsp32.pinValue(16, mb.Coil(7) ? 1000 : 0);

    delay(10);
}
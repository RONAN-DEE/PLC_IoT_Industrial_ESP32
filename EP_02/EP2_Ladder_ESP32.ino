/*
  ESP32-S3 Sliding Door Controller
  Converted from Ladder Logic
*/

#define ESTOP_PIN          2   // I0
#define OPEN_PB_PIN        3   // I1
#define CLOSE_PB_PIN       4   // I2
#define OPEN_LIMIT_PIN     5   // I3
#define CLOSE_LIMIT_PIN    6   // I4
#define MOTION_PIN         7   // I5
#define SAFETY_PIN         8   // I6

#define OPEN_MOTOR_PIN     9   // Q0
#define CLOSE_MOTOR_PIN   10   // Q1
#define OPEN_LED_PIN      11   // Q2
#define CLOSE_LED_PIN     12   // Q3

bool openMotor = false;
bool closeMotor = false;

unsigned long openLimitTime = 0;
bool timerRunning = false;

const unsigned long AUTO_CLOSE_DELAY = 3000;

void setup()
{
    Serial.begin(115200);

    pinMode(ESTOP_PIN, INPUT_PULLUP);
    pinMode(OPEN_PB_PIN, INPUT_PULLUP);
    pinMode(CLOSE_PB_PIN, INPUT_PULLUP);
    pinMode(OPEN_LIMIT_PIN, INPUT_PULLUP);
    pinMode(CLOSE_LIMIT_PIN, INPUT_PULLUP);
    pinMode(MOTION_PIN, INPUT_PULLUP);
    pinMode(SAFETY_PIN, INPUT_PULLUP);

    pinMode(OPEN_MOTOR_PIN, OUTPUT);
    pinMode(CLOSE_MOTOR_PIN, OUTPUT);
    pinMode(OPEN_LED_PIN, OUTPUT);
    pinMode(CLOSE_LED_PIN, OUTPUT);

    stopAll();
}

void loop()
{
    bool estop      = !digitalRead(ESTOP_PIN);
    bool openPB     = !digitalRead(OPEN_PB_PIN);
    bool closePB    = !digitalRead(CLOSE_PB_PIN);
    bool openLimit  = !digitalRead(OPEN_LIMIT_PIN);
    bool closeLimit = !digitalRead(CLOSE_LIMIT_PIN);
    bool motion     = !digitalRead(MOTION_PIN);
    bool safety     = !digitalRead(SAFETY_PIN);

    //------------------------------------
    // E-STOP
    //------------------------------------
    if (estop)
    {
        stopAll();
        return;
    }

    //------------------------------------
    // OPEN COMMAND
    //------------------------------------
    bool openRequest =
        openPB ||
        motion ||
        safety;

    if (openRequest &&
        !openLimit &&
        !closeMotor)
    {
        openMotor = true;
        closeMotor = false;

        timerRunning = false;
    }

    //------------------------------------
    // OPEN LIMIT
    //------------------------------------
    if (openLimit)
    {
        openMotor = false;

        if (!timerRunning)
        {
            timerRunning = true;
            openLimitTime = millis();
        }
    }

    //------------------------------------
    // AUTO CLOSE AFTER 3 SEC
    //------------------------------------
    bool autoClose =
        timerRunning &&
        (millis() - openLimitTime >= AUTO_CLOSE_DELAY);

    //------------------------------------
    // CLOSE COMMAND
    //------------------------------------
    bool closeRequest =
        autoClose ||
        closePB ||
        closeMotor;

    if (closeRequest &&
        !closeLimit &&
        !openMotor &&
        !safety)
    {
        closeMotor = true;
    }

    //------------------------------------
    // SAFETY REOPEN
    //------------------------------------
    if (safety && closeMotor)
    {
        closeMotor = false;
        openMotor = true;

        timerRunning = false;
    }

    //------------------------------------
    // CLOSE LIMIT
    //------------------------------------
    if (closeLimit)
    {
        closeMotor = false;
        timerRunning = false;
    }

    //------------------------------------
    // MOTOR INTERLOCK
    //------------------------------------
    if (openMotor)
        closeMotor = false;

    if (closeMotor)
        openMotor = false;

    //------------------------------------
    // OUTPUTS
    //------------------------------------
    digitalWrite(OPEN_MOTOR_PIN, openMotor);
    digitalWrite(CLOSE_MOTOR_PIN, closeMotor);

    digitalWrite(OPEN_LED_PIN, openMotor);
    digitalWrite(CLOSE_LED_PIN, closeMotor);

    //------------------------------------
    // DEBUG
    //------------------------------------
    static unsigned long t = 0;
    if (millis() - t > 1000)
    {
        t = millis();

        Serial.print("OPEN=");
        Serial.print(openMotor);

        Serial.print(" CLOSE=");
        Serial.print(closeMotor);

        Serial.print(" OPEN_LM=");
        Serial.print(openLimit);

        Serial.print(" CLOSE_LM=");
        Serial.print(closeLimit);

        Serial.print(" SAFETY=");
        Serial.println(safety);
    }
}

void stopAll()
{
    openMotor = false;
    closeMotor = false;

    digitalWrite(OPEN_MOTOR_PIN, LOW);
    digitalWrite(CLOSE_MOTOR_PIN, LOW);

    digitalWrite(OPEN_LED_PIN, LOW);
    digitalWrite(CLOSE_LED_PIN, LOW);

    timerRunning = false;
}
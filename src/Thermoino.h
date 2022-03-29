#define DEBUG_LEVEL 1
#define DT_BOILER_PIN 11
#define SERVO_PIN 10
#define CIRCUIT_RELAY_PIN 9
#define DHT21_PIN 8
#define BTN_1_PIN 6
#define BTN_2_PIN 7
#define BTN_3_PIN 4
#define BTN_4_PIN 5
#define BOILER_THERM_PIN A0
#define ROOM_THERM_PIN A1

#define USE_DHT_ROOM_TEMP 1
#define USE_DT_ROOM_BOILER 1

#if 0
#define DEBUG_TASK_ENTRY(x) do { Serial.print(F(#x" - e")); Serial.println(""); } while(0)
#define DEBUG_TASK_RET(x) do { Serial.print(F(#x" - r")); Serial.println(""); } while(0)
#else
#define DEBUG_TASK_ENTRY(x)
#define DEBUG_TASK_RET(x)
#endif

#define DEBUG_SER_PRINT(x) do { Serial.print(#x": "); Serial.print(x); Serial.print(", "); } while(0)
#define DEBUG_SER_PRINT_LN(x) do { Serial.print(#x": "); Serial.print(x); Serial.println(""); } while(0)

#define MENU_POS_GATE_MANUAL 0
#define MENU_POS_SERVO_MIN 5
#define MENU_POS_SERVO_MAX 6

typedef struct ConfigMenuItem {
    const char *name;
    void* param;
    void* (*handler)(void* param, int8_t diff);
    void (*formatter)(void* param, char *buffer, int16_t maxLen, void *value);
} ConfigMenuItem_t;

struct Configuration {
    uint8_t refTempBoiler;
    uint8_t refTempBoilerIdle;
    float refTempRoom;
    uint8_t circuitRelayForced;
    int16_t servoMin;
    int16_t servoMax;
    uint8_t curveItems;
    float debounceLimitC;
    uint8_t underheatingLimit;
    uint8_t overheatingLimit;
    // linear interpolation (least squares) of the following points:
    // [boilerTemp - roomTemp, real boilerTemp - boilerTemp]
    float deltaTempPoly1;
    float deltaTempPoly0;
    float roomTempAdjust;
    float pidKp;
    float pidKi;
    float pidKd;
};

typedef struct Button {
    uint8_t pin;
    uint8_t state;
    uint8_t pressedFor;
} Button_t;

void eepromInit();
void eepromUpdate();
float readTemp(uint8_t pin);
bool processSettings();
void printStatus();
void servoSetPos(int positionPercent);
void notifyChangeState(bool immediate);
void sendCurrentStateToRelay(bool state);
void screenSaverWakeup();
#include <SPI.h>
#include "PlayingWithFusion_MAX31855_Wcorr.h"
#include "PlayingWithFusion_MAX31855_STRUCT_corr.h"
#include "avr/pgmspace.h"

#define ExternalFactor (double)0.25
#define InternalFactor (double)0.0625

#define CS0_PIN (int8_t)36
#define CS1_PIN (int8_t)35
#define CS2_PIN (int8_t)34
#define CS3_PIN (int8_t)33
#define K_type 1

template <class T> int EEPROM_write(int addr, const T& value) {
    const byte* p = (const byte*)(const void*)&value;
    int newAddr;
    for (newAddr = 0; newAddr < sizeof(value); newAddr++) {
        EEPROM.write(addr++, *p++);
    }
    return newAddr;
}//End write any value/type

template <class T> int EEPROM_read(int addr, T& value) {
    byte* p = (byte*)(void*)&value;
    int newAddr;
    for (newAddr = 0; newAddr < sizeof(value); newAddr++)
        *p++ = EEPROM.read(addr++);
    return newAddr;
}//End read any value/type

struct TestInfo {
    bool running=false;
    bool paused=false;
    bool is150=false;
    unsigned long elapsed=0;
};

struct SystemSettings {
    bool switchingEnabled = true;
    int current2=120;
    int temperature=85;
    int analogVersion=1;
};

struct AnalogPins {
    volatile uint8_t a0 = A0;
    volatile uint8_t a1 = A1;
    volatile uint8_t a2 = A2;
    volatile uint8_t a3 = A3;
    volatile uint8_t a4 = A4;
    volatile uint8_t a5 = A5;
};

#define DEBUG 0
#define outputPeriod 1000
#define runTime 50
#define BurnTime120 (unsigned long)72000000  //20hrs
#define BurnTime150 (unsigned long)25200000  //7hrs
#define VoltageLimit 68
#define ledPin 2
#define heatPin1 3
#define heatPin2 4
#define heatPin3 5
#define led150Pin 6
#define TempPin1 A6
#define TempPin2 A7
#define TempPin3 A8
#define tempHLimit 100
#define tempLLimit 0
#define tempDeviation 10  //% error allowed
#define tempOffset (0)
#define Kp 20
#define Ki 0.1
#define Kd 0
#define maxDuty 100
#define hiDuty 98
#define lowDuty 2
#define readDelay 0
#define dutyTime 500
#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include "PlayingWithFusion_MAX31855_Wcorr.h"
#include "PlayingWithFusion_MAX31855_STRUCT_corr.h"
#include "avr/pgmspace.h"

#define ExternalFactor (double)0.25
#define InternalFactor (double)0.0625



#define CS0_PIN (int8_t)33 //T4
#define CS1_PIN (int8_t)34 //T2
#define CS2_PIN (int8_t)35 //T1
#define CS3_PIN (int8_t)36 //T3
#define K_type 1

#define outputPeriod 1000
#define HeaterCount 3
#define heatPin1 3
#define heatPin2 4
#define heatPin3 5
#define led150Pin 6
#define TempPin1 A6
#define TempPin2 A8
#define TempPin3 A7
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
#define runTime 50

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
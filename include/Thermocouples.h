#pragma once
#include <Definitions.h>
#include <Thermocouple.h>


#define ExternalFactor (double)0.25
#define InternalFactor (double)0.0625

#define CS0_PIN (int8_t)36
#define CS1_PIN (int8_t)35
#define CS2_PIN (int8_t)34
#define CS3_PIN (int8_t)33
#define K_type 1

class Thermocouples{
public:
    Thermocouples(){}
    void Init();
    const TC_Data& Read(int tc);
    TC_Data* ReadAll();
private:
    Thermocouple thermocouples[4];
};
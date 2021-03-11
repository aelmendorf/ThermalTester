#pragma once
#include <Definitions.h>
#include <Thermocouple.h>


#define ExternalFactor (double)0.25
#define InternalFactor (double)0.0625
#define K_type 1

class Thermocouples{
public:
    Thermocouples(){}
    void Init();
    void Read();
    const TC_Data& GetTemp(int tc);
    TC_Data* GetAllTemp();
private:
    Thermocouple thermocouples[4];
    TC_Data data[4];
};
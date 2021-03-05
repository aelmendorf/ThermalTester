#pragma once
#include <Definitions.h>


struct TC_Data{
    double Temperature;
    double ReferenceTemp;
    String Status;
};

class Thermocouple{
public:
    Thermocouple(){};
    Thermocouple(int8_t tc);
    void Init(); 
    const TC_Data& Read();
private:
    TC_Data data;
    struct var_max31855 TC_CH;
    struct var_max31855 *ptr;
    PWFusion_MAX31855_TC  thermocouple;

};
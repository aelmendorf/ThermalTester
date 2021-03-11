#pragma once
#include <Definitions.h>


struct TC_Data{
    float Temperature;
    float ReferenceTemp;
    String Status;
    TC_Data(){
        this->Temperature=0;
        this->ReferenceTemp=0;
        this->Status="";
    }

    TC_Data& operator=(const TC_Data &rhs){
        this->Temperature=rhs.Temperature;
        this->ReferenceTemp=rhs.ReferenceTemp;
        this->Status=rhs.Status;
        return *this;
    }
};

class Thermocouple{
public:
    Thermocouple(){};
    Thermocouple(int8_t tc);
    void Init(); 
    const TC_Data& Read();
    const TC_Data& GetTemp();
private:
    TC_Data data;
    struct var_max31855 TC_CH;
    struct var_max31855 *ptr;
    PWFusion_MAX31855_TC  thermocouple;
};
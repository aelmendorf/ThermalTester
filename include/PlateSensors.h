#pragma once
#include <Definitions.h>

class PlateSensors{
public:
    PlateSensors();
    void Init();
    void Read();
    float GetTemp(const int &temp);
    float* GetAllTemp();
private:
    volatile float fWeight=0.1;
    float temperatures[3]={0,0,0};
    uint8_t tempPins[3]={A6,A8,A7};
    volatile float tempSP = 0;
    volatile float TempSetPoint;
    volatile float aValue=1024;
};
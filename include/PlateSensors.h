#pragma once
#include <Definitions.h>

class PlateSensors{
public:
    PlateSensors();
    Init();
    float* ReadAll();
    float Read(const int& temp)


private:
    volatile float fWeight;
    volatile float temperatures[3]={0,0,0};
    volatile float tempSP = 0;
    volatile float TempSetPoint;
}
#pragma once
#include <Definitions.h>



class Heaters{
public:
    Heaters(){}
    Heaters(const int& setPoint);
    void ChangeSetPoint(const int& setPoint);
    int GetSetpoint();
    void StartHeating();
    void StopHeating();
    void SetDutyCycle(const int &t1,const int &t2,const int &t3);
    void SetOutputs();
    bool Running();
    void Init();
private:
    volatile float tempSP = 0;
    volatile float tempSetpoint = 25;
    volatile unsigned long lastDutyTime = 525;
    volatile unsigned long lastRunTime = 50;
    volatile unsigned long lastOutputTime = 50;
    bool running=false;

    volatile int heaterDuty1 = 100;
    volatile float Duty1 = 100.0;
    volatile float pTerm1 = 0.0;
    volatile float err1 = 0.0;
    volatile float iTerm1 = 0.0;
    volatile float dTerm1 = 0.0;
    volatile float lastErr1 = 0.0;
    volatile int heaterDuty2 = 100;
    volatile float Duty2 = 100.0;
    volatile float pTerm2 = 0.0;
    volatile float err2 = 0.0;
    volatile float iTerm2 = 0.0;
    volatile float dTerm2 = 0.0;
    volatile float lastErr2 = 0.0;
    volatile int heaterDuty3 = 100;
    volatile float Duty3 = 100.0;
    volatile float pTerm3 = 0.0;
    volatile float err3 = 0.0;
    volatile float iTerm3 = 0.0;
    volatile float dTerm3 = 0.0;
    volatile float lastErr3 = 0.0;
    volatile float Temp1 = tempSP;
    volatile float Temp2 = tempSP;
    volatile float Temp3 = tempSP;
    volatile boolean tempsOK = false;
    volatile boolean firstRun = true;
    

};
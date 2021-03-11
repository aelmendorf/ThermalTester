#include <Heaters.h>

Heaters::Heaters(const int &setPoint){
	this->tempSetpoint=setPoint;
	this->tempSP=0;
}

bool Heaters::Running(){
	return this->running;
}

int Heaters::GetSetpoint(){
	return (int)this->tempSetpoint;
}

void Heaters::ChangeSetPoint(const int &setPoint){
	this->tempSetpoint=setPoint;
}

void Heaters::StartHeating(){
	this->tempSP=this->tempSetpoint;
	this->running=true;
}

void Heaters::StopHeating(){
	this->tempSP=0;
	this->running=false;
}

void Heaters::Init(){
    pinMode(heatPin1, OUTPUT);  digitalWrite(heatPin1, LOW);
	pinMode(heatPin2, OUTPUT);  digitalWrite(heatPin2, LOW);
	pinMode(heatPin3, OUTPUT);  digitalWrite(heatPin3, LOW);
	this->tempSP=0;
	this->heaterDuty1 = 100;
	this->Duty1 = 100.0;
	this->pTerm1 = 0.0;
	this->err1 = 0.0;
	this->iTerm1 = 0.0;
	this->dTerm1 = 0.0;
	this->lastErr1 = 0.0;
	this->heaterDuty2 = 100;
	this->Duty2 = 100.0;
	this->pTerm2 = 0.0;
	this->err2 = 0.0;
	this->iTerm2 = 0.0;
	this->dTerm2 = 0.0;
	this->lastErr2 = 0.0;
	this->heaterDuty3 = 100;
	this->Duty3 = 100.0;
	this->pTerm3 = 0.0;
	this->err3 = 0.0;
	this->iTerm3 = 0.0;
	this->dTerm3 = 0.0;
	this->lastErr3 = 0.0;
}

void Heaters::SetDutyCycle(const int &t1,const int &t2,const int &t3){
	this->Temp1=t1;
	this->Temp2=t2;
	this->Temp3=t3;

	if (firstRun) {
		lastErr1 = err1; 
		err1 = tempSP - Temp1;
		lastErr2 = err2; 
		err2 = tempSP - Temp2;
		lastErr3 = err3; 
		err3 = tempSP - Temp3;
		firstRun = false;
	}
	if (millis() >= (lastDutyTime + dutyTime)) {
		lastDutyTime = lastDutyTime + dutyTime;
		lastErr1 = err1; 
		err1 = tempSP - Temp1;

		lastErr2 = err2; 
		err2 = tempSP - Temp2;
		lastErr3 = err3; 
		err3 = tempSP - Temp3;
		if ((abs(err1) * 100 / tempSetpoint < tempDeviation) && (abs(err2) * 100 / tempSetpoint < tempDeviation) && (abs(err3) * 100 / tempSetpoint < tempDeviation)) {
			tempsOK = true;
		} else {
			tempsOK = false;
		}

		iTerm1 = iTerm1 + err1 * Ki; if (iTerm1 > 100.0) {
			iTerm1 = 100.0;
		} else if (iTerm1 < 0) {
			iTerm1 = 0;
		}
		iTerm2 = iTerm2 + err2 * Ki; if (iTerm2 > 100.0) {
			iTerm2 = 100.0;
		} else if (iTerm2 < 0) {
			iTerm2 = 0;
		}
		iTerm3 = iTerm3 + err3 * Ki; if (iTerm3 > 100.0) {
			iTerm3 = 100.0;
		} else if (iTerm3 < 0) {
			iTerm3 = 0;
		}
		pTerm1 = Kp * err1; pTerm2 = Kp * err2; pTerm3 = Kp * err3;
		dTerm1 = dTerm1 + ((Kd * (err1 - lastErr1)) - dTerm1) * 0.05;
		dTerm2 = dTerm2 + ((Kd * (err2 - lastErr2)) - dTerm2) * 0.05;
		dTerm3 = dTerm3 + ((Kd * (err3 - lastErr3)) - dTerm3) * 0.05;
		Duty1 = pTerm1 + iTerm1 + dTerm1; if (Duty1 > 100.0) {
			Duty1 = 100.0;
		} else if (Duty1 < 0.0) {
			Duty1 = 0.0;
		}
		Duty2 = pTerm2 + iTerm2 + dTerm2; if (Duty2 > 100.0) {
			Duty2 = 100.0;
		} else if (Duty2 < 0.0) {
			Duty2 = 0.0;
		}
		Duty3 = pTerm3 + iTerm3 + dTerm3; if (Duty3 > 100.0) {
			Duty3 = 100.0;
		} else if (Duty3 < 0.0) {
			Duty3 = 0.0;
		}

		if (Temp1 > tempHLimit) {
			heaterDuty1 = 0;
		} else if (Temp1 < tempLLimit) {
			heaterDuty1 = maxDuty;
		} else if (Temp1 < tempHLimit) {
			heaterDuty1 = (int(Duty1) * maxDuty) / 100;
			if ((heaterDuty1 > hiDuty) || (heaterDuty1 > maxDuty)) {
				heaterDuty1 = maxDuty;
			} else if (heaterDuty1 < lowDuty) {
				heaterDuty1 = 0;
			}
		}
		if (Temp2 > tempHLimit) {
			heaterDuty2 = 0;
		} else if (Temp2 < tempLLimit) {
			heaterDuty2 = maxDuty;
		} else if (Temp2 < tempHLimit) {
			heaterDuty2 = (int(Duty2) * maxDuty) / 100;
			if ((heaterDuty1 > hiDuty) || (heaterDuty2 > maxDuty)) {
				heaterDuty2 = maxDuty;
			} else if (heaterDuty2 < lowDuty) {
				heaterDuty2 = 0;
			}
		}
		if (Temp3 > tempHLimit) {
			heaterDuty3 = 0;
		} else if (Temp3 < tempLLimit) {
			heaterDuty3 = maxDuty;
		} else if (Temp3 < tempHLimit) {
			heaterDuty3 = (int(Duty3) * maxDuty) / 100;
			if ((heaterDuty3 > hiDuty) || (heaterDuty3 > maxDuty)) {
				heaterDuty3 = maxDuty;
			} else if (heaterDuty3 < lowDuty) {
				heaterDuty3 = 0;
			}
		}
	}
}

void Heaters::SetOutputs(){
	if (millis() >= (lastRunTime + runTime)) {
		lastRunTime = lastRunTime + runTime;
		if (millis() >= (lastOutputTime + outputPeriod)) {
			lastOutputTime = lastOutputTime + outputPeriod;
			if (heaterDuty1 > 0) {
				digitalWrite(heatPin1, HIGH);
			} else {
				digitalWrite(heatPin1, LOW);
			}
			if (heaterDuty2 > 0) {
				digitalWrite(heatPin2, HIGH);
			} else {
				digitalWrite(heatPin2, LOW);
			}
			if (heaterDuty3 > 0) {
				digitalWrite(heatPin3, HIGH);
			} else {
				digitalWrite(heatPin3, LOW);
			}
		}
		if (millis() >= (lastOutputTime + (outputPeriod / 100) * heaterDuty1)) {
			digitalWrite(heatPin1, LOW);
		}
		if (millis() >= (lastOutputTime + (outputPeriod / 100) * heaterDuty2)) {
			digitalWrite(heatPin2, LOW);
		}
		if (millis() >= (lastOutputTime + (outputPeriod / 100) * heaterDuty3)) {
			digitalWrite(heatPin3, LOW);
		}
	}
}


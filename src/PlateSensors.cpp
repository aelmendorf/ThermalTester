#include <PlateSensors.h>


PlateSensors::PlateSensors(){

}

void PlateSensors::Init(){
    pinMode(TempPin1, INPUT);
	pinMode(TempPin2, INPUT);
	pinMode(TempPin3, INPUT);
    aValue = analogRead(TempPin1);
	this->temperatures[0] = (((float)(aValue) * 500.0) / 1024.0);

	aValue = analogRead(TempPin2);
	this->temperatures[1] = (((float)(aValue) * 500.0) / 1024.0);

	aValue = analogRead(TempPin3);
	this->temperatures[2] = (((float)(aValue) * 500.0) / 1024.0);
}

float* PlateSensors::ReadAll(){

}

float PlateSensors::Read(const int& temp){
    	aValue = analogRead(TempPin1);
		delay(readDelay);
        float Temp1=&this->temperatures[0];
		Temp1 = Temp1 + ((((float)(aValue) * 500.0) / 1024.0) + tempOffset - Temp1) * fWeight;

		aValue = analogRead(TempPin2);
		delay(readDelay);

		Temp2 = Temp2 + ((((float)(aValue) * 500.0) / 1024.0) + tempOffset - Temp2) * fWeight;

		aValue = analogRead(TempPin3); delay(readDelay);

		Temp3 = Temp3 + ((((float)(aValue) * 500.0) / 1024.0) + tempOffset - Temp3) * fWeight;
}
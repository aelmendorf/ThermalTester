#include <PlateSensors.h>


PlateSensors::PlateSensors(){

}

void PlateSensors::Init(){
    pinMode(TempPin1, INPUT);
	pinMode(TempPin2, INPUT);
	pinMode(TempPin3, INPUT);

	for(int i=0;i<3;i++){
		switch(i){
			case 0:
				aValue = analogRead(TempPin1);
				break;
			case 1:
				aValue = analogRead(TempPin3);
				break;
			case 2:
				aValue = analogRead(TempPin1);
				break;
			default:
				aValue=0;
				break;
		}
		
		this->temperatures[i] = (((float)(aValue) * 500.0) / 1024.0);
	}

    /*aValue = analogRead(TempPin1);
	this->temperatures[0] = (((float)(aValue) * 500.0) / 1024.0);

	aValue = analogRead(TempPin2);
	this->temperatures[1] = (((float)(aValue) * 500.0) / 1024.0);

	aValue = analogRead(TempPin3);
	this->temperatures[2] = (((float)(aValue) * 500.0) / 1024.0);*/
}

float PlateSensors::GetTemp(const int &temp){
	return this->temperatures[temp];
}

float* PlateSensors::GetAllTemp(){
	static float values[3];
	values[0]=this->temperatures[0];
	values[1]=this->temperatures[1];
	values[2]=this->temperatures[2];
	return values;
}

void PlateSensors::Read(){
	for(int i=0;i<3;i++){
		switch(i){
			case 0:
				aValue = analogRead(TempPin1);
				break;
			case 1:
				aValue = analogRead(TempPin3);
				break;
			case 2:
				aValue = analogRead(TempPin1);
				break;
			default:
				aValue=0;
				break;
		}
		//delay(readDelay);
		this->temperatures[i] = this->temperatures[i] + ((((float)(aValue) * 500.0) / 1024.0) + tempOffset - this->temperatures[i]) * fWeight;
	}
}
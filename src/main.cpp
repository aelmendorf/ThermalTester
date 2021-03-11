#include <Definitions.h>
#include <Thermocouples.h>
#include <Heaters.h>
#include <PlateSensors.h>

Thermocouples thermocouples;
Heaters heaters;
PlateSensors plateSensors;

float* plateTemps;
TC_Data* deviceTemps;
volatile unsigned long lastReadTime = 0;
volatile unsigned long comTime = 100;
volatile unsigned long lastComTime = 50;
volatile unsigned long readTime = 0;
volatile boolean boolArray[100];
volatile float realArray[100];
String textArray[100];
volatile boolean limitArray[10];

void(*resetFunc) (void) = 0; //declare reset function @ address 0

void readInputs();
void sendComs_v2();
void serialEvent();

void setup(){
  Serial.begin(38400);
  thermocouples.Init();
  plateSensors.Init();
  heaters.Init();
  for(int i=0;i<100;i++){
    realArray[i]=0;
  }

  for(int i=0;i<100;i++){
    boolArray[i]=0;
  }
  
}

void loop(){
  readInputs();
  heaters.SetDutyCycle(plateSensors.GetTemp(0),plateSensors.GetTemp(1),plateSensors.GetTemp(2));
  heaters.SetOutputs();
  sendComs_v2();
}

void readInputs(){
  	if (millis() >= (lastReadTime + readTime)) {
        lastReadTime = lastReadTime + readTime;
        plateSensors.Read();
        thermocouples.Read();
        boolArray[0] = false;
        boolArray[1] = digitalRead(heatPin1);
        boolArray[2] = digitalRead(heatPin2);
        boolArray[3] = digitalRead(heatPin3);
        boolArray[4] = false;
        
        deviceTemps=thermocouples.GetAllTemp();
        realArray[0] = (*(deviceTemps+0)).Temperature;
        realArray[1] = (*(deviceTemps+1)).Temperature;//T2
        realArray[2] = (*(deviceTemps+2)).Temperature;//T1
        realArray[3] = (*(deviceTemps+3)).Temperature;;//T3
        realArray[4] = 0;
        realArray[5] = 0;
        realArray[6]=plateSensors.GetTemp(0);
        realArray[7]=plateSensors.GetTemp(1);
        realArray[8]=plateSensors.GetTemp(2);
        //plateTemps=plateSensors.GetAllTemp();
        //realArray[6] = *(plateTemps+0); //T1
        //realArray[7] = *(plateTemps+1); //T3
        //realArray[8] = *(plateTemps+2); //T2
        realArray[10] = heaters.GetSetpoint();
        realArray[11] = 0;
    }
}

void sendComs_v2() {
	if (millis() >= (lastComTime + comTime)) {
		lastComTime = lastComTime + comTime;
    String buffer = "";
    for (int x = 0; x <= 12; x++) {
      buffer += "[R" + (String)x + "]{" + (String)realArray[x] + "}";
    }
    for (int x = 0; x <= 4; x++) {
      buffer += "[B" + (String)x + "]{" + (String)boolArray[x] + "}";
    }
    Serial.println(buffer);
  }

	/*if (millis() >= (lastEEpromTime + eepromDelay)) {
		lastEEpromTime = millis();
		runningTest.elapsed = burnInTimeMillis;
		runningTest.is150 = is150on;
		runningTest.running = boolArray[0];
		EEPROM_write(0, runningTest);
	}*/
}

void serialEvent() {
	byte inByte1 = 0;
	word buff = 0;
	while (Serial.available()) {
		inByte1 = (byte)Serial.read();
   if ((char)inByte1 == 'R') {
			Serial.println("[T]{Resetting Device}");
			delay(1000);
			resetFunc();
		}else if (((char)inByte1 == 'H')) {
      if(!heaters.Running()){
        heaters.StartHeating();
        Serial.println("[T]{Setting Temperature to " + String(heaters.GetSetpoint()) + "}");
      }else{
        heaters.StopHeating();
        Serial.println("[T]{Setting Temperature to 0}");
      }
		} else if(((char)inByte1=='U')){
        int th = ((char)Serial.read()) - '0';         //2
        int tt = ((char)Serial.read()) - '0';		  //3
        int to = ((char)Serial.read()) - '0';		  //4
        int newTemp= (th * 100) + (tt * 10) + to;
        heaters.ChangeSetPoint(newTemp);
        Serial.println("[T]{SetPoint Changed to " + String(newTemp) + "}");
    }
	}
}
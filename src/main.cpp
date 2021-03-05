#include <Arduino.h>
#include <Thermocouples.h>

Thermocouples thermocouples;

void setup(){
  Serial.begin(115200);
  thermocouples.Init();
}

void loop(){
  delay(1000);
  TC_Data* data=thermocouples.ReadAll();
  for(int i=0;i<4;i++){
    Serial.print("TC[");
    Serial.print(i);
    Serial.print("]=");
    Serial.print(data[i].Temperature);
    Serial.println();
  }
}


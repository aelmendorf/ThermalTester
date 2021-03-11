#include <Thermocouples.h>

/**************************************************************************
* Circuit:
*    Arduino Uno   Arduino Mega  -->  SEN-30002/3/4
*    MISO: pin 12  MISO: pin 50  -->  SDO (must not be changed for hardware SPI)
*    SCK:  pin 13  SCK:  pin 52  -->  SCLK (must not be changed for hardware SPI)
*    CS3:  pin  7         36     -->  CS3 T3
*    CS2:  pin  8         35     -->  CS2 T1
*    CS1:  pin  9         34     -->  CS1 T2
*    CS0:  pin  10        33     -->  CS0 T4
***************************************************************************/

void Thermocouples::Init(){
      // setup for the the SPI library:
  SPI.begin();                        // begin SPI
  SPI.setDataMode(SPI_MODE1);         // MAX31865 is a Mode 1 device
                                      //    --> clock starts low, read on rising edge
  pinMode(CS0_PIN, OUTPUT);
  pinMode(CS1_PIN, OUTPUT);
  pinMode(CS2_PIN, OUTPUT);
  pinMode(CS3_PIN, OUTPUT);
  this->thermocouples[0]=Thermocouple(CS1_PIN);
  this->thermocouples[1]=Thermocouple(CS2_PIN);
  this->thermocouples[2]=Thermocouple(CS0_PIN);
  this->thermocouples[3]=Thermocouple(CS3_PIN);

  for(int i=0;i<4;i++){
      this->thermocouples[i].Init();
  }
    
}

void Thermocouples::Read(){
    for(int i=0;i<4;i++){
        this->data[i]=this->thermocouples[i].Read();
    }
}

const TC_Data& Thermocouples::GetTemp(int  tc){
    return this->data[tc];
}

TC_Data* Thermocouples::GetAllTemp(){
    static TC_Data values[4];
    values[0]=this->data[0];
    values[1]=this->data[1];
    values[2]=this->data[2];
    values[3]=this->data[3];
    return values;
}
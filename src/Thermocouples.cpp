#include <Thermocouples.h>

/**************************************************************************
* Circuit:
*    Arduino Uno   Arduino Mega  -->  SEN-30002/3/4
*    MISO: pin 12  MISO: pin 50  -->  SDO (must not be changed for hardware SPI)
*    SCK:  pin 13  SCK:  pin 52  -->  SCLK (must not be changed for hardware SPI)
*    CS3:  pin  7         ''     -->  CS3
*    CS2:  pin  8         ''     -->  CS2
*    CS1:  pin  9         ''     -->  CS1
*    CS0:  pin  10        ''     -->  CS0
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
  this->thermocouples[0]=Thermocouple(CS0_PIN);
  this->thermocouples[1]=Thermocouple(CS1_PIN);
  this->thermocouples[2]=Thermocouple(CS2_PIN);
  this->thermocouples[3]=Thermocouple(CS3_PIN);

  for(int i=0;i<4;i++){
      this->thermocouples[i].Init();
  }
    
}

const TC_Data& Thermocouples::Read(int  tc){
    return this->thermocouples[tc].Read();
}

TC_Data* Thermocouples::ReadAll(){
    static TC_Data data[4];
    
    for(int i=0;i<4;i++){
        data[i]=this->thermocouples[i].Read();
    }
    return data;
}
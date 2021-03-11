
#include <Thermocouple.h>

Thermocouple::Thermocouple(int8_t tc){
    this->thermocouple=PWFusion_MAX31855_TC(tc);
}

void Thermocouple::Init(){
    this->TC_CH.value=0;
    this->TC_CH.ref_jcn_temp=0;
    this->TC_CH.status=0;
    this->TC_CH.tc_type=K_type;
    this->TC_CH.Tcorr=0;
}

const TC_Data& Thermocouple::GetTemp(){
    return this->data;
}

const TC_Data& Thermocouple::Read(){  
    this->ptr=&this->TC_CH;
    this->thermocouple.MAX31855_update(this->ptr);
    this->data.ReferenceTemp=(double)this->TC_CH.ref_jcn_temp*0.0625;
    this->data.Temperature=(double)this->TC_CH.value*0.25;
    if(0x00==this->TC_CH.status){
        this->data.Status="Okay";
        return this->data;
    }else if(0x01==this->TC_CH.status){
        this->data.Status="OPEN";
        return this->data;
    }else if(0x02==this->TC_CH.status){
        this->data.Status="SHORT TO GND";
        return this->data;
    }else if(0x03==this->TC_CH.status){
        this->data.Status="SHORT TO Vcc";
        return this->data;
    }
    return this->data;
}
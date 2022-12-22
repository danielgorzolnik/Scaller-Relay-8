#include <Arduino.h>
#include "relay.h"
#include <ScallerCom.h>

Relay::Relay(uint8_t pin){
    this->pin = pin;
    this->inverted = 0;
    this->change_readed = 1;
    pinMode(this->pin, OUTPUT);
    setState(0);
}

void Relay::setState(uint8_t state){
    this->state = state;
    if (this->inverted) digitalWrite(this->pin, !this->state);
    else digitalWrite(this->pin, this->state);
}

void Relay::toggleState(){
    this->state = !this->state;
    setState(this->state);
}

void Relay::setChanged(){
    this->change_readed = 0;
}

void Relay::setReaded(){
    this->change_readed = 1;
}

uint8_t Relay::readState(){
    this->change_readed = 1;
    return this->state;
}

RELAY_STATUS Relay::getStatusStruct(){
    RELAY_STATUS status;
    status.status = this->state;
    status.invert = this->inverted;
    status.changed = !this->change_readed;
    return status;
}
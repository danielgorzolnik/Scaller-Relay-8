#include <Arduino.h>
#include <ScallerCom.h>
#include <EEPROM.h>
#include "relay.h"
#include "../eeprom_map.h"

Relay::Relay(uint8_t pin, uint8_t id){
    this->id = id;
    this->pin = pin;
    this->inverted = 0;
    this->change_readed = 1;
    pinMode(this->pin, OUTPUT);
    setState(EEPROM.read(EEPROM_RELAY_STATE + this->id));
}

void Relay::setState(uint8_t state){
    this->state = state;
    if (this->inverted) digitalWrite(this->pin, !this->state);
    else digitalWrite(this->pin, this->state);
    EEPROM.update(this->id, this->state);
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
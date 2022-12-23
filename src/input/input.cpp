#include <Arduino.h>
#include <ScallerCom.h>
#include <EEPROM.h>
#include "input.h"
#include "../eeprom_map.h"

Input::Input(uint8_t pin, uint8_t id){
    this->id = id;
    this->pin = pin;
    this->inverted = 0;
    this->change_readed = 1;
    pinMode(this->pin, INPUT_PULLUP);
    this->state = getState();

    //////////////////////
    // LOAD FROM EEPROM //
    //////////////////////
    //button type
    uint8_t eeprom_button_type = EEPROM.read(EEPROM_INPUT_TYPE + id);
    if (eeprom_button_type > 1) this->button_type = button_switch;
    else this-> button_type = eeprom_button_type;

    //relay trigger
    for (byte i=0; i<3; i++){
        uint8_t eeprom_relay = EEPROM.read(EEPROM_INPUT_RELAYS + (id * 3) + id);
        if (eeprom_relay > 7) eeprom_relay = 0xff;
        this->relay[i] = eeprom_relay;
    }
}

bool Input::getState(){
    bool state = digitalRead(this->pin);
    if (!this->inverted) return !state;
    else return state;
}

void Input::setChanged(){
    this->change_readed = 0;
}

void Input::setReaded(){
    this->change_readed = 1;
}

void Input::tick(){
    bool new_state = getState();
    if (this->button_type == button_switch){
        if (new_state != this->state){
            this->state = new_state;
            setChanged();
        }
    }
    else {
        if (!this->state && new_state && !button_pushed){
            button_pushed = true;
        }
        else if (this->state && !new_state && button_pushed){
            this->state = new_state;
            button_pushed = false;
            setChanged();
        }
        else if (!this->state && !new_state && button_pushed){
            button_pushed = false;
        }
    }
}   

uint8_t Input::readState(){
    this->change_readed = 1;
    return this->state;
}

INPUT_STATUS Input::getStatusStruct(){
    INPUT_STATUS status;
    status.status = this->state;
    status.invert = this->inverted;
    status.changed = !this->change_readed;
    status.type = this->button_type;
    for (byte i=0; i<3; i++){
        status.relay[i] = this->relay[i];
    }
    return status;
}
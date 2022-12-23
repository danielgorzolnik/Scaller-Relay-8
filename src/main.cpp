#include <Arduino.h>
#include <EEPROM.h>
#include <ScallerCom.h>
#include "scallercom_read.h" 
#include "relay/relay.h"
#include "input/input.h"
#include "config.h"
#include "eeprom_map.h"

ScallerCom scallercom;

Relay relay_1(pin_relay_1, 0);
Relay relay_2(pin_relay_2, 1);
Relay relay_3(pin_relay_3, 2);
Relay relay_4(pin_relay_4, 3);
Relay relay_5(pin_relay_5, 4);
Relay relay_6(pin_relay_6, 5);
Relay relay_7(pin_relay_7, 6);
Relay relay_8(pin_relay_8, 7);

Relay *relays[8] = {
  &relay_1,
  &relay_2,
  &relay_3,
  &relay_4,
  &relay_5,
  &relay_6,
  &relay_7,
  &relay_8,
};
 
Input input_1(pin_input_1, 0);
Input input_2(pin_input_2, 1);
Input input_3(pin_input_3, 2);
Input input_4(pin_input_4, 3);
Input input_5(pin_input_5, 4);
Input input_6(pin_input_6, 5);
Input input_7(pin_input_7, 6);
Input input_8(pin_input_8, 7);

Input *inputs[8] = {
  &input_1,
  &input_2,
  &input_3,
  &input_4,
  &input_5,
  &input_6,
  &input_7,
  &input_8,
};

void loadFromEeprom(){
  //relay
  for (byte i=0; i<8; i++){
  }
}

void setup() {
  scallercom.init();
  scallercom.setMode(MODE_SLAVE);
  scallercom.setType(RELAY_8);
  scallercom.setAddress(0x01);
  scallercom.set485pin(pin_dir_rs485);
  scallercom.add_callback(&scallercomCallback);

  pinMode(pin_uc_reset, INPUT);
  digitalWrite(pin_uc_reset, HIGH);
}

void loop() {
  scallercom.scallercom_read();
  for (byte i=0; i<8; i++){
    inputs[i]->tick();
  }
}
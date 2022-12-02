#include <Arduino.h>
#include <ScallerCom.h>
#include "scallercom_read.h" 
#include "relay/relay.h"
#include "config.h"

ScallerCom scallercom;

Relay relay_1(pin_relay_1);
Relay relay_2(pin_relay_2);
Relay relay_3(pin_relay_3);
Relay relay_4(pin_relay_4);
Relay relay_5(pin_relay_5);
Relay relay_6(pin_relay_6);
Relay relay_7(pin_relay_7);
Relay relay_8(pin_relay_8);

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
 
void setup() {
  scallercom.init();
  scallercom.setMode(MODE_SLAVE);
  scallercom.setType(RELAY_8);
  scallercom.setAddress(0x01);
  scallercom.add_callback(&scallercomCallback);
}

void loop() {
  scallercom.scallercom_read();
}
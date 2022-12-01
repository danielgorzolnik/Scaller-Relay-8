#include <Arduino.h>
#include <ScallerCom.h>

ScallerCom scallercom;

struct testowa{
  uint64_t value;
  uint32_t value2;
};

testowa test;

void forocom_module_setup(scaller_frame *Scaller_Frame){
  Scaller_Frame->data_size = sizeof(struct testowa);

  uint8_t* structPtr = (uint8_t*) &test;
  for (byte i= 0; i < Scaller_Frame->data_size; i++){
    *structPtr = Scaller_Frame->data[i];
    structPtr++;
  }

  structPtr = (uint8_t*) &test;
  for (byte i= 0; i < Scaller_Frame->data_size; i++){
    Scaller_Frame->data[i] = *structPtr++;
  }

  digitalWrite(13, !digitalRead(13));
}

void setup() {
  scallercom.init();
  scallercom.add_callback(&forocom_module_setup);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  scallercom.scallercom_read();
}
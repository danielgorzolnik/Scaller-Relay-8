#include <Arduino.h>
#include <ScallerCom.h>
#include <ScallerComFunctions.h>
#include "scallercom_read.h"
#include "config.h"

extern ScallerCom scallercom;

void structToFrame(scaller_frame *Scaller_Frame, uint8_t* struct_ptr, uint8_t struct_size){
    for (byte i= 0; i < Scaller_Frame->data_size; i++){
        Scaller_Frame->data[i] = *struct_ptr++;
        Scaller_Frame->data_size = struct_size;
    }
}

void frameToStruct(scaller_frame *Scaller_Frame, uint8_t* struct_ptr, uint8_t struct_size){
    for (byte i= 0; i < Scaller_Frame->data_size; i++){
        *struct_ptr = Scaller_Frame->data[i];
        struct_ptr++;
    }
}

void scallercomCallback(scaller_frame *Scaller_Frame){
    uint16_t function = Scaller_Frame->function;
    uint8_t data_size = Scaller_Frame->data_size;

    //ACK
    if (function == 0x01){
        ACK_DATA ack_data;
        ack_data.address = scallercom.module_address;
        ack_data.type = scallercom.device_type;
        ack_data.version = SOFT_VERSION;

        structToFrame(Scaller_Frame, (uint8_t*) &ack_data, sizeof(struct ACK_DATA));
    }

    // uint8_t* structPtr = (uint8_t*) &test;
    // for (byte i= 0; i < Scaller_Frame->data_size; i++){
    //     *structPtr = Scaller_Frame->data[i];
    //     structPtr++;
    // }

    // structPtr = (uint8_t*) &test;
    // for (byte i= 0; i < Scaller_Frame->data_size; i++){
    //     Scaller_Frame->data[i] = *structPtr++;
    // }
}
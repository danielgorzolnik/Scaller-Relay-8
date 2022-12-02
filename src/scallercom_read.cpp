#include <Arduino.h>
#include <ScallerCom.h>
#include <ScallerComFunctions.h>
#include "scallercom_read.h"
#include "config.h"
#include "relay/relay.h"

extern ScallerCom scallercom;
extern Relay *relays[];

void structToFrame(scaller_frame *Scaller_Frame, uint8_t* struct_ptr, uint8_t struct_size, uint8_t data_offset = 0){
    for (byte i= 0; i < struct_size; i++){
        Scaller_Frame->data[i + data_offset] = *struct_ptr++;
    }
    Scaller_Frame->data_size = Scaller_Frame->data_size + struct_size;
}

void frameToStruct(scaller_frame *Scaller_Frame, uint8_t* struct_ptr, uint8_t struct_size){
    for (byte i= 0; i < struct_size; i++){
        *struct_ptr = Scaller_Frame->data[i];
        struct_ptr++;
    }
}

void scallercomCallback(scaller_frame *Scaller_Frame){
    uint16_t function = Scaller_Frame->function;
    uint8_t data_size = Scaller_Frame->data_size;
    Scaller_Frame->data_size = 0;

    //ACK
    if (function == 0x01){
        ACK_DATA ack_data;
        ack_data.address = scallercom.module_address;
        ack_data.type = scallercom.device_type;
        ack_data.version = SOFT_VERSION;

        
        structToFrame(Scaller_Frame, (uint8_t*) &ack_data, sizeof(struct ACK_DATA), 0);
    }

    else if (function == FUNCTION_GET_STATUS){
        Scaller_Frame->data_size = 0;
        for (byte i=0; i<8; i++){
            RELAY_STATUS status = relays[i]->getStatusStruct();
            structToFrame(Scaller_Frame, (uint8_t*) &status, sizeof(struct RELAY_STATUS), i * sizeof(struct RELAY_STATUS));
        }
    }

    else {
        Scaller_Frame->data_size = data_size;
    }
}
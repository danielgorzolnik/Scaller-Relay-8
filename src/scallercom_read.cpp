#include <Arduino.h>
#include <ScallerCom.h>
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

void badRequest(scaller_frame *Scaller_Frame){
    Scaller_Frame->function = FUNCTION_BAD_PARAM;
    Scaller_Frame->data_size = 0;
}

void scallercomCallback(scaller_frame *Scaller_Frame){
    uint16_t function = Scaller_Frame->function;
    uint8_t data_size = Scaller_Frame->data_size;
    Scaller_Frame->data_size = 0;

    //ACK
    //MODULE INFO
    if (function == FUNCTION_ACK || function == FUNCTION_MODULE_INFO){
        ACK_DATA ack_data;
        ack_data.address = scallercom.module_address;
        ack_data.type = scallercom.device_type;
        ack_data.version = SOFT_VERSION;
        structToFrame(Scaller_Frame, (uint8_t*) &ack_data, sizeof(struct ACK_DATA), 0);
    }

    //RESET uC
    else if (function == FUNCTION_UC_RESET){
        _delay_ms(200);
        pinMode(pin_uc_reset, OUTPUT);
        digitalWrite(pin_uc_reset, 0);
    }
    
    //ALL STATUS
    else if (function == FUNCTION_GET_STATUS){
        Scaller_Frame->data_size = 0;
        for (byte i=0; i<8; i++){
            RELAY_STATUS status = relays[i]->getStatusStruct();
            relays[i]->setReaded();
            structToFrame(Scaller_Frame, (uint8_t*) &status, sizeof(struct RELAY_STATUS), i * sizeof(struct RELAY_STATUS));
        }
    }

    //GET RELAY STATUS
    else if (function == FUNCTION_GET_RELAY){
        if (data_size == 1){
            if(Scaller_Frame->data[0] < 8){
                Scaller_Frame->data[0] = relays[Scaller_Frame->data[0]]->readState();
                Scaller_Frame->data_size = 1;
            }
            else badRequest(Scaller_Frame);
        }
        else badRequest(Scaller_Frame);
    }

    //SET RELAY STATUS
    else if (function == FUNCTION_SET_RELAY){
        if (data_size == 2){
            if(Scaller_Frame->data[0] < 8){
                relays[Scaller_Frame->data[0]]->setState(Scaller_Frame->data[1]);
                Scaller_Frame->function = FUNCTION_OK;
                Scaller_Frame->data_size = 0;
            }
            else badRequest(Scaller_Frame);
        }
        else badRequest(Scaller_Frame);
    }

    else {
        Scaller_Frame->function = FUNCTION_FUNCTION_NOT_FOUND;
        Scaller_Frame->data_size = 0;
    }
}
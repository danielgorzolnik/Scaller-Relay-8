#ifndef RELAY_h
#define RELAY_h
#include <Arduino.h>
#include <ScallerCom.h>

class Relay {
    private:
        uint8_t pin;
    public:
        Relay(uint8_t);
        uint8_t state;
        uint8_t change_readed;
        uint8_t inverted;
        uint8_t readState();
        void setState(uint8_t);
        void toggleState();
        void setChanged();
        RELAY_STATUS getStatusStruct();
};

#endif
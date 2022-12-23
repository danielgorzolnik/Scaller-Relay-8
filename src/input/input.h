#ifndef INPUT_h
#define INPUT_h
#include <Arduino.h>
#include <ScallerCom.h>

enum BUTTON_TYPES {
    button_push,
    button_switch
};

class Input {
    private:
        uint8_t pin;
        uint8_t id;
        bool button_pushed;
        bool getState();
    public:
        Input(uint8_t, uint8_t);
        uint8_t state;
        uint8_t change_readed;
        uint8_t local_change_readed;
        uint8_t inverted;
        uint8_t button_type;
        uint8_t relay[3];
        uint8_t readState();
        void setChanged();
        void setReaded();
        void tick();
        INPUT_STATUS getStatusStruct();
};

#endif
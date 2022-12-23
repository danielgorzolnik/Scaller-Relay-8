#define SOFT_VERSION 0xabcdef

//pins

//relays
#define pin_relay_1 A1
#define pin_relay_2 A0
#define pin_relay_3 10
#define pin_relay_4 9
#define pin_relay_5 8
#define pin_relay_6 7
#define pin_relay_7 6
#define pin_relay_8 5

//input
#define pin_input_1 4
#define pin_input_2 3
#define pin_input_3 A4
#define pin_input_4 A3
#define pin_input_5 A2
#define pin_input_6 13
#define pin_input_7 12
#define pin_input_8 11

//address select pin
#define pin_address A7

//uC self reset
#define pin_uc_reset A5

//max485 dir pin
#define pin_dir_rs485 2


// ADDRESS SWITCH
//
// NONE - 5v (1023)
// SW1 - 0V (0)
// SW2 - 1k5 i 2k7 = 3,21V (657)
// SW3 - 1k5 i 6k (2k7 + 3k3) = 4V (818)
// SW4 - 1k5 i 11k6 (2k7 + 3k3 + 5k6) = 4.42 (904)
// SW5 - 1k5 i 17k2 (2k7 + 3k3 + 5k6 + 5k6) = 4,59V (939)
#define ADC_TOLEANCE 15
#define ADDR_SW_NONE 1023
#define ADDR_SW_1 0
#define ADDR_SW_2 657
#define ADDR_SW_3 818
#define ADDR_SW_4 904
#define ADDR_SW_5 939
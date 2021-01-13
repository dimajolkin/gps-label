#pragma once 

#define TFT_CS        PB9
#define TFT_DC        PB7
#define TFT_RST       PB8

#define RADIO_CE       PB10
#define RADIO_CSP      PB11

#define GPO_GPS_TX PA9
#define GPO_GPS_RX PA10

#define BTN_RIGHT PA1
#define BTN_LEFT  PA2
#define BTN_UP  PA3
#define BTN_DOWN  PA4
#define BTN_OK  PA0

#define BTN_PIN_COUNT 5
#define BACKGROUND_COLOR ST77XX_BLACK

#define DEBUG 1
#define SERIAL_BAUND 9600

const uint8_t BUTTON_PINS[BTN_PIN_COUNT] = {
   BTN_RIGHT,
   BTN_LEFT,
   BTN_UP,
   BTN_DOWN,
   BTN_OK,
};
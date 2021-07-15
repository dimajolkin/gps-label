#pragma once

#define TFT_CS PB_10
#define TFT_RST PB_1
#define TFT_DC PB_0

#define RADIO_SPI_MOSI PB_15
#define RADIO_SPI_MISO PB_14
#define RADIO_SPI_SCK  PB_13
#define RADIO_CE       PA_8
#define RADIO_CSP      PA_9

// #define GPO_GPS_TX PA9
// #define GPO_GPS_RX PA10

#define BTN_RIGHT PA_1
#define BTN_LEFT  PA_4
#define BTN_UP  PC_15
#define BTN_DOWN  PA_3
#define BTN_OK  PC_14
#define BTN_KEY  PA_0

// #define BTN_PIN_COUNT 5
#define BACKGROUND_COLOR ST7735_BLACK

// #define DEBUG 1
// #define SERIAL_BAUND 9600

// const uint8_t BUTTON_PINS[BTN_PIN_COUNT] = {
//    BTN_RIGHT,
//    BTN_LEFT,
//    BTN_UP,
//    BTN_DOWN,
//    BTN_OK,
// };
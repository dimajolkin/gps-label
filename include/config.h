#define TFT_CS        2
#define TFT_DC        3 
#define TFT_RST       4

#define RADIO_CE       10
#define RADIO_CSP      9

#define BTN_PIN_COUNT 5
#define BTN_RIGHT A1
#define BTN_LEFT  A2
#define BTN_UP  A3
#define BTN_DOWN  A4
#define BTN_OK  A0

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
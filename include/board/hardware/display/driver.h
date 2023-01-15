#include <Adafruit_ST7735.h>

// #define DISPLAY_BUFFER_SEZE  240*320
// uint8_t _display_buffer[DISPLAY_BUFFER_SEZE];

class DisplayDriver: public Adafruit_ST7735 {
    public:
    DisplayDriver(PinName mosi, PinName miso, PinName sck, PinName CS, PinName RS, PinName RST)
        : Adafruit_ST7735(mosi, miso, sck, CS, RS, RST) {
            // memset(_display_buffer, 0, sizeof(_display_buffer));
        }

    
    void drawPixel(int16_t x, int16_t y, uint16_t color) {
        // uint8_t _c = 0;
        // if (color == ST7735_BLACK) {
        //     _c = 255;
        // } else if (color == ST7735_WHITE) {
        //     _c = 1;
        // } else if (color == ST7735_GREEN) {
        //     _c = 2;
        // } if (color == ST7735_BLUE) {
        //     _c = 3;
        // }

        // // #override
        // if (_display_buffer[x * y] == _c) {
        //     return;
        // }

        Adafruit_ST7735::drawPixel(x, y, color);
        // _display_buffer[x * y] = _c;
    }
};
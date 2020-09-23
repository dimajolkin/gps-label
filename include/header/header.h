
class Header {
    private:
        Adafruit_ST7735 *display;
        uint8_t power = 10;
        uint8_t tmp_power = 10;
        const uint8_t startX = 100;
        const uint8_t startY = 0;
    public:
        Header(Adafruit_ST7735 *display): display(display) {}

        void setup() {
            renderPower(startX, startY);
        }

        uint8_t getDy() {
            return 11;
        }

        void renderPower(uint8_t x, uint8_t y) {
            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->print(10);
            display->print("%");
            display->drawLine(x + 22, y, x + 24, y, ST7735_WHITE);
            display->fillRect(x + 20, y + 1, 7, 9, ST7735_WHITE);

            display->drawLine(
                0, getDy(),
                display->width(), getDy(),
                ST7735_WHITE
            );
        }

        uint8_t readPower() {
            return 10;
        }

        void check() {
            // tmp_power = readPower();
            // if (tmp_power != power) {
            //     power = tmp_power;
            //     //renderPower(startX, startY);
            // }
        }
};

class Header: public Renderer {
    private:
        Server *server;
        uint8_t power = 10;
        uint8_t tmp_power = 10;

        uint16_t memory = 0;
        uint16_t tmp_memory = 0;

        const uint8_t startX = 100;
        const uint8_t startY = 0;

        unsigned int timing;
    public:
        Header(Adafruit_ST7735 *display): Renderer(display) {}

        void configure(Container *container) {
            server = container->getServer();
        }

        uint8_t getDy() {
            return 11;
        }

        void renderPower() {
            uint8_t x = 100;
            uint8_t y = 0;
            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->print(power);
            display->print(F("%"));

            display->drawLine(x + 22, y, x + 24, y, ST7735_WHITE);
            display->fillRect(x + 20, y + 1, 7, 9, ST7735_WHITE);
        }

        void renderMemory() {
            uint8_t x = 10;
            uint8_t y = 0;
            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->setTextWrap(true);
            display->fillRect(x, y + 1, 30, 10, BACKGROUND_COLOR);
            display->print(memory);
            display->print(F("b"));
        }

        void update() {
            if (millis() - timing > 1000) {
                timing = millis(); 
                tmp_power = server->getPower();
                tmp_memory = server->getAvailableMemory();
            }

            if (tmp_memory != memory) {
                memory = tmp_memory;
                renderMemory();
            }

            if (tmp_power != power) {
                power = tmp_power;
                renderPower();
            }
        }

        void render() {
            renderMemory();
            renderPower();
             display->drawLine(
                0, getDy(),
                display->width(), getDy(),
                ST7735_WHITE
            );
        }
};
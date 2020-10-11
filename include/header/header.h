#pragma once

class Header: public Renderer {
    private:
        Server *server;
        uint8_t power = 0;
        uint8_t tmp_power = 0;

        uint16_t memory = 0;
        uint16_t tmp_memory = 0;

        const uint8_t startX = 100;
        const uint8_t startY = 0;

        unsigned int timing;
    public:
        Header(Display *display): Renderer(display) {}

        void configure(Container *container) {
            server = container->getServer();
        }

        uint8_t getDy() {
            return 11;
        }

        void renderPower() {
            uint8_t x = 100;
            uint8_t y = 0;
            display->fillRect(x, y + 1, 24, 9, BACKGROUND_COLOR);

            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->print(power);
            display->write('%');
            renderBattery(x + 20, y, 100);
        }

        void renderBattery(uint8_t x, uint8_t y, uint8_t percent) {
            const uint8_t w = 7;
            const uint8_t h = 8;
            uint8_t step = percent / (100 / (h + 1));
            uint16_t color = ST7735_WHITE;
            if (step < 2) {
                color = ST7735_RED;
            }
            for (uint8_t line = 1; line <= step; line++) {
                if (line == step) {
                    display->fillRect(x + 2, y + 1, 3, 1, color);
                } else {
                    display->fillRect(x, getDy() - 1 - line, w, 1, color);
                }
            }
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
                tmp_power = server->getPowerPercent();
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
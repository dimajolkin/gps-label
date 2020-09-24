

class ChannelView: public BaseView {
    private:
        uint8_t active = 1;
        uint8_t selected = 1;
        static const uint8_t COUNT_CHANELS = 42; // 127
        static const uint8_t COUNT_BLOCKS_IN_LINE = 6;

        static const uint16_t BACKGROUND_BLOCK = ST7735_BLUE;
        static const uint16_t BACKGROUND_ACTIVE_BLOCK = ST7735_GREEN;
        static const uint16_t BACKGROUND_SELECT_BLOCK = ST7735_YELLOW;
        LanConfig *lanConfig;

        void drawSelect(uint8_t n, uint8_t previewNumber) {
            block(previewNumber);
            selectBlock(n);
        }

        void selectBlock(uint8_t n) {
             drawBlock(n, BACKGROUND_SELECT_BLOCK);
        }

        void defaultBlock(uint8_t n) {
            drawBlock(n, BACKGROUND_BLOCK);
        }

        void block(uint8_t n) {
            if (n == active) {
                drawBlock(n, BACKGROUND_ACTIVE_BLOCK);
            } else {
                defaultBlock(n);
            }
        }

        void drawBlock(uint8_t n, uint16_t color) {
            uint8_t x = ((n - 1) % COUNT_BLOCKS_IN_LINE);
            uint8_t y = (n - 1) / COUNT_BLOCKS_IN_LINE;
            
            display->fillRoundRect((x * 20) + 3, (y * 20) + dy + 5, 18, 18, 1, BACKGROUND_BLOCK);
            display->drawRect((x * 20) + 3, (y * 20) + dy + 5, 18, 18, color);
            display->setCursor((x * 20) + 3, (y * 20) + dy + 5 + 7);
            display->print(n);
        }

        void setActive(uint8_t n) {
             defaultBlock(active);
             active = n;
             block(active);
             lanConfig->setChannel(active);
        }

    public:
        ChannelView(Adafruit_ST7735 *display, uint8_t dy): BaseView(display, dy) {}

        void configure(Container *container) {
            lanConfig = container->getLan()->getConfig();
            active = lanConfig->getChannel();
            selected = active;
        }

        void onClick(uint8_t btn) {
            if (btn == BTN_OK) {
                if (selected == active) {
                    return goBack();
                }

                setActive(selected);
            }
            
            uint8_t previewNumber = selected;

            if (btn == BTN_RIGHT) {
                selected++;
            }

            if (btn == BTN_LEFT) {
                selected--;
            }

            if (btn == BTN_UP) {
                selected -= COUNT_BLOCKS_IN_LINE;
            }

            if (btn == BTN_DOWN) {
                selected += COUNT_BLOCKS_IN_LINE;
            }

            if (selected > COUNT_CHANELS) {
                selected = COUNT_CHANELS;
            } else if (selected < 1) {
                selected = 1;
            }

            if (btn == BTN_RIGHT || btn == BTN_LEFT || btn == BTN_UP || btn == BTN_DOWN) {
                drawSelect(selected, previewNumber);
            }
        }

        String getName() {
            return "ChannelView";
        }

        void render() {
            for(uint8_t n = 1; n < COUNT_CHANELS; n++) {
                block(n);
            }
        }
};
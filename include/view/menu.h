
class Menu: public BaseView {
    private:
        uint8_t active = 1;
        
    public:
        Menu(Adafruit_ST7735 *display, uint8_t dy): BaseView(display, dy) {}
        
        void onClick(uint8_t btn) {
            Serial.println("menu view click");
            // Serial.println(btn);

            if (btn == BTN_LEFT) {
                goBack();
                return;
            }

            

            if (btn == BTN_UP) {
                active--;
                is_render = 0;
            }

            if (btn == BTN_DOWN) {
                active++;
                is_render = 0;
            }

            if (active > 4) active = 4;
            if (active < 1) active = 1;
        }

        void element(byte n, const char *chars) {
            display->setCursor(1, dy + (n * 10));
            if (n == active) {
                display->print("* ");
            } else {
                display->print("  ");
            }
            display->print(n);
            display->print(". ");
            display->print(chars);
        }

        void render() {
            display->fillRect(0, dy, 7, 5 * 10, ST77XX_BLACK);
            display->setTextColor(ST77XX_WHITE);
            display->setTextWrap(true);

            element(1, "LAN");
            element(2, "GPS");
            element(3, "Navigation");
            element(4, "Exit");
        }
};

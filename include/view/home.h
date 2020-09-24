
class Home: public BaseView {
    private:
        uint8_t is_render = 0;

    public:
        Home(Adafruit_ST7735 *display, uint8_t dx): BaseView(display, dx) {}

        void render() {
            display->setCursor(100, 150);
            display->setTextSize(1);
            display->print("Menu");    
        }

        String getName() {
            return "home";
        }

        void onClick(uint8_t btn) {
            Serial.println("home view click");
            if (btn == BTN_OK) {
                return redirectTo(new Setting(display, dy));
            }
        }
};
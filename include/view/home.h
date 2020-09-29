
class Home: public BaseView {
    private:
        const uint8_t DEFAULT_RADIUS_STEP = 10;
        const uint8_t MAX_RADIUS_STEP = 30;

        const uint8_t MAX_RADIUS = 70;

        uint8_t radiusStep = DEFAULT_RADIUS_STEP;
    public:
        Home(Adafruit_ST7735 *display, uint8_t dy): BaseView(display, dy) {}
        ~Home() {}


        void update() {
           
        }


        void render2() {
            uint8_t cx = display->width() / 2;
            uint8_t cy = 85;
            display->fillCircle(cx, cy, 2, ST7735_BLUE);
            for(uint8_t i = 0 ; i < MAX_RADIUS; i += radiusStep) {
                display->drawCircle(cx, cy, i, ST77XX_GREEN);
            }
            renderMenu(); 
        }

        void renderMenu() {
            display->setCursor(100, 150);
            display->setTextSize(1);
            display->print(F("Menu"));   
        }

        void onClick(uint8_t btn) {
            if (btn == BTN_OK) {
                return redirectTo(new Setting(display, dy));
            }

            if (btn == BTN_UP) {
                radiusStep += DEFAULT_RADIUS_STEP;
                is_render = 0;
                clear();
            }
            if (btn == BTN_DOWN) {
                radiusStep -= DEFAULT_RADIUS_STEP;
                is_render = 0;
                clear();
            }

            if (radiusStep < 0) {
                radiusStep = 0;
            }

            if (radiusStep > MAX_RADIUS_STEP) {
                radiusStep = MAX_RADIUS_STEP;
            }
            
        }
};
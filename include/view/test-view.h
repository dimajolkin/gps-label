
class TestView: public BaseView {
    private:
        String str;
    public:
        TestView(Adafruit_ST7735 *display, uint8_t dy, String str): BaseView(display, dy), str(str) {}

        ~TestView() {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }
     
        void render() {
            display->setCursor(1, dy + 30);
            display->println(F("Test view"));
            display->println(str);
        }
    
};

class ChannelView: public BaseView {
    public:
        ChannelView(Adafruit_ST7735 *display, uint8_t dy): BaseView(display, dy) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }

        String getName() {
            return "ChannelView";
        }

        void render() {
            display->setCursor(1, dy + 30);
            display->print("Channels");
        }
    
};
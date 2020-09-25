
class Renderer {
    protected:
        Adafruit_ST7735 *display;
        uint8_t is_render = 0;
        uint8_t dy = 0;
    public:
        Renderer(Adafruit_ST7735 *display, uint8_t dy): display(display), dy(dy) {}
        Renderer(Adafruit_ST7735 *display): display(display) {}
        virtual ~Renderer() {}

        void load() {
            display->fillRect(0, dy, display->width(), display->height(), BACKGROUND_COLOR);
            is_render = 0;
        }

        virtual void configure(Container *container) {}
        
        virtual void render();

        virtual void update() {};

        virtual void check() {
            if (!is_render) {
                render();
                is_render = 1;
            }
            update();
        }
};
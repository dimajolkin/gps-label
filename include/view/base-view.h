
class BaseView {
    protected:
        uint8_t is_render = 0;
        uint8_t state = 0;
        
        BaseView *next  = NULL;
        BaseView *preview  = NULL;

        Adafruit_ST7735 *display;
        uint8_t dy = 0;

    public:
        BaseView(Adafruit_ST7735 *display, uint8_t dy): display(display), dy(dy) {}

        void setup() {
            display->fillRect(0, dy, display->width(), display->height(), ST7735_BLACK);
            is_render = 0;
        }

        void goBack() {
            next = preview;
            next->setNext(NULL);
            preview = NULL;
        }

        virtual void onClick(uint8_t btn);

        BaseView* getNext() {
            return next;
        }

        BaseView* getPreview() {
            return preview;
        }

        void SetPreview(BaseView *view) {
            preview = view;
        }

        void SetNext(BaseView *view) {
            next = view;
        }
        
        virtual void render();

        void tick() {
            if (!is_render) {
                render();
                is_render = 1;
            }
        }
};

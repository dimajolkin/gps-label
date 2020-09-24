
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
        ~BaseView() {
            Serial.println("destruct view");
        }

        virtual String getName();

        void setup() {
            display->fillRect(0, dy, display->width(), display->height(), BACKGROUND_COLOR);
            is_render = 0;
        }

        virtual void configure(Container *container) {

        }

        void goBack() {
            setNext(preview);
            preview->setNext(NULL);
            setPreview(NULL);
        }

        void redirectTo(BaseView *view) {
            next = view;
            next->setPreview(this);
        }

        virtual void onClick(uint8_t btn);

        BaseView* getNext() {
            return next;
        }

        BaseView* getPreview() {
            return preview;
        }

        void setPreview(BaseView *view) {
            preview = view;
        }

        void setNext(BaseView *view) {
            next = view;
        }
        
        virtual void render();

        void check() {
            if (!is_render) {
                render();
                is_render = 1;
            }
        }
};

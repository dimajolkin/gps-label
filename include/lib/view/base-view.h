
class BaseView: public Renderer {
    private:
        BaseView *next  = NULL;
        BaseView *preview  = NULL;

    public:
        BaseView(Adafruit_ST7735 *display, uint8_t dy): Renderer(display, dy) {}
        virtual  ~BaseView() {}
        
        void goBack() {
            setNext(preview);
            if (preview->getNext() != NULL) {
                delete preview->getNext();
                preview->setNext(NULL);
            }

            if (preview != NULL) {
                setPreview(NULL);
            }
        }

        void redirectTo(BaseView *view) {
            next = view;
            next->setPreview(this);
        }

        virtual void onClick(uint8_t btn) {};

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

        virtual void render() {}
};
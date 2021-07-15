#pragma once

#include "renderer.h"

class Page: public Renderer {
    private:
        Page *next  = NULL;
        Page *preview  = NULL;

    public:
        Page(Display *display, uint8_t dy): Renderer(display, dy) {}
        virtual  ~Page() {}
        
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

        void redirectTo(Page *view) {
            next = view;
            next->setPreview(this);
        }

        virtual void onClick(uint8_t btn) {};

        Page* getNext() {
            return next;
        }

        Page* getPreview() {
            return preview;
        }

        void setPreview(Page *page) {
            preview = page;
        }

        void setNext(Page *page) {
            next = page;
        }

        virtual void render() {}
};
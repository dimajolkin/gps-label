#pragma once

#include "service-locator.h"
#include "ui/view/view.h"

class Controller {
    protected:
        ServiceLocator *container;
        View *view;

    public:
        Controller(ServiceLocator *container): container(container) {}

        void draw() {
            if (view) {
                view->draw(container->getDisplay());
            }
        }

        virtual void onClick(uint8_t key) {}
};
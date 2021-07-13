#pragma once

#include "service-locator.h"
#include "lib/ui/view.h"
#include "lib/ui/response.h"

class Controller {
    protected:
        ServiceLocator *container;
        View *view;

    public:
        Controller(ServiceLocator *container): container(container) {}

        virtual ~Controller() {
            delete(view);
        }

        void draw() {
            if (view) {
                view->draw(container->getDisplay());
            }
        }

        virtual Controller* onClick(uint8_t key) = 0;
};
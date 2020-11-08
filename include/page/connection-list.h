#pragma once

#include "lib/page/page.h"
#include "device/member.h"
#include "device/members.h"

class ConnectionListPage: public Page {
    private:
        MemberCollection *list;
    public:
        ConnectionListPage(Display *display, uint8_t dy): Page(display, dy) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }

        void configure(Container *container) {
            list = container->getMembers();
        }

        void renderMember(uint8_t n, Member *m)
        {
            // @TODO нарисовать нормально
            display->println(n);   
            display->println(m->getCountPakages());   

            display->drawRect(0, dy + (30 * n) + 2, 128, 30, ST77XX_GREEN);
        }
     
        void render() {
            display->setCursor(1, dy + 30);
            uint8_t n = 0;
            for (size_t i = 0; i < list->getSize(); i++) {
                if (list->has(i)) {
                    renderMember(n, list->get(i));
                    n++;
                }
            }
        }
};
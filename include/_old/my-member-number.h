#pragma once

#include "lib/page/page.h"
#include "device/member.h"
#include "device/members.h"

class MyMemberNumber: public Page {
     private:
        MemberService *service;
        uint8_t active = 0;
    public:
        MyMemberNumber(Display *display, uint8_t dy): Page(display, dy) {}

        void configure(Container *container) {
            service = container->getMemberService();
            active = service->getMy()->getNumber();
        }

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                return goBack();
            }

            if (btn == BTN_UP) {
                active++;
                load();
            }
            if (btn == BTN_DOWN) {
                active--;
                load();
            }
                        
            if (btn == BTN_OK) {
                service->updateMyNumber(active);
                return goBack();
            }
        }
     
        void render() {
            display->setCursor(1, dy + 30);
            display->setTextSize(12);
            display->println(active);
        }
};
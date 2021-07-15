#pragma once

#include "lib/page/page.h"
#include "device/member.h"
#include "device/members.h"

class MemberListPage: public Page {
    private:
        MemberService *service;
    public:
        MemberListPage(Display *display, uint8_t dy): Page(display, dy) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }

        void configure(Container *container) {
            service = container->getMemberService();
        }
        
        void update() {
            uint8_t n = 0;
            for (uint8_t i = 0; i < service->getList()->getSize(); i++) {
                if (service->getList()->has(i)) {
                    renderMember(n, service->getList()->get(i));
                    n++;
                }
            }
        }
};
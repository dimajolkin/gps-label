#pragma once

#include "hardware/lan/package.h"
#include "device/member.h"
#include "device/members.h"

class MemberService {
    private:
        MemberCollection *members;
    public:
        MemberService() {
            members = new MemberCollection();
        }

        MemberCollection* getList() {
            return members;
        }

        void start() {
            members->append(new Member(1, true));
        }
    
        void registerPakage(Package *pack) {
            if (!members->has(pack->n)) {
                members->append(new Member(pack->n));
            } else {
                members->get(pack->n)->setLastPackage(pack);
            }
        }

        void update() {
             for (uint8_t i = 0; i < members->getSize(); i++) {
                if (members->has(i)) {
                    members->get(i)->update();
                }
            }
        }
};
#pragma once

#include "board/hardware/lan/package.h"
#include "app/service/member/config.h"
#include "app/service/member/member.h"
#include "app/service/member/members.h"

class MemberService
{
private:
    MemberCollection *members;
    MemberConfig config;
    Member *my;

public:
    MemberService()
    {
        members = new MemberCollection();
    }

    void init()
    {
        config.init();
        my = new Member(config.getNumber(), true);
        members->append(my);
    }

    void updateMyNumber(uint8_t number)
    {
        my->setNumber(number);
        config.setNumber(number);
    }

    MemberCollection *getList()
    {
        return members;
    }

    Member *getMy()
    {
        return my;
    }

    void registerPakage(Package *pack)
    {
        if (pack->n > members->getSize())
        {
            return;
        }

        if (!members->has(pack->n))
        {
            members->append(new Member(pack->n));
        }
        else
        {
            members->get(pack->n)->setLastPackage(pack);
        }
    }

    void update()
    {
        for (uint8_t i = 0; i < members->getSize(); i++)
        {
            if (members->has(i))
            {
                members->get(i)->update();
            }
        }
    }
};
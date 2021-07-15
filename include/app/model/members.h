#pragma once

#include "framework/ui/model.h"

class MembersModel : public Model
{
public:
    MemberCollection *members;

    MembersModel(MemberCollection *members) : members(members) {}
};
#pragma once
#include "mm2_common.h"

#include <modules\phys.h>

namespace MM2
{
    // External declarations
    extern class dgPhysEntity;
    extern class dgPhysManager;
    extern class dgTrailerJoint;
    extern class phJoint;

    template<>
    void luaAddModule<module_phys>(LuaState L) {
        luaBind<phInertialCS>(L);
        luaBind<dgPhysManager>(L);
        luaBind<phJoint>(L);
        luaBind<dgTrailerJoint>(L);
        luaBind<dgPhysEntity>(L);
    }
}
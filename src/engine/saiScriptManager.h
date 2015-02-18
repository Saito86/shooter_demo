////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SCRIPTMANAGER_H
#define _SCRIPTMANAGER_H

#include "saiEntity.h"
#include "saiCamera.h"

class saiScriptManager
{
    public:
        static void registerScript(lua_State* p_L);
    private:
};

#endif // _SCRIPTMANAGER_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <lua.hpp>
#include "saiOption.h"

class saiScript
{
    public:
        saiScript(std::string p_Name);
        virtual ~saiScript();
        std::string getName(){return m_Name;}
        lua_State* getState(){return m_L;}
        void onInit();
        void onUpdate();
        void onCleanup();
        void* p_EntityPointer;
    private:
        std::string m_Name;
        lua_State* m_L;
};

#endif // _SCRIPT_H

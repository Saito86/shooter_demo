////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiScript.h"

//SCRIPT
saiScript::saiScript(std::string p_Name)
{
    std::string path = saiOptions::getPaths().f_sScriptpath + p_Name;
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    luaL_loadfile(m_L,path.c_str());
    lua_call(m_L,0,0);
    m_Name = p_Name;
    std::string nam = p_Name.erase(p_Name.size()-4,4);
}

saiScript::~saiScript()
{
    lua_close(m_L);
}


void saiScript::onInit()
{
    //calling the onInit function in lua script
    lua_getglobal(m_L,"OnInit");
    lua_pushlightuserdata(m_L,p_EntityPointer);
    lua_call(m_L,1,0);
}

void saiScript::onUpdate()
{
    //calling the onUpdate function in lua script
    lua_getglobal(m_L,"OnUpdate");
    lua_pushlightuserdata(m_L,p_EntityPointer);
    lua_call(m_L,1,0);
}

void saiScript::onCleanup()
{
    //calling the onCleanup function in lua script
    lua_getglobal(m_L,"OnCleanup");
    lua_pushlightuserdata(m_L,p_EntityPointer);
    lua_call(m_L,1,0);
}

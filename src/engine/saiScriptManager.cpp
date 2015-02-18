////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiScriptManager.h"

//lua functions
int saiLuaGetRot(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    float x = ent->getCollisionObject()->getRigidRotXasDegree();
    float y = ent->getCollisionObject()->getRigidRotYasDegree();
    float z = ent->getCollisionObject()->getRigidRotZasDegree();
    lua_pushnumber(p_S,x);
    lua_pushnumber(p_S,y);
    lua_pushnumber(p_S,z);
    return 3;
}

int saiLuaSetRot(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    if(ent != NULL)
    {
        ent->getCollisionObject()->setRigidRot(lua_tonumber(p_S,2),lua_tonumber(p_S,3),lua_tonumber(p_S,4));
    }
    return 0;
}

int saiLuaSetPos(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    if(ent != NULL)
    {
        ent->getCollisionObject()->setRigidPos(lua_tonumber(p_S,2),lua_tonumber(p_S,3),lua_tonumber(p_S,4));
    }
    return 0;
}

int saiLuaGetPos(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    float x = ent->getCollisionObject()->getRigidPosX();
    float y = ent->getCollisionObject()->getRigidPosY();
    float z = ent->getCollisionObject()->getRigidPosZ();
    lua_pushnumber(p_S,x);
    lua_pushnumber(p_S,y);
    lua_pushnumber(p_S,z);
    return 3;
}

int saiLuaGetCamPos(lua_State* p_S)
{
    lua_pushnumber(p_S,saiCamera::pos.x);
    lua_pushnumber(p_S,saiCamera::pos.y);
    lua_pushnumber(p_S,saiCamera::pos.z);
    return 3;
}

int saiLuaGetCamRot(lua_State* p_S)
{
    lua_pushnumber(p_S,saiCamera::rot.x);
    lua_pushnumber(p_S,saiCamera::rot.y);
    lua_pushnumber(p_S,saiCamera::rot.z);
    return 3;
}

int saiLuaSetCamPos(lua_State* p_S)
{
    saiCamera::pos.set(lua_tonumber(p_S,1),lua_tonumber(p_S,2),lua_tonumber(p_S,3));
    return 0;
}

int saiLuaSetCamRot(lua_State* p_S)
{
    saiCamera::rot.set(lua_tonumber(p_S,1),lua_tonumber(p_S,2),lua_tonumber(p_S,3));
    return 0;
}

int saiLuaGetName(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    lua_pushstring(p_S,(ent->getName()).c_str());
    return 1;
}

int saiLuaSetName(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    ent->setName(lua_tostring(p_S,2));
    return 0;
}
int saiLuaGetDirection(lua_State* p_S)
{
    float v1x = lua_tonumber(p_S,1);
    float v1y = lua_tonumber(p_S,2);
    float v1z = lua_tonumber(p_S,3);
    float v2x = lua_tonumber(p_S,4);
    float v2y = lua_tonumber(p_S,5);
    float v2z = lua_tonumber(p_S,6);
    saiVec3 v1(v1x,v1y,v1z);
    saiVec3 v2(v2x,v2y,v2z);
    saiVec3 result = v2-v1;
    lua_pushnumber(p_S,result.x);
    lua_pushnumber(p_S,result.y);
    lua_pushnumber(p_S,result.z);
    return 3;
}

int saiLuaNormalize(lua_State* p_S)
{
    float x = lua_tonumber(p_S,1);
    float y = lua_tonumber(p_S,2);
    float z = lua_tonumber(p_S,3);
    saiVec3 vec(x,y,z);
    vec.normalize();
    lua_pushnumber(p_S,vec.x);
    lua_pushnumber(p_S,vec.y);
    lua_pushnumber(p_S,vec.z);
    return 3;
}

int saiLuaGetDistance(lua_State* p_S)
{
    float x1 = lua_tonumber(p_S,1);
    float y1 = lua_tonumber(p_S,2);
    float z1 = lua_tonumber(p_S,3);
    float x2 = lua_tonumber(p_S,4);
    float y2 = lua_tonumber(p_S,5);
    float z2 = lua_tonumber(p_S,6);
    saiVec3 v1(x1,y1,z1);
    saiVec3 v2(x2,y2,z2);
    float d = getDistance(v1,v2);
    lua_pushnumber(p_S,d);
    return 1;
}

int saiLuaMoveTo(lua_State* p_S)
{
    saiEntity* ent = (saiEntity*)lua_touserdata(p_S,1);
    if(ent != NULL)
    {
        if(ent->getCollisionObject() != NULL)
        {
            ent->getCollisionObject()->getRigidBody()->setLinearVelocity(btVector3(lua_tonumber(p_S,2),lua_tonumber(p_S,3),lua_tonumber(p_S,4)));
        }
    }
    return 0;
}
//SCRIPTMANAGER

void saiScriptManager::registerScript(lua_State* p_L)
{
    lua_register(p_L,"getCamPos",saiLuaGetCamPos);
    lua_register(p_L,"setCamPos",saiLuaSetCamPos);
    lua_register(p_L,"getRot",saiLuaGetRot);
    lua_register(p_L,"setRot",saiLuaSetRot);
    lua_register(p_L,"setPos",saiLuaSetPos);
    lua_register(p_L,"getPos",saiLuaGetPos);
    lua_register(p_L,"getName",saiLuaGetName);
    lua_register(p_L,"setName",saiLuaSetName);
    lua_register(p_L,"getDirection",saiLuaGetDirection);
    lua_register(p_L,"getDistance",saiLuaGetDistance);
    lua_register(p_L,"normalize",saiLuaNormalize);
    lua_register(p_L,"moveTo",saiLuaMoveTo);
}


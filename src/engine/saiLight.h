////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _LIGHT_H
#define _LIGHT_H

#include "saiRenderable.h"

class saiPointLight : public saiRenderable
{
    public:
        saiPointLight();
        virtual ~saiPointLight();
        void setAmbient(saiVec3 p_amb){m_Ambient = p_amb;}
        void setDiffuse(saiVec3 p_dif){m_Diffuse = p_dif;}
        saiVec3 getAmbient(){return m_Ambient;}
        saiVec3 getDiffuse(){return m_Diffuse;}
    private:
        saiVec3 m_Ambient;
        saiVec3 m_Diffuse;
};

class saiLightManager
{
    public:
        static void setNearestLights(saiVec3 p_Pos);
        static void addLight(saiPointLight* p_light);
        static void cleanUp();
    private:
        static std::vector<saiPointLight*> s_vecLights;
};

#endif // _LIGHT_H

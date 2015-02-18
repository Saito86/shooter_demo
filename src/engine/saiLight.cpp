////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiLight.h"

//Point Light
saiPointLight::saiPointLight()
{

}

saiPointLight::~saiPointLight()
{

}

//Light Manager
std::vector<saiPointLight*> saiLightManager::s_vecLights;

void saiLightManager::setNearestLights(saiVec3 p_Pos)
{
    //for now only two lights are possible

    float pos[] = {s_vecLights[0]->getPosX(),s_vecLights[0]->getPosY(),s_vecLights[0]->getPosZ(),1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    float dif[] = {s_vecLights[0]->getDiffuse().x,s_vecLights[0]->getDiffuse().y,s_vecLights[0]->getDiffuse().z,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    float amb[] = {s_vecLights[0]->getAmbient().x,s_vecLights[0]->getAmbient().y,s_vecLights[0]->getAmbient().z,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);

    float pos2[] = {s_vecLights[1]->getPosX(),s_vecLights[1]->getPosY(),s_vecLights[1]->getPosZ(),1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, pos2);
    float dif2[] = {s_vecLights[1]->getDiffuse().x,s_vecLights[1]->getDiffuse().y,s_vecLights[1]->getDiffuse().z,1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif2);
    float amb2[] = {s_vecLights[1]->getAmbient().x,s_vecLights[1]->getAmbient().y,s_vecLights[1]->getAmbient().z,1.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
}

void saiLightManager::addLight(saiPointLight* p_light)
{
    s_vecLights.push_back(p_light);
}

void saiLightManager::cleanUp()
{
    for(unsigned int i=0;i<s_vecLights.size();i++)
    {
        delete s_vecLights[i];
    }
}

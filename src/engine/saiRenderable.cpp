////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiRenderable.h"

saiRenderable::saiRenderable()
{
    mat = NULL;
    Size.set(1,1,1);
}

saiRenderable::~saiRenderable()
{

}

void saiRenderable::setPos(float a,float b,float c)
{
    Position.set(a,b,c);
}

void saiRenderable::setPos(saiVec3 p)
{
    Position = p;
}

void saiRenderable::setPosX(float a)
{
    Position.x = a;
}

void saiRenderable::setPosY(float a)
{
    Position.y = a;
}

void saiRenderable::setPosZ(float a)
{
    Position.z = a;
}

void saiRenderable::setRot(float a,float b,float c)
{
    Rotation.set(a,b,c);
}

void saiRenderable::setRotX(float a)
{
    Rotation.x = a;
}

void saiRenderable::setRotY(float a)
{
    Rotation.y = a;
}

void saiRenderable::setRotZ(float a)
{
    Rotation.z = a;
}

void saiRenderable::setSize(float a,float b,float c)
{
    Size.set(a,b,c);
}

void saiRenderable::setSizeX(float a)
{
    Size.x = a;
}

void saiRenderable::setSizeY(float a)
{
    Size.y = a;
}

void saiRenderable::setSizeZ(float a)
{
    Size.z = a;
}

saiVec3 saiRenderable::getPos()
{
    return Position;
}

float saiRenderable::getPosX()
{
    return Position.x;
}

float saiRenderable::getPosY()
{
    return Position.y;
}

float saiRenderable::getPosZ()
{
    return Position.z;
}

saiVec3 saiRenderable::getRot()
{
    return Rotation;
}

float saiRenderable::getRotX()
{
    return Rotation.x;
}

float saiRenderable::getRotY()
{
    return Rotation.y;
}

float saiRenderable::getRotZ()
{
    return Rotation.z;
}

saiVec3 saiRenderable::getSize()
{
    return Size;
}

float saiRenderable::getSizeX()
{
    return Size.x;
}

float saiRenderable::getSizeY()
{
    return Size.y;
}

float saiRenderable::getSizeZ()
{
    return Size.z;
}

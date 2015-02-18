////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _RENDERABLE_H
#define _RENDERABLE_H

#include "saiBase.h"
#include "saiMath.h"
#include "saiMaterial.h"

class saiRenderable
{
    public:
        saiRenderable();
        virtual ~saiRenderable();
        void setPos(float a,float b,float c);
        void setPos(saiVec3 p);
        void setPosX(float a);
        void setPosY(float a);
        void setPosZ(float a);
        void setRot(float a,float b,float c);
        void setRotX(float a);
        void setRotY(float a);
        void setRotZ(float a);
        void setSize(float a,float b,float c);
        void setSizeX(float a);
        void setSizeY(float a);
        void setSizeZ(float a);
        saiVec3 getPos();
        float getPosX();
        float getPosY();
        float getPosZ();
        saiVec3 getRot();
        float getRotX();
        float getRotY();
        float getRotZ();
        saiVec3 getSize();
        float getSizeX();
        float getSizeY();
        float getSizeZ();
        saiMaterial* getMaterial(){return mat;}
        void setMaterial(saiMaterial* mt){mat = mt;}
        void setName(std::string nam){Name = nam;}
        std::string getName(){return Name;}
    protected:
        saiVec3 Position;
        saiVec3 Rotation;
        saiVec3 Size;
        saiMaterial* mat;
        std::string Name;
};

#endif // _RENDERABLE_H

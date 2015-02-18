////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SKY_H
#define _SKY_H

#include <iostream>
#include <string>

#include "saiMaterial.h"

class saiSkybox
{
    public:
        saiSkybox(std::string t1,std::string t2,std::string t3,std::string t4,std::string t5,std::string t6);
        ~saiSkybox();
        void render();
        void setSize(float a){size = a;}
        float getSize(){return size;}
    private:
        saiMaterial* mat1;
        saiMaterial* mat2;
        saiMaterial* mat3;
        saiMaterial* mat4;
        saiMaterial* mat5;
        saiMaterial* mat6;
        float size;
};

#endif // _SKY_H

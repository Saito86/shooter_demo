////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SPRITE_H
#define _SPRITE_H

#include "saiBase.h"
#include "saiOption.h"
#include "saiMaterial.h"

class saiSprite
{
    public:
        saiSprite(std::string fname);
        ~saiSprite();
        void render();
        void setPos(float x,float y);
        void setPosX(float x);
        void setPosY(float y);
        void setSize(float x,float y);
        void setSizeX(float x);
        void setSizeY(float y);
        void show(){bHidden = false;}
        void hide(){bHidden = true;}
        bool isHidden(){return bHidden;}
    private:
        GLuint texId;
        saiMaterial* m_Mat;
        int width;
        int height;
        int posX;
        int posY;
        float sizeX;
        float sizeY;
        float ratioX;
        float ratioY;
        bool bHidden;
};

#endif // _SPRITE_H

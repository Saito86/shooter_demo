////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SCREENTEXT_H
#define _SCREENTEXT_H

#include <iomanip>
#include <sstream>
#include "saiBase.h"
#include "saiOption.h"
#include "saiMaterial.h"

enum saiTextAlign
{
    SAI_ALIGN_LEFT,
    SAI_ALIGN_RIGHT
};

class saiScreentext
{
    public:
        saiScreentext(std::string txt);
        ~saiScreentext();
        void render();
        void setText(std::string txt);
        void setText(int num);
        void setPos(float x,float y);
        void setPosX(float x);
        void setPosY(float y);
        void setSize(float x,float y);
        void setSizeX(float x);
        void setSizeY(float y);
        void hide(){bHidden = true;}
        void show(){bHidden = false;}
        bool isHidden(){return bHidden;}
        std::string getText(){return Text;}
        int getSize(){return Size;}
        void setAlignment(int a){alignment = a;}
    private:
        bool bHidden;
        saiMaterial* m_Mat;
        TTF_Font* fnt;
        TTF_Font* loadFont(std::string fFile);
        GLuint loadTexture();
        GLuint texId;
        std::string Text;
        std::string fontFileName;
        int Size;
        SDL_Color color;
        int width;
        int height;
        int posX;
        int posY;
        float scaleX;
        float scaleY;
        int alignment;
};

#endif // _SCREENTEXT_H

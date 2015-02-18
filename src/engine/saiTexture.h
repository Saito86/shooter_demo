////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "saiOption.h"

class saiTexture
{
    public:
        static saiTexture* load(std::string fname);
        ~saiTexture();
        void bind();
        int getWidth(){return width;}
        int getHeight(){return height;}
        std::string getName(){return Name;}
        GLuint getId(){return texId;}
    private:
        saiTexture();
        int width;
        int height;
        std::string Name;
        GLuint texId;
};

#endif // _TEXTURE_H

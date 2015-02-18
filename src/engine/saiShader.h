////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SHADER_H
#define _SHADER_H

#include "saiOption.h"

class saiShader
{
    public:
        static saiShader* load(std::string fname);
        ~saiShader();
        void use();
        GLuint getProgramId(){return program;}
    private:
        saiShader();
        GLuint vertShader;
        GLuint fragShader;
        GLuint program;
        static GLuint loadShader(std::string fname,int type);
};

#endif // _SHADER_H

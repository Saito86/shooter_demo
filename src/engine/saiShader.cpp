////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiShader.h"

saiShader::saiShader()
{

}

saiShader::~saiShader()
{
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteProgram(program);
}

void saiShader::use()
{
    glUseProgram(program);
}

GLuint saiShader::loadShader(std::string fname,int type)
{
    std::string src;
    std::vector<std::string> lines = loadTextfile(fname);
    for(unsigned int i=0;i<lines.size();i++)
    {
        if(lines[i].c_str()[0] != '/' && lines[i].c_str()[1] != '/')
        {
            src += lines[i] + "\n";
        }
    }

    //create shader
    GLuint shaderId;
    if(type == 0)
        shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if(type == 1)
        shaderId = glCreateShader(GL_FRAGMENT_SHADER);

    //compile shader
    std::cout << "compiling shader: " << fname << std::endl;
    char const* shadSource = src.c_str();
    glShaderSource(shaderId,1,&shadSource,NULL);
    glCompileShader(shaderId);

    //check for errors
    GLint Result = GL_FALSE;
    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&Result);
    if(!Result)
    {
        int infoLogLength;
        glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        std::vector<char> shaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(shaderId,infoLogLength,NULL,&shaderErrorMessage[0]);
        std::string s(shaderErrorMessage.begin(),shaderErrorMessage.end());
        std::cout << "Compile error: " << s << std::endl;
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

saiShader* saiShader::load(std::string fname)
{
    std::string vertName = saiOptions::getPaths().f_sShaderpath + fname + ".vert";
    std::string fragName = saiOptions::getPaths().f_sShaderpath + fname + ".frag";
    saiShader* newShad = new saiShader();
    newShad->vertShader = loadShader(vertName,0);
    newShad->fragShader = loadShader(fragName,1);

    //linking shaders
    std::cout << "linking shader: " << fname << std::endl;
    newShad->program = glCreateProgram();
    glAttachShader(newShad->program,newShad->vertShader);
    glAttachShader(newShad->program,newShad->fragShader);
    //shader input
    //here
    glLinkProgram(newShad->program);

    //check for errors
    GLint Result = GL_FALSE;
    glGetProgramiv(newShad->program,GL_LINK_STATUS,&Result);
    if(!Result)
    {
        int infoLogLength;
        glGetProgramiv(newShad->program,GL_INFO_LOG_LENGTH,&infoLogLength);
        std::vector<char> programErrorMessage(std::max(infoLogLength,int(1)));
        glGetProgramInfoLog(newShad->program,infoLogLength,NULL,&programErrorMessage[0]);
        std::string s(programErrorMessage.begin(),programErrorMessage.end());
        std::cout << "Linker error: " << s << std::endl;
        glDeleteProgram(newShad->program);
        return 0;
    }

    return newShad;
}

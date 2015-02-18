////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiMaterial.h"

saiShader* saiMaterial::defaultShader;
saiShader* saiMaterial::texLight;
saiShader* saiMaterial::normalMappingShader;
saiShader* saiMaterial::diffuseMappingShader;

saiMaterial::saiMaterial()
{
    diffuseMap = NULL;
    normalMap = NULL;
    m_fR = 1.0;
    m_fG = 1.0;
    m_fB = 1.0;
    m_fA = 1.0;
    m_Ambient.set(0.1,0.1,0.1);
    m_Diffuse.set(0.6,0.6,0.6);
    m_Specular.set(1.0,1.0,1.0);
    m_fShininess = 32;
}

saiMaterial::~saiMaterial()
{
    if(diffuseMap != NULL)
        delete diffuseMap;
    if(normalMap != NULL)
        delete normalMap;
}

void saiMaterial::use()
{
    m_Shader->use();
    if(diffuseMap != NULL)
    {
        glActiveTexture(GL_TEXTURE0);
        diffuseMap->bind();
    }
    glUniform4f(glGetUniformLocation(m_Shader->getProgramId(),"color"),m_fR,m_fG,m_fB,m_fA);
    glUniform1i(glGetUniformLocation(m_Shader->getProgramId(),"diffuseMap"),0);
    if(m_sShaderName == "texLight")
    {
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"lightPos"),0.0,0.0,0.0);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_ambient"),0.1,0.1,0.1);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_diffuse"),0.6,0.6,0.6);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_specular"),1.0,1.0,1.0);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_ambient"),0.2,0.2,0.2);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_diffuse"),0.6,0.6,0.6);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_specular"),1.0,1.0,1.0);
        glUniform1f(glGetUniformLocation(m_Shader->getProgramId(),"m_shinines"),32);
    }
    else if(m_sShaderName == "normMap")
    {
        glActiveTexture(GL_TEXTURE1);
        normalMap->bind();
        glUniform1i(glGetUniformLocation(m_Shader->getProgramId(),"normalMap"),1);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"lightPos"),0.0,0.0,0.0);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_ambient"),0.1,0.1,0.1);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_diffuse"),0.6,0.6,0.6);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_specular"),1.0,1.0,1.0);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_ambient"),0.2,0.2,0.2);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_diffuse"),0.6,0.6,0.6);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"l_specular"),1.0,1.0,1.0);
        glUniform1f(glGetUniformLocation(m_Shader->getProgramId(),"m_shinines"),32);
    }
    else if(m_sShaderName == "diffuseMap")
    {
        GLfloat shiny[] = {1.0,1.0,1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
        glUniform3f(glGetUniformLocation(m_Shader->getProgramId(),"m_ambient"),m_Ambient.x,m_Ambient.y,m_Ambient.z);
    }
}

void saiMaterial::setColor(float p_r,float p_g,float p_b,float p_a)
{
    m_fR = p_r;
    m_fG = p_g;
    m_fB = p_b;
    m_fA = p_a;
}

void saiMaterial::setColor(float p_r,float p_g,float p_b)
{
    m_fR = p_r;
    m_fG = p_g;
    m_fB = p_b;
    m_fA = 1.0;
}

void saiMaterial::compileShaders()
{
    defaultShader = saiShader::load("default");
    texLight = saiShader::load("texLight");
    normalMappingShader = saiShader::load("normalmap");
    diffuseMappingShader = saiShader::load("diffusemapping");
}

void saiMaterial::cleanupShaders()
{
    delete defaultShader;
    delete texLight;
    delete normalMappingShader;
    delete diffuseMappingShader;
}

saiMaterial* saiMaterial::load(std::string fname)
{
    std::string filename = saiOptions::getPaths().f_sMaterialpath + fname + ".mat";
    std::vector<std::string> lines = loadTextfile(filename);
    if(lines.size() == 0)
        return NULL;

    saiMaterial* newMat = new saiMaterial();
    newMat->m_Shader = defaultShader;
    newMat->m_sShaderName = "default";
    for(unsigned int i=0;i<lines.size();i++)
    {
        if(lines[i].c_str()[0] == 'd' && lines[i].c_str()[1] == 'f')
        {
            char nm[32];
            sscanf(lines[i].c_str(),"df %s",nm);
            std::string name(nm);
            newMat->diffuseMap = saiTexture::load(name);
        }
        else if(lines[i].c_str()[0] == 'n' && lines[i].c_str()[1] == 'm')
        {
            char nm[32];
            sscanf(lines[i].c_str(),"df %s",nm);
            std::string name(nm);
            newMat->normalMap = saiTexture::load(name);
        }
        else if(lines[i].c_str()[0] == 's' && lines[i].c_str()[1] == 'h')
        {
            char nm[32];
            sscanf(lines[i].c_str(),"sh %s",nm);
            std::string nam(nm);
            if(nam == "texLight")
            {
                newMat->m_Shader = texLight;
                newMat->m_sShaderName = "texLight";
            }
            else if(nam == "normMap")
            {
                newMat->m_Shader = normalMappingShader;
                newMat->m_sShaderName = "normMap";
            }
            else if(nam == "diffuseMap")
            {
                newMat->m_Shader = diffuseMappingShader;
                newMat->m_sShaderName = "diffuseMap";
            }
        }
        else if(lines[i].c_str()[0] == 'c' && lines[i].c_str()[1] == 'l')
        {
            float r,g,b,a;
            sscanf(lines[i].c_str(),"cl %f %f %f %f",&r,&g,&b,&a);
            newMat->m_fA = a;
            newMat->m_fB = b;
            newMat->m_fG = g;
            newMat->m_fR = r;
        }
        else if(lines[i].c_str()[0] == 'a' && lines[i].c_str()[1] == 'c')
        {
            float ar,ag,ab;
            sscanf(lines[i].c_str(),"ac %f %f %f",&ar,&ag,&ab);
            newMat->m_Ambient.set(ar,ag,ab);
        }
        else if(lines[i].c_str()[0] == 'd' && lines[i].c_str()[1] == 'c')
        {
            float dr,dg,db;
            sscanf(lines[i].c_str(),"dc %f %f %f",&dr,&dg,&db);
            newMat->m_Diffuse.set(dr,dg,db);
        }
        else if(lines[i].c_str()[0] == 's' && lines[i].c_str()[1] == 'c')
        {
            float sr,sg,sb,shin;
            sscanf(lines[i].c_str(),"sc %f %f %f %f",&sr,&sg,&sb,&shin);
            newMat->m_Specular.set(sr,sg,sb);
            newMat->m_fShininess = shin;
        }
    }
    return newMat;
}

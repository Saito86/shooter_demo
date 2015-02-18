#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "saiShader.h"
#include "saiTexture.h"
#include "saiMath.h"

class saiMaterial
{
    public:
        static saiMaterial* load(std::string fname);
        ~saiMaterial();
        void use();
        static void compileShaders();
        static void cleanupShaders();
        float getR(){return m_fR;}
        float getG(){return m_fG;}
        float getB(){return m_fB;}
        float getA(){return m_fA;}
        void setColor(float p_r,float p_g,float p_b,float p_a);
        void setColor(float p_r,float p_g,float p_b);
        static saiShader* getDefault(){return defaultShader;}
    private:
        static saiShader* defaultShader;
        static saiShader* texLight;
        static saiShader* normalMappingShader;
        static saiShader* diffuseMappingShader;
        saiMaterial();
        saiTexture* diffuseMap;
        saiTexture* normalMap;
        saiShader* m_Shader;
        std::string m_sShaderName;
        float m_fR;
        float m_fG;
        float m_fB;
        float m_fA;
        saiVec3 m_Ambient;
        saiVec3 m_Diffuse;
        saiVec3 m_Specular;
        float m_fShininess;
};

#endif // _MATERIAL_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _STATICMODEL_H
#define _STATICMODEL_H

#include <fstream>
#include <algorithm>

#include "saiRenderable.h"
#include "saiOption.h"

//SSM File--------------------------------------------
struct saiSMHeader
{
    int vertexCount;
    int faceCount;
};

struct saiSMVertex
{
    float vertex[3];
    float normal[3];
};

struct saiSMFace
{
    int vertices[3];
    float texcoords[6];
};

class saiStaticmodel : public saiRenderable
{
    public:
        static saiStaticmodel* load(std::string fname);
        ~saiStaticmodel();
        void render();
        void update();
    private:
        saiStaticmodel();
        saiSMVertex* vertices;
        saiSMFace* faces;
        int numFaces;
        int numVertices;
};
//-----------------------------------------------------

//OBJ File---------------------------------------------
struct saiOBJface
{
    int m_nVertices[3];
    int m_nTexcoords[3];
    int m_nNormals[3];
};

class saiObjModel : public saiRenderable
{
    public:
        static saiObjModel* load(std::string p_sName);
        virtual ~saiObjModel();
        void render();
    private:
        saiObjModel();
        std::vector<saiVec3*> m_vecVertices;
        std::vector<saiVec3*> m_vecNormals;
        std::vector<saiVec3*> m_vecTexcoords;
        std::vector<saiOBJface*> m_vecFaces;
};
//-----------------------------------------------------

#endif // _STATICMODEL_H

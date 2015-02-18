////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiSky.h"

saiSkybox::saiSkybox(std::string t1,std::string t2,std::string t3,std::string t4,std::string t5,std::string t6)
{
    mat1 = saiMaterial::load(t1); // left plane
    mat2 = saiMaterial::load(t2); // front plane
    mat3 = saiMaterial::load(t3); // right plane
    mat4 = saiMaterial::load(t4); // back plane
    mat5 = saiMaterial::load(t5); // top plane
    mat6 = saiMaterial::load(t6); // bottom plane
    size = 5.0;
}

saiSkybox::~saiSkybox()
{
    delete mat1;
    delete mat2;
    delete mat3;
    delete mat4;
    delete mat5;
    delete mat6;
}

void saiSkybox::render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    //Left plane
    mat1->use();
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    glTexCoord2f(0,0);
    glVertex3f(-size,size,size);
    glTexCoord2f(0,1);
    glVertex3f(-size,-size,size);
    glTexCoord2f(1,1);
    glVertex3f(-size,-size,-size);
    glTexCoord2f(1,0);
    glVertex3f(-size,size,-size);
    glEnd();
    //front plane
    mat2->use();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size,size,size);
    glTexCoord2f(0,1);
    glVertex3f(size,-size,size);
    glTexCoord2f(1,1);
    glVertex3f(-size,-size,size);
    glTexCoord2f(1,0);
    glVertex3f(-size,size,size);
    glEnd();
    //right plane
    mat3->use();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size,size,-size);
    glTexCoord2f(0,1);
    glVertex3f(size,-size,-size);
    glTexCoord2f(1,1);
    glVertex3f(size,-size,size);
    glTexCoord2f(1,0);
    glVertex3f(size,size,size);
    glEnd();
    //back plane
    mat4->use();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-size,size,-size);
    glTexCoord2f(0,1);
    glVertex3f(-size,-size,-size);
    glTexCoord2f(1,1);
    glVertex3f(size,-size,-size);
    glTexCoord2f(1,0);
    glVertex3f(size,size,-size);
    glEnd();
    //top plane
    mat5->use();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size,size,-size);
    glTexCoord2f(0,1);
    glVertex3f(size,size,size);
    glTexCoord2f(1,1);
    glVertex3f(-size,size,size);
    glTexCoord2f(1,0);
    glVertex3f(-size,size,-size);
    glEnd();
    //bottom plane
    mat6->use();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size,-size,size);
    glTexCoord2f(0,1);
    glVertex3f(size,-size,-size);
    glTexCoord2f(1,1);
    glVertex3f(-size,-size,-size);
    glTexCoord2f(1,0);
    glVertex3f(-size,-size,size);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

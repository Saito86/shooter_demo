////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiDecal.h"

saiMaterial* saiDecal::s_Material;

saiDecal::saiDecal()
{
    if(s_Material == NULL)
    {
        s_Material = saiMaterial::load("decal");
        mat = s_Material;
    }
    else
    {
        mat = s_Material;
    }
}

saiDecal::~saiDecal()
{

}

void saiDecal::cleanUp()
{
    delete s_Material;
}

void saiDecal::render()
{
    if(mat != NULL)
        mat->use();
    glPushMatrix();
    glTranslatef(Position.x,Position.y,Position.z);
    glRotatef(Rotation.x,1,0,0);
    glRotatef(Rotation.y,0,1,0);
    glRotatef(Rotation.z,0,0,1);
    glScalef(Size.x,Size.y,Size.z);
    glBegin(GL_QUADS);
    glColor4f(1.0,1.0,1.0,1.0);
    glTexCoord2f(0,0);
    glVertex3f(-3*0.01,3*0.01,0);
    glTexCoord2f(0,1);
    glVertex3f(-3*0.01,-3*0.01,0);
    glTexCoord2f(1,1);
    glVertex3f(3*0.01,-3*0.01,0);
    glTexCoord2f(1,0);
    glVertex3f(3*0.01,3*0.01,0);
    glEnd();
    glPopMatrix();
}

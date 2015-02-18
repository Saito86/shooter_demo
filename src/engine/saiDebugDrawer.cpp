////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiDebugDrawer.h"

saiDebugDrawer::saiDebugDrawer()
{
    m_debugMode = 0;
}

void saiDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
    glPushMatrix();
    glColor4f(color.getX(),color.getY(),color.getZ(),1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex3f(from.getX(),from.getY(),from.getZ());
    glVertex3f(to.getX(),to.getY(),to.getZ());
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex3f(from.getX(),from.getY(),from.getZ());
    glVertex3f(to.getX(),to.getY(),to.getZ());
    glEnd();
    glPopMatrix();
}

void saiDebugDrawer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{

}

void saiDebugDrawer::reportErrorWarning(const char* warningString)
{
    std::cout << "Bullet warning: " << warningString << std::endl;
}

void saiDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{

}

void saiDebugDrawer::setDebugMode(int debugMode)
{
    m_debugMode = debugMode;
}

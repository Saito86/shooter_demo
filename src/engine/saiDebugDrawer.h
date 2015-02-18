////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _DEBUGDRAWER_H
#define _DEBUGDRAWER_H

#include "saiBase.h"
#include <btBulletDynamicsCommon.h>

class saiDebugDrawer : public btIDebugDraw
{
    public:
        saiDebugDrawer();
        virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
        virtual void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
        virtual void reportErrorWarning(const char* warningString);
        virtual void draw3dText(const btVector3& location,const char* textString);
        virtual void setDebugMode(int debugMode);
        virtual int getDebugMode() const{return m_debugMode;}
    private:
        int m_debugMode;
};

#endif

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _TRIGGER_H
#define _TRIGGER_H

#include "saiPhysics.h"

class saiTrigger
{
    public:
        saiTrigger(int p_nId);
        ~saiTrigger();
        int getId(){return m_nId;}
        void setCollision(saiCollisionObject* p_Collision){m_Collision = p_Collision;}
        saiCollisionObject* getCollisionObject(){return m_Collision;}
    private:
        int m_nId;
        saiCollisionObject* m_Collision;
};

#endif // _TRIGGER_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiTrigger.h"

saiTrigger::saiTrigger(int p_nId)
{
    m_nId = p_nId;
    m_Collision = NULL;
}

saiTrigger::~saiTrigger()
{
    if(m_Collision != NULL)
        saiPhysics::removeCollisionObject(m_Collision);
}

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiItem.h"

saiItem::saiItem(std::string p_sType,int p_nId,int p_nValue)
{
    mdl = NULL;
    mat = NULL;
    collObj = NULL;
    m_sType = p_sType;
    m_nId = p_nId;
    m_nValue = p_nValue;
    m_bActive = true;
}

saiItem::~saiItem()
{
    if(mdl != NULL)
        delete mdl;
    if(mat != NULL)
        delete mat;
    if(collObj != NULL)
        saiPhysics::removeCollisionObject(collObj);
}

void saiItem::render(float fDeltaTime)
{
    if(m_bActive)
    {
        if(mdl != NULL)
        {
            mdl->setRotY(mdl->getRotY()+100*fDeltaTime); // rotate mesh
            mdl->render();
        }
    }
}

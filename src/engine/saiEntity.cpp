////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiEntity.h"

unsigned int saiEntity::s_nIdCount = 0;


//Entity
saiEntity::saiEntity(std::string p_sName,saiScript* p_Script)
{
    m_pMdl = NULL;
    m_pMat = NULL;
    m_pColl = NULL;
    m_Script = p_Script;
    m_sName = p_sName;
    m_nId = s_nIdCount;
    s_nIdCount++;
}

void saiEntity::init()
{
    if(m_Script != NULL)
    {
        m_Script->onInit(); //call init-function in script
    }
}

saiEntity::~saiEntity()
{
    if(m_Script != NULL)
    {
        m_Script->onCleanup();
        delete m_Script;
    }
    if(m_pMat != NULL)
        delete m_pMat;
    if(m_pMdl != NULL)
        delete m_pMdl;
    if(m_pColl != NULL)
        saiPhysics::removeCollisionObject(m_pColl);
}

void saiEntity::update()
{
    if(m_Script != NULL)
    {
        m_Script->onUpdate();
    }
}

void saiEntity::render()
{
    if(m_pMdl != NULL)
    {
        glPushMatrix();
        if(m_pColl != NULL)
        {
            btTransform tr;
            m_pColl->getRigidBody()->getMotionState()->getWorldTransform(tr);
            float matr[16];
            tr.getOpenGLMatrix(matr);
            glMultMatrixf(matr);
        }
        m_pMdl->render();
        glPopMatrix();
    }
}

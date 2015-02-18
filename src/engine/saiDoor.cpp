////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiDoor.h"

saiDoor::saiDoor()
{
    m_Material = NULL;
    m_Model = NULL;
    m_Collision = NULL;
    m_Trigger = NULL;
    m_bIsOpening = false;
    m_bIsOpened = false;
    m_bIsClosing = false;
    m_fSpeed = 50.0*0.01;
}

saiDoor::~saiDoor()
{
    if(m_Model != NULL)
        delete m_Model;
    if(m_Material != NULL)
        delete m_Material;
    if (m_Collision != NULL)
        saiPhysics::removeCollisionObject(m_Collision);
        //delete m_Collision;
}

void saiDoor::render(float fDeltaTime)
{
    if(m_Trigger->getCollisionObject()->m_bHasCollided)
    {
        if(!m_bIsOpening && !m_bIsOpened && !m_bIsClosing)
        {
            open();
        }
    }
    else
    {
        if(m_bIsOpened && !m_bIsClosing)
        {
            close();
        }
    }
    if(m_bIsOpening)
    {
        float pi = 3.141592654f;
        float rad = (m_Model->getRotY() - 90)*pi/180.0;
        m_Model->setPosX(m_Model->getPosX()-(sin(rad)*m_fSpeed*fDeltaTime));
        m_Model->setPosZ(m_Model->getPosZ()-(cos(rad)*m_fSpeed*fDeltaTime));
        m_Collision->setRigidPos(-(sin(rad)*m_fSpeed*fDeltaTime),0,-(cos(rad)*m_fSpeed*fDeltaTime));
        saiVec3 newPos = m_Model->getPos();
        if(btDistance(btVector3(m_InitPos.x,m_InitPos.y,m_InitPos.z),btVector3(newPos.x,newPos.y,newPos.z))>115*0.01)
        {
            m_bIsOpening = false;
            m_bIsOpened = true;
        }
    }
    if(m_bIsClosing)
    {
        float pi = 3.141592654f;
        float rad = (m_Model->getRotY() - 90)*pi/180.0;
        m_Model->setPosX(m_Model->getPosX()+(sin(rad)*m_fSpeed*fDeltaTime));
        m_Model->setPosZ(m_Model->getPosZ()+(cos(rad)*m_fSpeed*fDeltaTime));
        m_Collision->setRigidPos(+(sin(rad)*m_fSpeed*fDeltaTime),0,+(cos(rad)*m_fSpeed*fDeltaTime));
        saiVec3 newPos = m_Model->getPos();
        if(btDistance(btVector3(m_InitPos.x,m_InitPos.y,m_InitPos.z),btVector3(newPos.x,newPos.y,newPos.z))< 1.0*0.01)
        {
            m_bIsOpening = false;
            m_bIsOpened = false;
            m_bIsClosing = false;
        }
    }
    if(m_Model != NULL)
    {
        //m_Model->setPosX(m_Collision->getRigidPosX());
        //m_Model->setPosZ(m_Collision->getRigidPosZ());
        m_Model->render();
    }
}

void saiDoor::setModel(saiStaticmodel* p_Model)
{
    m_Model = p_Model;
    if(m_Material != NULL)
        m_Model->setMaterial(m_Material);
}

void saiDoor::setMaterial(saiMaterial* p_Material)
{
    m_Material = p_Material;
    if(m_Model != NULL)
        m_Model->setMaterial(m_Material);
}

void saiDoor::open()
{
    //std::cout << "Door Open\n";
    saiSoundManager::play("metaldoor.wav");
    m_bIsOpening = true;
}

void saiDoor::close()
{
    //std::cout << "Door Close\n";
    m_bIsClosing = true;
}

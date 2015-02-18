////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _DOOR_H
#define _DOOR_H

#include "saiMaterial.h"
#include "saiModel.h"
#include "saiPhysics.h"
#include "saiTrigger.h"
#include "saiSound.h"

class saiDoor
{
    public:
        saiDoor();
        virtual ~saiDoor();
        void render(float fDeltaTime);
        void setId(int p_nId){m_nId = p_nId;}
        void setKeyId(int p_nKeyId){m_nKeyId = p_nKeyId;}
        int getId(){return m_nId;}
        int getKeyId(){return m_nKeyId;}
        void setModel(saiStaticmodel* p_Model);
        void setMaterial(saiMaterial* p_Material);
        void setCollision(saiCollisionObject* p_Collision){m_Collision = p_Collision;}
        void setTrigger(saiTrigger* p_Trigger){m_Trigger = p_Trigger;}
        std::string objType;
        void setInitPos(saiVec3 p_pos){m_InitPos = p_pos;}
    private:
        void open();
        void close();
        saiMaterial* m_Material;
        saiStaticmodel* m_Model;
        saiCollisionObject* m_Collision;
        saiTrigger* m_Trigger;
        int m_nId;
        int m_nKeyId;
        bool m_bIsOpening;
        bool m_bIsOpened;
        bool m_bIsClosing;
        saiVec3 m_InitPos;
        float m_fSpeed;
};

#endif // _DOOR_H

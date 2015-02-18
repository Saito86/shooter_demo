////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _ITEM_H
#define _ITEM_H

#include "saiBase.h"
#include "saiModel.h"
#include "saiPhysics.h"

class saiItem
{
    public:
        saiItem(std::string p_sType,int p_nId,int p_nValue);
        virtual ~saiItem();
        void render(float fDeltaTime);
        int getValue(){return m_nValue;}
        saiObjModel* mdl;
        saiMaterial* mat;
        saiCollisionObject* collObj;
        int getId(){return m_nId;}
        std::string getType(){return m_sType;}
        void setActive(bool p_bActive){m_bActive = p_bActive;}
        bool getActive(){return m_bActive;}
    private:
        std::string m_sType;
        int m_nValue;
        int m_nId;
        bool m_bActive;
};

#endif // _ITEM_H

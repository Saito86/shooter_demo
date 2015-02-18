////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _ENTITY_H
#define _ENTITY_H

#include "saiModel.h"
#include "saiScript.h"
#include "saiPhysics.h"


class saiEntity
{
    public:
        saiEntity(std::string p_sName,saiScript* p_Script);
        ~saiEntity();
        void init();
        void update();
        void render();
        //getters setters
        std::string getName(){return m_sName;}
        void setName(std::string p_sName){m_sName = p_sName;}
        unsigned int getId(){return m_nId;}
        void setMaterial(saiMaterial* p_pMat){m_pMat = p_pMat;}
        saiMaterial* getMaterial(){return m_pMat;}
        void setModel(saiObjModel* p_pMdl){m_pMdl = p_pMdl;}
        saiObjModel* getModel(){return m_pMdl;}
        void setCollisionObject(saiCollisionObject* p_pColl){m_pColl = p_pColl;}
        saiCollisionObject* getCollisionObject(){return m_pColl;}
    private:
        int type;
        saiObjModel* m_pMdl;
        saiMaterial* m_pMat;
        saiCollisionObject* m_pColl;
        saiScript* m_Script;
        std::string m_sName;
        unsigned int m_nId;
        static unsigned int s_nIdCount;
};

#endif // _ENTITY_H

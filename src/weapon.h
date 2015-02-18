////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _WEAPON_H
#define _WEAPON_H

#include "saiBase.h"
#include "saiModel.h"
#include "saiAnimatedmodel.h"
#include "saiParticle.h"
#include "saiDecal.h"
#include "saiSound.h"

class WeaponClass
{
    public:
        //loads a .def file
        static WeaponClass* load(std::string fname);
        virtual ~WeaponClass();
        void render(float fDeltaTime);
        void shoot();
        void reload();
        //getters/setters
        int getAmmo(){return initAmmo;}
        void addAmmo(int amount);
        int getDamage(){return damage;}
    private:
        WeaponClass();
        int initAmmo;
        int damage;
        int clipSize;
        int ammoType;
        int type;
        bool m_bFireVisible;
        int m_nFireCounter;
        saiAnimatedmodel* fpMdl;
        saiObjModel* gunFire;
        saiMaterial* mat;
        saiMaterial* fireMat;
        std::string Name;
        saiVec3 offsetPosition;
        saiVec3 offsetRotation;
        saiVec3 offsetSize;
};

#endif // _WEAPON_H

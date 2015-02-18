////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _PLAYER_H
#define _PLAYER_H

#include "actor.h"
#include "saiCamera.h"
#include "saiInput.h"
#include "saiModel.h"
#include "saiMap.h"
#include "saiPhysics.h"
#include "weapon.h"
#include "hud.h"
#include "saiDecal.h"
#include "enemy.h"
#include "saiParticle.h"
#include "saiMd5.h"

class Player : public Actor
{
    public:
        Player(saiCamera* cm,Hud* hd);
        ~Player();
        void render(float fDeltaTime);
        void update(float fDeltaTime);
        void setMap(saiMap* level);
        std::string objType;
    private:
        saiCamera* cam;
        saiMap* lvl;
        Hud* hud;
        saiCollisionObject* collObj;
        WeaponClass* currentWeapon;
        std::vector<WeaponClass*> weapons;
        float walkSpeed;
        float runSpeed;
        float currSpeed;
        void moveTo(float dir,float fDeltaTime);
        void shoot();
        void reload();
        void jump();
        void sneak();
        void standup();
        bool isShooting;
        bool isJumping;
        bool isReloading;
        bool isSneaking;
        saiMd5* mdl; //testing md5 mesh and animation
};

#endif // _PLAYER_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _ENEMY_H
#define _ENEMY_H

#include "saiAnimatedmodel.h"
#include "saiPhysics.h"
#include "actor.h"
#include "player.h"

class Enemy : public Actor
{
    public:
        Enemy(float px,float py,float pz,float dir);
        ~Enemy();
        void update(float fDeltaTime);
        void render(float fDeltaTime);
        void hit(int p_nDamage);
    private:
        saiAnimatedmodel* mdl;
        saiMaterial* mat;
        saiCollisionObject* collObj;
        bool m_bIsDead;
        void die();
};

#endif // _ENEMY_H

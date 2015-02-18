////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _ACTOR_H
#define _ACTOR_H

#include "saiMath.h"
#include "saiCollision.h"

//interface for characters
class Actor
{
    public:
        Actor();
        virtual ~Actor();


        virtual void render(float fDeltaTime) = 0;
        virtual void update(float fDeltaTime) = 0;
    protected:
        std::string Name;
        int health;

        //transforms
        saiVec3 Position;
        saiVec3 Rotation;
    private:
};

#endif // _ACTOR_H

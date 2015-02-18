////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _PHYSICS_H
#define _PHYSICS_H

#define BIT(x) (1<<(x))

#include "saiCollision.h"
#include "saiDebugDrawer.h"

enum colMask
{
    MASK_NOTHING = 0,
    MASK_RAY = BIT(0),
    MASK_ALL = BIT(1)
};

class saiPhysics
{
    public:
        saiPhysics();
        ~saiPhysics();
        void update(float time);
        void render();
        static void addCollisionObject(saiCollisionObject* obj);
        static void removeCollisionObject(saiCollisionObject* obj);
        static btDynamicsWorld* getWorld(){return world;}
        static void resetObjects();
    private:
        btCollisionConfiguration* collisionConfig;
        btDispatcher* dispatcher;
        btBroadphaseInterface* broadphase;
        btConstraintSolver* solver;
        static btDynamicsWorld* world;
        static std::vector<saiCollisionObject*> objects;
        saiDebugDrawer* drawer;
};

#endif // _PHYSICS_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiPhysics.h"

std::vector<saiCollisionObject*> saiPhysics::objects;
btDynamicsWorld* saiPhysics::world = NULL;


bool saiCollisionCallback(btManifoldPoint& cp,const btCollisionObjectWrapper* obj1,int id1,int index1,const btCollisionObjectWrapper* obj2,int id2,int index2)
{
    ((saiCollisionObject*)obj1->getCollisionObject()->getUserPointer())->collide((saiCollisionObject*)obj2->getCollisionObject()->getUserPointer());
    ((saiCollisionObject*)obj2->getCollisionObject()->getUserPointer())->collide((saiCollisionObject*)obj1->getCollisionObject()->getUserPointer());
    saiCollision col1;
    col1.obj1 = (saiCollisionObject*)obj1->getCollisionObject()->getUserPointer();
    col1.obj2 = (saiCollisionObject*)obj2->getCollisionObject()->getUserPointer();
    saiCollision col2;
    col2.obj1 = (saiCollisionObject*)obj2->getCollisionObject()->getUserPointer();
    col2.obj2 = (saiCollisionObject*)obj1->getCollisionObject()->getUserPointer();
    //col1.point = cp.
    ((saiCollisionObject*)obj1->getCollisionObject()->getUserPointer())->m_coll = col1;
    ((saiCollisionObject*)obj1->getCollisionObject()->getUserPointer())->m_bHasCollided = true;
    ((saiCollisionObject*)obj2->getCollisionObject()->getUserPointer())->m_coll = col2;
    ((saiCollisionObject*)obj2->getCollisionObject()->getUserPointer())->m_bHasCollided = true;


    return false;
}

saiPhysics::saiPhysics()
{
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfig);
    world->setGravity(btVector3(0.0f,-9.81f,0.0f));
    drawer = new saiDebugDrawer();
    drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    world->setDebugDrawer(drawer);
    gContactAddedCallback = saiCollisionCallback;
}

saiPhysics::~saiPhysics()
{
    delete dispatcher;
    delete collisionConfig;
    delete solver;
    delete broadphase;
    delete drawer;
    delete world;
}


void saiPhysics::update(float time)
{
    //world->stepSimulation(1/time);
    world->stepSimulation(time);
}

void saiPhysics::addCollisionObject(saiCollisionObject* obj)
{
    objects.push_back(obj);
    if(obj->m_bCollideWithRays)
    {
        int collideWith = MASK_RAY | MASK_ALL;
        world->addRigidBody(obj->getRigidBody(),MASK_ALL,collideWith);
    }
    else
    {
        int collideWith = MASK_ALL;
        world->addRigidBody(obj->getRigidBody(),MASK_ALL,collideWith);
    }
}

void saiPhysics::removeCollisionObject(saiCollisionObject* obj)
{
    world->removeRigidBody(obj->getRigidBody());
    for(unsigned int i=0;i<objects.size();i++)
    {
        if(objects[i]->getId() == obj->getId())
        {
            objects.erase(objects.begin() + i);
        }
    }
}

void saiPhysics::render()
{
    world->debugDrawWorld();
}

void saiPhysics::resetObjects()
{
    for(unsigned int i=0;i<objects.size();i++)
    {
        objects[i]->reset();
    }
}

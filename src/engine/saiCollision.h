////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _COLLISION_H
#define _COLLISION_H

#include "saiBase.h"
#include "saiMath.h"
#include <btBulletDynamicsCommon.h>

enum saiCollTypes
{
    COLL_NONE,
    COLL_SPHERE,
    COLL_BOX,
    COLL_INF_PLANE,
    COLL_CYLINDER,
    COLL_TRIANGLEMESH,
    COLL_CAPSULE,
    COLL_COMPOUND
};


struct saiCollision
{
    void* obj1;
    void* obj2;
    saiVec3 point;
};

struct saiCollisionTriangle
{
    saiVec3 vertices[3];
};

class saiCollisionObject
{
    public:
        saiCollisionObject(float px,float py,float pz,float rx,float ry,float rz,float m);
        ~saiCollisionObject();
        void createSphere(float rad);
        void createBox(float w,float h,float l);
        void createInfinitePlane();
        void createCylinder(float rad,float height);
        void createTrianglemesh(std::vector<saiCollisionTriangle>& tris);
        void createCapsule(float rad,float height);
        void createCompound();
        void finishCompound();
        void addBox(float w,float h,float l,saiVec3 locPos,saiVec3 locRot);
        void addSphere(float rad,saiVec3 locPos);
        int getType(){return Type;}
        void setColor(float r,float g,float b){colR=r;colG=g;colB=b;}
        void setMass(float m){mass=m;}
        float getMass(){return mass;}
        btRigidBody* getRigidBody(){return rigBody;}
        unsigned int getId(){return id;}
        float getRigidPosX();
        float getRigidPosY();
        float getRigidPosZ();
        float getRigidRotX();
        float getRigidRotY();
        float getRigidRotZ();
        float getRigidRotXasDegree();
        float getRigidRotYasDegree();
        float getRigidRotZasDegree();
        void setRigidPos(float a,float b,float c);
        void setRigidRot(float a,float b,float c);
        void collide(saiCollisionObject* obj);
        void reset();
        saiCollision m_coll;
        std::string m_sParentName;
        void* m_pParentObj;
        bool m_bHasCollided;
        saiCollisionObject* otherCollisionObject;
        float getBoxWidth(){return boxWidth;}
        float getBoxHeight(){return boxHeight;}
        float getBoxLength(){return boxLength;}
        bool m_bCollideWithRays;
    private:
        float posX;
        float posY;
        float posZ;
        float rotX;
        float rotY;
        float rotZ;
        float colR;
        float colG;
        float colB;
        float mass;
        float boxWidth;
        float boxHeight;
        float boxLength;
        float sphRadius;
        float cylRadius;
        float cylHeight;
        float capRadius;
        float capHeight;
        int Type;
        btTransform t;
        btRigidBody* rigBody;
        btMotionState* motion;
        btSphereShape* sphere;
        btStaticPlaneShape* plane;
        btBoxShape* box;
        btCylinderShape* cylinder;
        btTriangleMesh* triMesh;
        btCollisionShape* triMeshShape;
        btCapsuleShape* capsule;
        btCompoundShape* compound;
        unsigned int id;
        static unsigned int idCount;
};
#endif // _COLLISION_H

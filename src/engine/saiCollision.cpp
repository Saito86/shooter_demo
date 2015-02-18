////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiCollision.h"

unsigned int saiCollisionObject::idCount = 0;

//create a blank collision object
saiCollisionObject::saiCollisionObject(float px,float py,float pz,float rx,float ry,float rz,float m)
{
    Type = COLL_NONE;
    mass = m;
    posX = px*0.01; // convert to meters
    posY = py*0.01;
    posZ = pz*0.01;
    rotX = rx;
    rotY = ry;
    rotZ = rz;

    //set default values
    colR = 1.0f;
    colG = 1.0f;
    colB = 1.0f;
    motion = NULL;
    rigBody = NULL;
    sphere = NULL;
    plane = NULL;
    box = NULL;
    cylinder = NULL;
    triMeshShape = NULL;
    capsule = NULL;
    compound = NULL;
    id = idCount;
    idCount++;
    m_sParentName = "None";
    m_bHasCollided = false;
    m_bCollideWithRays = true;
}

saiCollisionObject::~saiCollisionObject()
{
    if(motion!=NULL)
        delete motion;
    if(sphere!=NULL)
        delete sphere;
    if(plane!=NULL)
        delete plane;
    if(box!=NULL)
        delete box;
    if(cylinder!=NULL)
        delete cylinder;
    if(triMeshShape!=NULL)
        delete triMeshShape;
    if(triMesh!=NULL)
        delete triMesh;
    if(capsule != NULL)
        delete capsule;
    if(compound != NULL)
        delete compound;
    if(rigBody!=NULL)
        delete rigBody;
}

void saiCollisionObject::createSphere(float rad)
{
    Type = COLL_SPHERE;
    sphRadius = rad*0.01;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0));
    sphere = new btSphereShape(sphRadius);
    motion = new btDefaultMotionState(t);
    btVector3 inertia(0,0,0);
    if(mass != 0.0)
        sphere->calculateLocalInertia(mass,inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::createBox(float w,float h,float l)
{
    Type = COLL_BOX;
    boxWidth = w*0.01;
    boxHeight = h*0.01;
    boxLength = l*0.01;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0)); // x and y are swaped
    box = new btBoxShape(btVector3((w/2)*0.01,(h/2)*0.01,(l/2)*0.01));
    motion = new btDefaultMotionState(t);
    btVector3 inertia(0,0,0);
    if(mass != 0.0)
        box->calculateLocalInertia(mass,inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,box,inertia);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::createInfinitePlane()
{
    Type = COLL_INF_PLANE;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    plane = new btStaticPlaneShape(btVector3(0,1,0),0);
    motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,plane);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::createCylinder(float rad,float height)
{
    Type = COLL_CYLINDER;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0));
    cylRadius = rad*0.01;
    cylHeight = height*0.01;
    cylinder = new btCylinderShape(btVector3(rad*0.01,height*0.01,rad*0.01));
    motion = new btDefaultMotionState(t);
    btVector3 inertia(0,0,0);
    if(mass != 0.0)
        cylinder->calculateLocalInertia(mass,inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,cylinder,inertia);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::createCapsule(float rad,float height)
{
    Type = COLL_CAPSULE;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0));
    capRadius = rad*0.01;
    capHeight = height*0.01;
    capsule = new btCapsuleShape(rad*0.01,height*0.01);
    motion = new btDefaultMotionState(t);
    btVector3 inertia(0,0,0);
    if(mass != 0.0)
        capsule->calculateLocalInertia(mass,inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,capsule,inertia);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::createTrianglemesh(std::vector<saiCollisionTriangle>& tris)
{
    Type = COLL_TRIANGLEMESH;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0));
    triMesh = new btTriangleMesh();
    for(unsigned int i=0;i<tris.size();i++)
    {
        btVector3 v0(tris[i].vertices[0].x,tris[i].vertices[0].y,tris[i].vertices[0].z);
        btVector3 v1(tris[i].vertices[1].x,tris[i].vertices[1].y,tris[i].vertices[1].z);
        btVector3 v2(tris[i].vertices[2].x,tris[i].vertices[2].y,tris[i].vertices[2].z);
        //std::cout << v0.getX() << " " << v0.getY() << " " << v0.getZ() << std::endl;
        triMesh->addTriangle(v0,v1,v2);
    }
    //std::cout << triMesh->getNumTriangles() << std::endl;
    triMeshShape = new btBvhTriangleMeshShape(triMesh,true);
    motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,triMeshShape);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

//compounds don't work yet
void saiCollisionObject::createCompound()
{
    Type = COLL_COMPOUND;
    t.setIdentity();
    t.setOrigin(btVector3(posX,posY,posZ));
    float pi = 3.141592654f;
    t.setRotation(btQuaternion(rotY*pi/180.0,rotX*pi/180.0,rotZ*pi/180.0));
    compound = new btCompoundShape();
}

void saiCollisionObject::finishCompound()
{
    motion = new btDefaultMotionState(t);
    btVector3 inertia(0,0,0);
    if(mass != 0.0)
        compound->calculateLocalInertia(mass,inertia);
    btRigidBody::btRigidBodyConstructionInfo info(mass,motion,compound,inertia);
    rigBody = new btRigidBody(info);
    rigBody->setCollisionFlags(rigBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    rigBody->setUserPointer(this);
}

void saiCollisionObject::addBox(float w,float h,float l,saiVec3 locPos,saiVec3 locRot)
{
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(locPos.x*0.01,locPos.y*0.01,locPos.z*0.01));
    float pi = 3.141592654f;
    trans.setRotation(btQuaternion(locRot.y*pi/180.0,locRot.x*pi/180.0,locRot.z*pi/180.0));
    btBoxShape* newBox = new btBoxShape(btVector3((w/2)*0.01,(h/2)*0.01,(l/2)*0.01));
    compound->addChildShape(trans,newBox);
}

void saiCollisionObject::addSphere(float rad,saiVec3 locPos)
{
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(locPos.x*0.01,locPos.y*0.01,locPos.z*0.01));
    btSphereShape* sph = new btSphereShape(rad*0.01);
    compound->addChildShape(trans,sph);
}

float saiCollisionObject::getRigidPosX()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getOrigin().x();
}

float saiCollisionObject::getRigidPosY()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getOrigin().y();
}

float saiCollisionObject::getRigidPosZ()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getOrigin().z();
}

float saiCollisionObject::getRigidRotX()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getRotation().x();
}

float saiCollisionObject::getRigidRotY()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getRotation().y();
}

float saiCollisionObject::getRigidRotZ()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    return tr.getRotation().z();
}

float saiCollisionObject::getRigidRotXasDegree()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    float tmp = tr.getRotation().x();
    return tmp*180/3.141592654f;
}

float saiCollisionObject::getRigidRotYasDegree()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    float tmp = tr.getRotation().y();
    return tmp*180/3.141592654f;
}

float saiCollisionObject::getRigidRotZasDegree()
{
    btTransform tr;
    rigBody->getMotionState()->getWorldTransform(tr);
    float tmp = tr.getRotation().z();
    return tmp*180/3.141592654f;
}

void saiCollisionObject::setRigidPos(float a,float b,float c)
{
//    btTransform tr;
//    tr.setOrigin(btVector3(a,b,c));
//    rigBody->getMotionState()->setWorldTransform(tr);
    //t.setOrigin(btVector3(a,b,c));
    rigBody->translate(btVector3(a,b,c));
}

void saiCollisionObject::setRigidRot(float a,float b,float c)
{
//    btTransform tr;
//    tr.setRotation(btQuaternion(a,b,c));
//    rigBody->getMotionState()->setWorldTransform(tr);
    t.setRotation(btQuaternion(a,b,c));
}

void saiCollisionObject::collide(saiCollisionObject* obj)
{
    m_bHasCollided = true;
    otherCollisionObject = obj;
}

void saiCollisionObject::reset()
{
    m_bHasCollided = false;
}

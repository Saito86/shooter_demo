////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "enemy.h"

Enemy::Enemy(float px,float py,float pz,float dir)
{
    //set the initial transform
    //Convert centimeters to meters
    Position.set(px*0.01,py*0.01,pz*0.01);
    Rotation.set(0,dir,0);

    //load mesh and material
    mat = saiMaterial::load("enemy");
    mdl = saiAnimatedmodel::load("enemy");
    mdl->setMaterial(mat);

    //move the mesh to initial position
    mdl->setPos(px*0.01,py*0.01,pz*0.01);
    mdl->setRot(0,dir,0);

    //create animation
    mdl->addAnimation(1,5,10,"shoot");
    mdl->addAnimation(6,8,3,"idle");
    mdl->addAnimation(9,12,5,"walk");
    mdl->addAnimation(14,16,10,"hit");
    mdl->addAnimation(17,20,5,"die");
    mdl->addAnimation(20,21,5,"dead");

    //play idle animation
    mdl->playAnimation(2,false);

    //create collision object
    collObj = new saiCollisionObject(px,py+40,pz,0,0,0,130.0);
    collObj->createCapsule(30.0,120.0);
    collObj->m_sParentName = "Enemy";
    collObj->m_pParentObj = this;
    saiPhysics::addCollisionObject(collObj);
    collObj->getRigidBody()->setAngularFactor(0);//Disable rotation
    collObj->getRigidBody()->forceActivationState(DISABLE_DEACTIVATION);
    m_bIsDead = false;
}

Enemy::~Enemy()
{
    delete mdl;
    delete mat;
    if(!m_bIsDead) // if the enemy is dead the collision object is already removed
        saiPhysics::removeCollisionObject(collObj);
}

void Enemy::render(float fDeltaTime)
{
    if(health > 0)
    {
        //if enemy has no active animation
        //play idle animation
        if(mdl->hasStopedPlaying())
            mdl->playAnimation(2,false);
    }
    else
    {
        if(mdl->hasStopedPlaying())
        {
            mdl->playAnimation("dead",true);
        }
    }
    mdl->render(fDeltaTime);
}

void Enemy::update(float fDeltaTime)
{
    if(!m_bIsDead)
    {
        //set mesh position and rotation to collision object
        mdl->setPos(collObj->getRigidPosX(),collObj->getRigidPosY()-90*0.01,collObj->getRigidPosZ());
        mdl->setRot(Rotation.x,Rotation.y,Rotation.z);
    }
}

void Enemy::hit(int p_nDamage)
{
    if(!m_bIsDead)
    {
        health -= p_nDamage;
        if(health <= 0)
        {
            die();
        }
        else
            mdl->playAnimation("hit",false);
    }
}

void Enemy::die()
{
    mdl->playAnimation("die",false);
    m_bIsDead = true;
    saiPhysics::removeCollisionObject(collObj);
}

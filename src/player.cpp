////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "player.h"

Player::Player(saiCamera* cm,Hud* hd)
{
    //set default values
    objType = "player";
    cam = cm;
    hud = hd;
    Position.set(0*0.01,10*0.01,0*0.01);
    Rotation.set(-90,45,0);
    walkSpeed = 20000.0*0.01;
    runSpeed = 40000.0*0.01;
    currSpeed = walkSpeed;

    //hide mouse cursor
    saiInput::showCursor(false);

    //move mouse cursor to the screencenter
    saiInput::warpMouse(saiOptions::getConfig().m_iScreenCenterX,saiOptions::getConfig().m_iScreenCenterY);

    //create capsule collision object
    collObj = new saiCollisionObject(Position.x,Position.y+10,Position.z,0,0,0,130.0);
    collObj->createCapsule(30.0,120.0);
    saiPhysics::addCollisionObject(collObj);
    collObj->getRigidBody()->setAngularFactor(0);
    collObj->getRigidBody()->forceActivationState(DISABLE_DEACTIVATION);
    collObj->m_sParentName = "Player";
    isShooting = false;
    isSneaking = false;
    //create Weapons
    currentWeapon = WeaponClass::load("pistol");
    weapons.push_back(currentWeapon);
    hud->setAmmo(currentWeapon->getAmmo());

    //create md5 test mesh
    mdl = saiMd5::load("bob_lamp_update");
    mdl->setSize(0.25,0.25,0.25);
    mdl->setPos(0.0,0.0,-1000.0*0.01);
    mdl->loadAnim("bob_lamp_update");
}

Player::~Player()
{
    saiPhysics::removeCollisionObject(collObj);
    for(unsigned int i=0;i<weapons.size();i++)
        delete weapons[i];
    delete mdl;
}

void Player::render(float fDeltaTime)
{
    currentWeapon->render(fDeltaTime);
    mdl->render();
}

void Player::update(float fDeltaTime)
{
    mdl->update(fDeltaTime);
    if(cam->Mode == SAI_CAM_PLAYER)
    {
        //get mouse movement and rotate camera
        Rotation.y += 12.0*(saiOptions::getConfig().m_iScreenCenterX - saiInput::keyMap.mousePosX) * fDeltaTime;
        Rotation.x += 12.0*(saiOptions::getConfig().m_iScreenCenterY - saiInput::keyMap.mousePosY) * fDeltaTime;
            if(Rotation.x > 90.0)
                Rotation.x = 90.0;
            if(Rotation.x < -90.0)
                Rotation.x = -90.0;
            if(Rotation.y < 0.0)
                Rotation.y += 360.0;
            if(Rotation.y > 360.0)
                Rotation.y -= 360.0;
        Position.set(cam->pos.x,cam->pos.y,cam->pos.z);

        //process keys
        if(saiInput::keyMap.up) //w
        {
            moveTo(0.0,fDeltaTime);
        }
        if(saiInput::keyMap.down) // s
        {
            moveTo(180.0,fDeltaTime);
        }
        if(saiInput::keyMap.left) // a
        {
            moveTo(90.0,fDeltaTime);
        }
        if(saiInput::keyMap.right) // d
        {
            moveTo(270.0,fDeltaTime);
        }
        if(!saiInput::keyMap.up && !saiInput::keyMap.down && !saiInput::keyMap.left && !saiInput::keyMap.right)
        {
            if(!isJumping)
                collObj->getRigidBody()->setLinearVelocity(btVector3(0.0,0.0,0.0));
        }
        if(saiInput::keyMap.mouseLeft)
        {
            shoot();
        }
        else
        {
            isShooting  = false;
        }
        if(saiInput::keyMap.jump) // space
        {
            jump();
        }
        else
        {
            isJumping = false;
        }
        if(saiInput::keyMap.sprint) // left shift
        {
            currSpeed = runSpeed;
        }
        else
        {
            currSpeed = walkSpeed;
        }
        if(saiInput::keyMap.sneak) // left ctrl
        {
            sneak();
        }
        else
        {
            if(isSneaking)
                standup();
        }
        if(saiInput::keyMap.reload) // r
        {
            reload();
        }
        else
        {
            isReloading = false;
        }

        //set camera position
        if(!isSneaking)
            cam->pos.set(collObj->getRigidPosX(),collObj->getRigidPosY()+80*0.01,collObj->getRigidPosZ());
        else
            cam->pos.set(collObj->getRigidPosX(),collObj->getRigidPosY()+40*0.01,collObj->getRigidPosZ());
        cam->rot.set(Rotation);

        //get collision
        if(collObj->m_bHasCollided)
        {
            //if collision with an item
            if(collObj->otherCollisionObject->m_sParentName == "Item")
            {
                saiItem* colItem = ((saiItem*)(collObj->otherCollisionObject->m_pParentObj));
                if(colItem->getType() == "PistolAmmo")
                {
                    if(colItem->getActive())
                    {
                        currentWeapon->addAmmo(colItem->getValue());
                        hud->setAmmo(currentWeapon->getAmmo());
                        colItem->setActive(false);
                        saiSoundManager::play("pistolpickup.wav");
                    }
                }
            }
        }
        //reset mouse position to screen center
        saiInput::warpMouse(saiOptions::getConfig().m_iScreenCenterX,saiOptions::getConfig().m_iScreenCenterY);

        //reset collision object
        collObj->reset();
    }
}

void Player::moveTo(float dir,float fDeltaTime)
{
    float pi = 3.141592654f;

    //get direction in radians
    float rad = (Rotation.y + dir)*pi/180.0;

    //get direction as vector
    btVector3 vDir(-sin(rad),0,-cos(rad));

    //normalize direction vector
    btVector3 vFinal = (vDir.normalized()*(currSpeed*fDeltaTime));

    //move collision object
    collObj->getRigidBody()->setLinearVelocity(vFinal);
}

void Player::shoot()
{
    //if is already shooting, do nothing
    if(!isShooting)
    {
        if(currentWeapon->getAmmo() > 0)
        {
            //shoot in camera direction
            saiVec3 dir = cam->getDirection() * 1000;

            //raytest callback
            btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(cam->pos.x,cam->pos.y,cam->pos.z),btVector3(dir.x,dir.y,dir.z));
            saiPhysics::getWorld()->rayTest(btVector3(cam->pos.x,cam->pos.y,cam->pos.z),btVector3(dir.x,dir.y,dir.z),rayCallback);

            if(rayCallback.hasHit())
            {
                //get collision point
                saiVec3 p(rayCallback.m_hitPointWorld.getX(),rayCallback.m_hitPointWorld.getY(),rayCallback.m_hitPointWorld.getZ());

                //get normal of collision surface
                saiVec3 n(rayCallback.m_hitNormalWorld.getX(),rayCallback.m_hitNormalWorld.getY(),rayCallback.m_hitNormalWorld.getZ());


                if(((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Level" ||
                   ((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Static" ||
                   ((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Entity" ||
                   ((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Door")
                {

                    saiMaterial* newMat = saiMaterial::load("particle");
                    saiParticle* newPart = new saiParticle(p,n*0.01,20,0.5,newMat,20.0,0.05,saiVec3(1.0,0.8,0.0),saiVec3(0.01,0.01,0.01));
                    saiParticleManager::addParticle(newPart);

                    if(((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Level" ||
                   ((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Static")
                    {
                        //if there are more than 50 decals,
                        //delete the oldest one
                        if(lvl->m_vecDecals.size()>50)
                        {
                            lvl->m_vecDecals.erase(lvl->m_vecDecals.begin());
                        }

                        //create a new decal
                        saiDecal* newDecal = new saiDecal();
                        newDecal->setPos(p+n*1.1*0.01);
                        newDecal->setRot(n.z*90-90,n.x*90,n.y*90);//align to surface
                        lvl->m_vecDecals.push_back(newDecal);
                    }
                }

                if(((saiCollisionObject*)(rayCallback.m_collisionObject->getUserPointer()))->m_sParentName == "Enemy")
                {
                    ((Enemy*)((saiCollisionObject*)rayCallback.m_collisionObject->getUserPointer())->m_pParentObj)->hit(currentWeapon->getDamage());
                    saiMaterial* newMat = saiMaterial::load("blood");
                    saiParticle* newPart = new saiParticle(p,n*0.01,5,0.8,newMat,15.0,0.025,saiVec3(0.8,0.2,0.2),saiVec3(0.3,0.3,0.1));
                    saiParticleManager::addParticle(newPart);
                }
            }
            currentWeapon->shoot();
            hud->setAmmo(currentWeapon->getAmmo());
        }
        else
        {
            saiSoundManager::play("emptygun.wav");
        }
        isShooting = true;
    }
}

void Player::jump()
{
    if(!isJumping)
    {
        collObj->getRigidBody()->setLinearVelocity(btVector3(0,1,0));
        isJumping = true;
    }
}

void Player::sneak()
{
    if(!isSneaking)
    {
        isSneaking = true;
    }
}

void Player::standup()
{
    isSneaking = false;
}

void Player::reload()
{
    if(!isReloading)
    {
        currentWeapon->reload();
        isReloading = true;
    }
}

void Player::setMap(saiMap* level)
{
    lvl = level;

    //create spawnpoints
    for(unsigned int i=0;i<lvl->spawnpoints.size();i++)
    {
        if(lvl->spawnpoints[i].id == 0)
        {
            Position.set(lvl->spawnpoints[i].Position);
            Rotation.y = lvl->spawnpoints[i].Direction;
            collObj->setRigidPos(Position.x,Position.y,Position.z);
            collObj->setRigidRot(0,Rotation.y,0);
        }
    }
}

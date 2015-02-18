////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiCamera.h"

saiVec3 saiCamera::rot;
saiVec3 saiCamera::pos;

//CAMERA
saiCamera::saiCamera()
{
    pos.z = -50;
    speed = 0.9f;
    mouseSpeed = 0.3f;
    pi = 3.141592654f;
    Mode = SAI_CAM_PLAYER;
}

saiCamera::~saiCamera()
{

}

void saiCamera::moveUp(float dir)
{
    float radY = (rot.x + dir)*pi/180.0;
    pos.y += sin(radY)*speed;
}

void saiCamera::moveTo(float dir)
{
    float rad = (rot.y + dir)*pi/180.0;
    pos.x -= sin(rad)*speed;
    pos.z -= cos(rad)*speed;
}

void saiCamera::update()
{
    //if there is  no player object
    //similar to player update
    if(Mode == SAI_CAM_SPECTATOR)
    {
        rot.y += mouseSpeed*(saiOptions::getConfig().m_iScreenCenterX - saiInput::keyMap.mousePosX);
        rot.x += mouseSpeed*(saiOptions::getConfig().m_iScreenCenterY - saiInput::keyMap.mousePosY);
        if(rot.x > 90.0)
            rot.x = 90.0;
        if(rot.x < -90.0)
            rot.x = -90.0;
        if(rot.y < 0.0)
            rot.y += 360.0;
        if(rot.y > 360.0)
            rot.y -= 360.0;
        if(saiInput::keyMap.up)
        {
            moveTo(0.0);
            moveUp(0.0);
        }
        else if(saiInput::keyMap.down)
        {
            moveTo(180.0);
            moveUp(180.0);
        }
        if(saiInput::keyMap.left)
        {
            moveTo(90.0);
        }
        else if(saiInput::keyMap.right)
        {
            moveTo(270.0);
        }
        saiInput::warpMouse(saiOptions::getConfig().m_iScreenCenterX,saiOptions::getConfig().m_iScreenCenterY);
    }

    //rotate the scene
    glRotatef(-rot.x,1,0,0);
    glRotatef(-rot.y,0,1,0);
    glRotatef(-rot.z,0,0,1);
}



void saiCamera::applyCameraMatrix()
{
    //translate scene
    glTranslatef(-pos.x,-pos.y,-pos.z);
}

saiVec3 saiCamera::getDirection()
{
    return (saiVec3(-cos(rot.x*pi/180.0)*sin(rot.y*pi/180.0),sin(rot.x*pi/180.0),-cos(rot.x*pi/180.0)*cos(rot.y*pi/180.0)));
}

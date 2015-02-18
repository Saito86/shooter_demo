////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _CAMERA_H
#define _CAMERA_H

#include "saiBase.h"
#include "saiOption.h"
#include "saiInput.h"
#include "saiMath.h"

enum saiCameraMode
{
    SAI_CAM_PLAYER,
    SAI_CAM_SPECTATOR,
    SAI_CAM_INACTIVE
};

//todo
//needed for octree
class saiFrustum
{
    public:
    private:
};

class saiCamera
{
    public:
        saiCamera();
        ~saiCamera();
        void update();
        void applyCameraMatrix();
        void moveTo(float dir);
        static saiVec3 pos;
        static saiVec3 rot;
        saiVec3 getDirection();
        int Mode;
    private:
        void moveUp(float dir);
        float speed;
        float mouseSpeed;
        float pi;
};

#endif // _CAMERA_H


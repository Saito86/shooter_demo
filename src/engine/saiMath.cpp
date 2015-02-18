////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiMath.h"

float randomFloat()
{
    return (float)rand() / ((float)RAND_MAX + 1);
}

float linearInterpolate(float a,float b,float i)
{
    return(a*(1-i) + b*i);
}

float getDistance(saiVec3 v1,saiVec3 v2)
{
    float xd = v2.x -v1.x;
    float yd = v2.y -v1.y;
    float zd = v2.z -v1.z;
    return sqrtf(xd*xd + yd*yd + zd*zd);
}

void computeQuatW(glm::quat& quat)
{
    float t = 1.0f - (quat.x*quat.x) - (quat.y*quat.y) - (quat.z*quat.z);
    if(t< 0.0f)
    {
        quat.w = 0.0f;
    }
    else
    {
        quat.w = -sqrtf(t);
    }
}

//Vector 3d
saiVec3::saiVec3()
{
    x = y = z =0;
}
saiVec3::saiVec3(float a)
{
    x = y = z = a;
}

saiVec3::saiVec3(float a,float b,float c)
{
    x = a;
    y = b;
    z = c;
}

void saiVec3::set(float a,float b,float c)
{
    x = a;
    y = b;
    z = c;
}

void saiVec3::set(const saiVec3& v2)
{
    x = v2.x;
    y = v2.y;
    z = v2.z;
}

float saiVec3::getDotProduct(const saiVec3& v2)
{
    return (x*v2.x + y*v2.y + z*v2.z);
}

saiVec3 saiVec3::getCrossProduct(const saiVec3& v2)
{
    return (saiVec3(y*v2.z-z*v2.y,x*v2.z-z*v2.x,x*v2.y-y*v2.x));
}

float saiVec3::getLength()
{
    return sqrt(x*x + y*y + z*z);
}

void saiVec3::normalize()
{
    float len = getLength();
    if(len != 0)
    {
        x /= len;
        y /= len;
        z /= len;
    }
}

saiVec3 saiVec3::operator+(const saiVec3& v2)
{
    return saiVec3(x+v2.x,y+v2.y,z+v2.z);
}

saiVec3 saiVec3::operator-(const saiVec3& v2)
{
    return saiVec3(x-v2.x,y-v2.y,z-v2.z);
}

saiVec3 saiVec3::operator*(float n)
{
    return saiVec3(x*n,y*n,z*n);
}

saiVec3 saiVec3::operator/(float n)
{
    if(n != 0)
        return saiVec3(x/n,y/n,z/n);
    else
    {
        std::cout << "Error: division by Zero in Vector3 divide-operator\n";
        return saiVec3();
    }
}

bool saiVec3::operator==(const saiVec3 v2)
{
    return (x==v2.x && y==v2.y && z==v2.z);
}

bool saiVec3::operator!=(const saiVec3 v2)
{
    return (x!=v2.x && y!=v2.y && z!=v2.z);
}

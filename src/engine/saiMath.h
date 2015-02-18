////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _MATH_H
#define _MATH_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

float randomFloat();
float linearInterpolate(float a,float b,float i);
void computeQuatW(glm::quat& quat);

class saiVec3
{
    public:
        saiVec3();
        saiVec3(float a);
        saiVec3(float a,float b,float c);
        void set(float a,float b,float c);
        void set(const saiVec3& v2);
        float x,y,z;
        float getDotProduct(const saiVec3& v2);
        saiVec3 getCrossProduct(const saiVec3& v2);
        float getLength();
        void normalize();
        saiVec3 operator+(const saiVec3& v2);
        saiVec3 operator-(const saiVec3& v2);
        saiVec3 operator*(float n);
        saiVec3 operator/(float n);
        bool operator==(const saiVec3 v2);
        bool operator!=(const saiVec3 v2);
    private:
};

float getDistance(saiVec3 v1,saiVec3 v2);

#endif // _MATH_H

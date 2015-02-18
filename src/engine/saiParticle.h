////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <algorithm>
#include "saiBase.h"
#include "saiMath.h"
#include "saiMaterial.h"
#include "saiRenderable.h"
#include "saiCamera.h"

class saiParticlePoint
{
    public:
        saiVec3 m_Pos;
        saiVec3 m_Vel;
        float m_fSize;
        bool operator<(const saiParticlePoint& p2)const;
};

class saiParticle : public saiRenderable
{
    public:
        saiParticle(saiVec3 p_Pos,saiVec3 p_Dir,int p_nNum,float rand,saiMaterial* p_Mat,float p_fLifetime,float p_fSize,saiVec3 p_startCol,saiVec3 p_endCol);
        virtual ~saiParticle();
        void render(float fDeltaTime);
        bool m_bIsFinished;
    private:
        //Array of particles
        std::vector<saiParticlePoint> m_aParticles;
        //number of Particles
        int m_nNum;
        float m_fLifetime;
        float m_fSize;
        float m_fCurrSize;
        float m_fAge;
        saiVec3 m_Pos;
        saiVec3 m_StartColor;
        saiVec3 m_EndColor;
        saiVec3 m_CurrColor;
        float m_fStartAlpha;
        float m_fCurrAlpha;
};

class saiParticleManager
{
    public:
        static bool init();
        static void cleanup();
        static void render(float fDeltaTime);
        static void addParticle(saiParticle* p_Particle);
    private:
        static std::vector<saiParticle*> s_vecParticles;
};

#endif // _PARTICLE_H

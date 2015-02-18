////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiParticle.h"

bool saiParticlePoint::operator<(const saiParticlePoint& p2) const
{
    float d1 = getDistance(saiCamera::pos,m_Pos);
    float d2 = getDistance(saiCamera::pos,p2.m_Pos);
    if(d1 < d2)
        return true;
    else
        return false;
}

//Particle----------------------------------------
saiParticle::saiParticle(saiVec3 p_Pos,saiVec3 p_Dir,int p_nNum,float rand,saiMaterial* p_Mat,float p_fLifetime,float p_fSize,saiVec3 p_startCol,saiVec3 p_endCol)
{
    m_nNum = p_nNum;
    m_fLifetime = p_fLifetime;
    m_fSize = p_fSize;
    m_fCurrSize = p_fSize;
    m_Pos = p_Pos;
    mat = p_Mat;
    m_StartColor = p_startCol;
    m_EndColor = p_endCol;
    m_CurrColor = p_startCol;
    m_fStartAlpha = 1.0;
    m_fCurrAlpha = 1.0;
    m_fAge = 0.0;
    m_bIsFinished = false;
    for(int i=0;i<m_nNum;i++)
    {
        saiParticlePoint p;
        p.m_Pos = p_Pos;
        float a = randomFloat();
        float a1 = randomFloat();
        float b = randomFloat();
        float b1 = randomFloat();
        float c = randomFloat();
        float c1 = randomFloat();
        saiVec3 newDir = saiVec3(p_Dir.x*a,p_Dir.y*b,p_Dir.z*c); //every particle should have slightly different speed
        p.m_Vel = newDir*0.5 + saiVec3(a-a1,b-b1,c-c1)*0.001;//adjust the direction by a randonm number
        p.m_fSize = p_fSize;
        m_aParticles.push_back(p);
    }
}

saiParticle::~saiParticle()
{
    delete mat;
}

void saiParticle::render(float fDeltaTime)
{
    m_fAge += 0.1 * fDeltaTime * 120.0;
    if(m_fAge >= m_fLifetime)
    {
        m_bIsFinished = true;
    }
    else
    {
        for(int i=0;i<m_nNum;i++)
        {
            m_aParticles[i].m_Pos = m_aParticles[i].m_Pos + m_aParticles[i].m_Vel + saiVec3(0,-0.0008,0);
        }

        std::sort(m_aParticles.begin(),m_aParticles.end());

        float inter = m_fAge / m_fLifetime;
        m_fCurrAlpha = linearInterpolate(1.0,0.0,inter);
        m_CurrColor.x = linearInterpolate(m_StartColor.x,m_EndColor.x,inter);
        m_CurrColor.y = linearInterpolate(m_StartColor.y,m_EndColor.y,inter);
        m_CurrColor.z = linearInterpolate(m_StartColor.z,m_EndColor.z,inter);
        m_fCurrSize = linearInterpolate(m_fSize,0.0,inter);

        GLdouble matr[16];
        glGetDoublev(GL_MODELVIEW_MATRIX,matr);
        saiVec3 right(matr[0],matr[4],matr[8]);
        right = right*m_fCurrSize;
        saiVec3 up(matr[1],matr[5],matr[9]);
        up = up*m_fCurrSize;

        mat->setColor(m_CurrColor.x,m_CurrColor.y,m_CurrColor.z,m_fCurrAlpha);
        mat->use();
        glDisable(GL_LIGHTING);
        for(int i=0;i<m_nNum;i++)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex3f((m_aParticles[i].m_Pos.x+right.x+up.x),(m_aParticles[i].m_Pos.y+right.y+up.y),(m_aParticles[i].m_Pos.z+right.z+up.z));
            glTexCoord2f(0,1);
            glVertex3f((m_aParticles[i].m_Pos.x-right.x+up.x),(m_aParticles[i].m_Pos.y-right.y+up.y),(m_aParticles[i].m_Pos.z-right.z+up.z));
            glTexCoord2f(1,1);
            glVertex3f((m_aParticles[i].m_Pos.x-right.x-up.x),(m_aParticles[i].m_Pos.y-right.y-up.y),(m_aParticles[i].m_Pos.z-right.z-up.z));
            glTexCoord2f(1,0);
            glVertex3f((m_aParticles[i].m_Pos.x+right.x-up.x),(m_aParticles[i].m_Pos.y+right.y-up.y),(m_aParticles[i].m_Pos.z+right.z-up.z));
            glEnd();
        }
        glEnable(GL_LIGHTING);
    }
}
//--------------------------------------------------

//Particle manager----------------------------------
std::vector<saiParticle*> saiParticleManager::s_vecParticles;

bool saiParticleManager::init()
{
    return true;
}

void saiParticleManager::cleanup()
{
    for(unsigned int i=0;i<s_vecParticles.size();i++)
    {
        delete s_vecParticles[i];
    }
}

void saiParticleManager::render(float fDeltaTime)
{
    int toDelete = -1;
    for(unsigned int i=0;i<s_vecParticles.size();i++)
    {
        if(!s_vecParticles[i]->m_bIsFinished)
            s_vecParticles[i]->render(fDeltaTime);
        else
        {
            toDelete = i;
        }
    }

    if(toDelete > -1)
    {
        s_vecParticles.erase(s_vecParticles.begin()+toDelete);
        toDelete = -1;
    }
}

void saiParticleManager::addParticle(saiParticle* p_Particle)
{
    s_vecParticles.push_back(p_Particle);
}
//--------------------------------------------------

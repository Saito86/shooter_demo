////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _ANIMATEDMODEL_H
#define _ANIMATEDMODEL_H

#include <fstream>
#include <algorithm>
#include "saiRenderable.h"
#include "saiOption.h"

//Header of the sam-file
struct saiAMHeader
{
    int nVertCount;
    int nFaceCount;
    int nFrameCount;
};

//Triangle
struct saiAMFace
{
    int nVertices[3];
    float fTexcoords[6];
};

//Vertex
struct saiAMVertex
{
    float fVertex[3];
    float fNormal[3];
};

//Animation Frame
struct saiAMFrame
{
    //Array of vertices
    saiAMVertex* aVertices;
};

//Animation
struct saiAMAnimation
{
    int nStartFrame;
    int nEndFrame;
    int nFrameRate;
    std::string sName;
};


class saiAnimatedmodel : public saiRenderable
{
    public:
        static saiAnimatedmodel* load(std::string p_sFname);
        ~saiAnimatedmodel();
        void render(float fDeltaTime);
        //Adds a Animation Definition to Model
        void addAnimation(saiAMAnimation p_aAnim);
        void addAnimation(int p_nStartFr,int p_nEndFr,int p_nFrameRate,std::string p_sName); // needs startframe, endframe, framerate and name
        //plays a animation
        bool playAnimation(unsigned int p_nId,bool p_bLoop);
        bool playAnimation(saiAMAnimation p_Ani,bool p_bLoop);
        bool playAnimation(std::string p_sName,bool p_bLoop);
        //return the id of the animation with the name p_sName
        //-1 if there is no animation
        int getAnimationIndex(std::string p_sName);
        bool isPlaying(){return m_bPlaying;}
        bool hasStopedPlaying(){return m_bStopedPlaying;}
    private:
        //private Constructor
        saiAnimatedmodel();
        //list of all animation definitions
        std::vector<saiAMAnimation> m_vecAnimations;
        int m_nFaceCount;
        int m_nVertexCount;
        int m_nFrameCount;
        saiAMFace* m_Faces;
        saiAMFrame* m_Frames;
        //final calculated Frame
        saiAMFrame m_CurrFrame;
        saiAMFrame calculateFrame(saiAMFrame p_f1,saiAMFrame p_f2,float p_fInter);
        //currently playing animation
        saiAMAnimation m_CurrAnimation;
        int m_nFra;
        int m_nNextFra;
        float m_fInterpol;
        bool m_bPlaying;
        bool m_bLooping;
        bool m_bStopedPlaying;
};

#endif // _ANIMATEDMODEL_H

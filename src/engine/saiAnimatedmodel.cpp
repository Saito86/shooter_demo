////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiAnimatedmodel.h"

saiAnimatedmodel::saiAnimatedmodel()
{
    //assign default values
    m_nFra = 0;
    m_nNextFra = 1;
    m_fInterpol = 0.0;
    m_bPlaying = false;
    m_bLooping = true;
    m_bStopedPlaying = false;
}

saiAnimatedmodel::~saiAnimatedmodel()
{
    //cleanup allocated memory
    delete[] m_Faces;
    delete[] m_Frames;
}

saiAMFrame saiAnimatedmodel::calculateFrame(saiAMFrame p_f1,saiAMFrame p_f2,float p_fInter)
{
    saiAMFrame newFrame;
    newFrame.aVertices = new saiAMVertex[m_nVertexCount];
    for(int i=0;i<m_nVertexCount;i++)
    {
        newFrame.aVertices[i].fVertex[0] = p_f2.aVertices[i].fVertex[0]*p_fInter + p_f1.aVertices[i].fVertex[0]*(1.0f-p_fInter);
        newFrame.aVertices[i].fVertex[1] = p_f2.aVertices[i].fVertex[1]*p_fInter + p_f1.aVertices[i].fVertex[1]*(1.0f-p_fInter);
        newFrame.aVertices[i].fVertex[2] = p_f2.aVertices[i].fVertex[2]*p_fInter + p_f1.aVertices[i].fVertex[2]*(1.0f-p_fInter);
    }
    return newFrame;
}

void saiAnimatedmodel::render(float fDeltaTime)
{
    if(m_bPlaying)
    {
        //compute interpolation
        m_fInterpol += ((float)m_CurrAnimation.nFrameRate/60)*60.0*fDeltaTime;

        if(m_fInterpol >= 1.0f)//if one animation frame is completely played
        {
            m_nFra++;
            if(m_nFra > m_CurrAnimation.nEndFrame)
            {
                m_nFra = m_CurrAnimation.nStartFrame;
                if(!m_bLooping)
                {
                    m_bPlaying = false;
                    m_bStopedPlaying = true;
                }
            }
            m_nNextFra = m_nFra + 1;
            if(m_nNextFra > m_CurrAnimation.nEndFrame)
                m_nNextFra = m_CurrAnimation.nStartFrame;
            m_fInterpol = 0.0f;
        }
        //calculate final frame by interpolating
        m_CurrFrame = calculateFrame(m_Frames[m_nFra],m_Frames[m_nNextFra],m_fInterpol);
    }

    glPushMatrix();
    glTranslatef(Position.x,Position.y,Position.z);
    glRotatef(Rotation.x,1,0,0);
    glRotatef(Rotation.y,0,1,0);
    glRotatef(Rotation.z,0,0,1);
    glScalef(Size.x,Size.y,Size.z);
    if(mat != NULL)
        mat->use();
    glColor4f(1.0,1.0,1.0,1.0);

    //disable lighting
    //because the normals in the .sam file are not correct yet
    glDisable(GL_LIGHTING);
    for(int i=0;i<m_nFaceCount;i++)
    {
        glBegin(GL_TRIANGLES);
        glTexCoord2f(m_Faces[i].fTexcoords[0],m_Faces[i].fTexcoords[1]);
        glNormal3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[2],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[2]);
        glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[2]);
        glTexCoord2f(m_Faces[i].fTexcoords[2],m_Faces[i].fTexcoords[3]);
        glNormal3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[2],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[2]);
        glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[2]);
        glTexCoord2f(m_Faces[i].fTexcoords[4],m_Faces[i].fTexcoords[5]);
        glNormal3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[2],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[2]);
        glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[2]);
        glEnd();

        //draw Normals
        if(saiOptions::bDebugView)
        {
            float nSize = 0.05;
            glBegin(GL_LINES);
            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[2]);
            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[0] + m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[0]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[1] + m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[1]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fVertex[2] + m_CurrFrame.aVertices[m_Faces[i].nVertices[0]].fNormal[2]*nSize);

            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[2]);
            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[0] + m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[0]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[1] + m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[1]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fVertex[2] + m_CurrFrame.aVertices[m_Faces[i].nVertices[1]].fNormal[2]*nSize);

            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[0],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[1],m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[2]);
            glVertex3f(m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[0] + m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[0]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[1] + m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[1]*nSize,
                       m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fVertex[2] + m_CurrFrame.aVertices[m_Faces[i].nVertices[2]].fNormal[2]*nSize);
            glEnd();
        }
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void saiAnimatedmodel::addAnimation(saiAMAnimation p_aAnim)
{
    m_vecAnimations.push_back(p_aAnim);
}
void saiAnimatedmodel::addAnimation(int p_nStartFr,int p_nEndFr,int p_nFrameRate,std::string p_sName)
{
    saiAMAnimation anim;
    anim.nStartFrame = p_nStartFr;
    anim.nEndFrame = p_nEndFr;
    anim.nFrameRate = p_nFrameRate;
    anim.sName = p_sName;
    m_vecAnimations.push_back(anim);
}

bool saiAnimatedmodel::playAnimation(unsigned int p_nId,bool p_bLoop)
{
    if(p_nId < m_vecAnimations.size())
    {
        m_CurrAnimation = m_vecAnimations[p_nId];
        m_nFra = m_CurrAnimation.nStartFrame;
        m_nNextFra = m_nFra+1;
        m_bLooping = p_bLoop;
        m_bPlaying = true;
        if(p_bLoop)
            m_bStopedPlaying = true;
        else
            m_bStopedPlaying = false;
        return true;
    }
    else
    {
        std::cout << "No animation with id " << p_nId << std::endl;
        return false;
    }
}

bool saiAnimatedmodel::playAnimation(saiAMAnimation p_Ani,bool p_bLoop)
{
    m_CurrAnimation = p_Ani;
    m_nFra = m_CurrAnimation.nStartFrame;
    m_nNextFra = m_nFra+1;
    m_bLooping = p_bLoop;
    m_bPlaying = true;
    if(p_bLoop)
        m_bStopedPlaying = true;
    else
        m_bStopedPlaying = false;
    return true;
}

bool saiAnimatedmodel::playAnimation(std::string p_sName,bool p_bLoop)
{
    for(unsigned int i=0;i<m_vecAnimations.size();i++)
    {
        if(m_vecAnimations[i].sName == p_sName)
        {
            m_CurrAnimation = m_vecAnimations[i];
            m_nFra = m_CurrAnimation.nStartFrame;
            m_nNextFra = m_nFra+1;
            m_bLooping = p_bLoop;
            m_bPlaying = true;
            if(p_bLoop)
                m_bStopedPlaying = true;
            else
                m_bStopedPlaying = false;
            return true;
        }
    }
    std::cout << "No animation with name: " << p_sName << std::endl;
    return false;
}

int saiAnimatedmodel::getAnimationIndex(std::string p_sName)
{
    for(unsigned int i=0;i<m_vecAnimations.size();i++)
    {
        if(m_vecAnimations[i].sName == p_sName)
        {
            return i;
        }
    }
    return -1;
}

saiAnimatedmodel* saiAnimatedmodel::load(std::string p_sFname)
{
    std::string path = saiOptions::getPaths().f_sModelpath + p_sFname + ".sam";
    std::ifstream file;
    saiAnimatedmodel* newMdl = new saiAnimatedmodel();

    //allocate memory for the header
    saiAMHeader header;

    //load binary file
    file.open(path.c_str(),std::ios::in|std::ios::binary);
    if(file.fail())
    {
        std::cout << "Error loading model " << path << std::endl;
        delete newMdl;
        return NULL;
    }
    file.read((char*)&header,sizeof(saiAMHeader));
    newMdl->m_nVertexCount = header.nVertCount;
    newMdl->m_nFaceCount = header.nFaceCount;
    newMdl->m_nFrameCount = header.nFrameCount;
    newMdl->m_Faces = new saiAMFace[header.nFaceCount];
    newMdl->m_Frames = new saiAMFrame[header.nFrameCount];
    file.seekg(sizeof(header),std::ios::beg);
    file.read((char*)newMdl->m_Faces,header.nFaceCount*sizeof(saiAMFace));
    for(int i=0;i<header.nFrameCount;i++)
    {
        file.seekg(i*header.nVertCount*sizeof(saiAMVertex) + header.nFaceCount*sizeof(saiAMFace) + sizeof(header),std::ios::beg);
        newMdl->m_Frames[i].aVertices = new saiAMVertex[header.nVertCount];
        file.read((char*)newMdl->m_Frames[i].aVertices,header.nVertCount*sizeof(saiAMVertex));
    }

    //rescale model to meters
    //needed for bullet
    for(int i=0;i<newMdl->m_nFrameCount;i++)
    {
        for(int j=0;j<newMdl->m_nVertexCount;j++)
        {
            newMdl->m_Frames[i].aVertices[j].fVertex[0] *= 0.01;
            newMdl->m_Frames[i].aVertices[j].fVertex[1] *= 0.01;
            newMdl->m_Frames[i].aVertices[j].fVertex[2] *= 0.01;
        }
    }

    //create default animation
    saiAMAnimation anim;
    anim.nStartFrame = 0;
    anim.nEndFrame = header.nFrameCount-1;
    anim.nFrameRate = 30; //30fps animation
    anim.sName = "default";
    newMdl->addAnimation(anim);
    newMdl->playAnimation(0,true);
    file.close();
    return newMdl;
}

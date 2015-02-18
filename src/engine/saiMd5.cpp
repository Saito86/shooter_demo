////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiMd5.h"

//Animation
saiMD5Animation::saiMD5Animation()
: m_iMD5Version( 0 )
, m_iNumFrames( 0 )
, m_iNumJoints( 0 )
, m_iFramRate( 0 )
, m_iNumAnimatedComponents( 0 )
, m_fAnimDuration( 0 )
, m_fFrameDuration( 0 )
, m_fAnimTime( 0 )
{

}

saiMD5Animation::~saiMD5Animation()
{}

bool saiMD5Animation::LoadAnimation( const std::string& filename )
{
    std::string path = saiOptions::getPaths().f_sAnimationpath + filename + ".md5anim";

    m_JointInfos.clear();
    m_Bounds.clear();
    m_BaseFrames.clear();
    m_Frames.clear();
    m_AnimatedSkeleton.m_Joints.clear();
    m_iNumFrames = 0;

    std::vector<std::string> lines = loadTextfile(path);



    for(unsigned int i=0;i<lines.size();++i)
    {
        if(lines[i].c_str()[0] == 'n' && lines[i].c_str()[1] == 'u' &&  lines[i].c_str()[2] == 'm' &&
           lines[i].c_str()[3] == 'F' && lines[i].c_str()[4] == 'r' && lines[i].c_str()[5] == 'a')
        {
            int nf;
            sscanf(lines[i].c_str(),"numFrames %i",&nf);
            m_iNumFrames = nf;
        }
        else if(lines[i].c_str()[0] == 'n' && lines[i].c_str()[1] == 'u' &&  lines[i].c_str()[2] == 'm' &&
                lines[i].c_str()[3] == 'J' && lines[i].c_str()[4] == 'o' && lines[i].c_str()[5] == 'i')
        {
            int nj;
            sscanf(lines[i].c_str(),"numJoints %i",&nj);
            m_iNumJoints = nj;
        }
        else if(lines[i].c_str()[0] == 'f' && lines[i].c_str()[1] == 'r' &&  lines[i].c_str()[2] == 'a' &&
                lines[i].c_str()[3] == 'm' && lines[i].c_str()[4] == 'e' && lines[i].c_str()[5] == 'R')
        {
            int fr;
            sscanf(lines[i].c_str(),"frameRate %i",&fr);
            m_iFramRate = fr;
        }
        else if(lines[i].c_str()[0] == 'n' && lines[i].c_str()[1] == 'u' &&  lines[i].c_str()[2] == 'm' &&
                lines[i].c_str()[3] == 'A' && lines[i].c_str()[4] == 'n' && lines[i].c_str()[5] == 'i')
        {
            int na;
            sscanf(lines[i].c_str(),"numAnimatedComponents %i",&na);
            m_iNumAnimatedComponents = na;
        }
        else if(lines[i].c_str()[0] == 'h' && lines[i].c_str()[1] == 'i' &&  lines[i].c_str()[2] == 'e' &&
                lines[i].c_str()[3] == 'r' && lines[i].c_str()[4] == 'a' && lines[i].c_str()[5] == 'r')
        {
            i++;
            while(lines[i].c_str()[0] != '}')
            {
                char nm[32];
                int pid;
                int fl;
                int st;
                sscanf(lines[i].c_str(),"\t%s\t %i %i %i",nm,&pid,&fl,&st);
                std::string nam(nm);
                nam.erase(nam.begin());
                nam.erase(nam.end()-1);


                JointInfo joint;
                joint.m_Name = nam;
                joint.m_ParentID = pid;
                joint.m_Flags = fl;
                joint.m_StartIndex = st;

                m_JointInfos.push_back(joint);

                i++;
            }

        }
        else if(lines[i].c_str()[0] == 'b' && lines[i].c_str()[1] == 'o' &&  lines[i].c_str()[2] == 'u' &&
                lines[i].c_str()[3] == 'n' && lines[i].c_str()[4] == 'd' && lines[i].c_str()[5] == 's')
        {
            i++;
            while(lines[i].c_str()[0] != '}')
            {
                float minx,miny,minz;
                float maxx,maxy,maxz;
                sscanf(lines[i].c_str(),"\t( %f %f %f ) ( %f %f %f )",&minx,&miny,&minz,&maxx,&maxy,&maxz);
                Bound bound;
                bound.m_Min.x = minx;
                bound.m_Min.y = miny;
                bound.m_Min.z = minz;
                bound.m_Max.x = maxx;
                bound.m_Max.y = maxy;
                bound.m_Max.z = maxz;
                m_Bounds.push_back(bound);
                i++;
            }
        }
        else if(lines[i].c_str()[0] == 'b' && lines[i].c_str()[1] == 'a' &&  lines[i].c_str()[2] == 's' &&
                lines[i].c_str()[3] == 'e' && lines[i].c_str()[4] == 'f' && lines[i].c_str()[5] == 'r')
        {
            i++;
            while(lines[i].c_str()[0] != '}')
            {
                float px,py,pz;
                float rx,ry,rz;
                sscanf(lines[i].c_str(),"\t( %f %f %f ) ( %f %f %f )",&px,&py,&pz,&rx,&ry,&rz);
                BaseFrame baseFrame;
                baseFrame.m_Pos.x = px;
                baseFrame.m_Pos.y = py;
                baseFrame.m_Pos.z = pz;
                baseFrame.m_Orient.x = rx;
                baseFrame.m_Orient.y = ry;
                baseFrame.m_Orient.z = rz;
                m_BaseFrames.push_back(baseFrame);
                i++;
            }
        }
        else if(lines[i].c_str()[0] == 'f' && lines[i].c_str()[1] == 'r' &&  lines[i].c_str()[2] == 'a' &&
                lines[i].c_str()[3] == 'm' && lines[i].c_str()[4] == 'e' && lines[i].c_str()[5] == ' ')
        {
            i++;
            FrameData frame;
            while(lines[i].c_str()[0] != '}')
            {
                std::istringstream iss(lines[i]);
                std::vector<std::string> tokens;
                copy(std::istream_iterator<std::string>(iss),
                std::istream_iterator<std::string>(),
                std::back_inserter<std::vector<std::string> >(tokens));

                for(unsigned int j=0;j<tokens.size();++j)
                {
                    float frameData = std::atof(tokens[j].c_str());
                    frame.m_FrameData.push_back(frameData);
                }
                i++;
            }
            m_Frames.push_back(frame);
            BuildFrameSkeleton(m_Skeletons,m_JointInfos,m_BaseFrames,frame);
        }
    }

    // Make sure there are enough joints for the animated skeleton.
    m_AnimatedSkeleton.m_Joints.assign(m_iNumJoints, SkeletonJoint() );

    m_fFrameDuration = 1.0f / (float)m_iFramRate;
    m_fAnimDuration = ( m_fFrameDuration * (float)m_iNumFrames );
    m_fAnimTime = 0.0f;

    assert( m_JointInfos.size() == m_iNumJoints );
    assert( m_Bounds.size() == m_iNumFrames );
    assert( m_BaseFrames.size() == m_iNumJoints );
    assert( m_Frames.size() == m_iNumFrames );
    assert( m_Skeletons.size() == m_iNumFrames );

    return true;
}

void saiMD5Animation::BuildFrameSkeleton( FrameSkeletonList& skeletons, const JointInfoList& jointInfos, const BaseFrameList& baseFrames, const FrameData& frameData )
{
    FrameSkeleton skeleton;

    for ( unsigned int i = 0; i < jointInfos.size(); ++i )
    {
        unsigned int j = 0;

        const JointInfo& jointInfo = jointInfos[i];
        // Start with the base frame position and orientation.
        SkeletonJoint animatedJoint = baseFrames[i];

        animatedJoint.m_Parent = jointInfo.m_ParentID;

        if ( jointInfo.m_Flags & 1 ) // Pos.x
        {
            animatedJoint.m_Pos.x = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }
        if ( jointInfo.m_Flags & 2 ) // Pos.y
        {
            animatedJoint.m_Pos.y = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }
        if ( jointInfo.m_Flags & 4 ) // Pos.x
        {
            animatedJoint.m_Pos.z  = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }
        if ( jointInfo.m_Flags & 8 ) // Orient.x
        {
            animatedJoint.m_Orient.x = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }
        if ( jointInfo.m_Flags & 16 ) // Orient.y
        {
            animatedJoint.m_Orient.y = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }
        if ( jointInfo.m_Flags & 32 ) // Orient.z
        {
            animatedJoint.m_Orient.z = frameData.m_FrameData[ jointInfo.m_StartIndex + j++ ];
        }

        computeQuatW( animatedJoint.m_Orient );

        if ( animatedJoint.m_Parent >= 0 ) // Has a parent joint
        {
            SkeletonJoint& parentJoint = skeleton.m_Joints[animatedJoint.m_Parent];
            glm::vec3 rotPos = parentJoint.m_Orient * animatedJoint.m_Pos;

            animatedJoint.m_Pos = parentJoint.m_Pos + rotPos;
            animatedJoint.m_Orient = parentJoint.m_Orient * animatedJoint.m_Orient;

            animatedJoint.m_Orient = glm::normalize( animatedJoint.m_Orient );
        }

        skeleton.m_Joints.push_back(animatedJoint);
    }

    skeletons.push_back(skeleton);
}

void saiMD5Animation::Update( float fDeltaTime )
{
    if ( m_iNumFrames < 1 ) return;

    m_fAnimTime += fDeltaTime;

    while ( m_fAnimTime > m_fAnimDuration ) m_fAnimTime -= m_fAnimDuration;
    while ( m_fAnimTime < 0.0f ) m_fAnimTime += m_fAnimDuration;

    // Figure out which frame we're on
    float fFramNum = m_fAnimTime * (float)m_iFramRate;
    int iFrame0 = (int)floorf( fFramNum );
    int iFrame1 = (int)ceilf( fFramNum );
    iFrame0 = iFrame0 % m_iNumFrames;
    iFrame1 = iFrame1 % m_iNumFrames;

    float fInterpolate = fmodf( m_fAnimTime, m_fFrameDuration ) / m_fFrameDuration;

    InterpolateSkeletons( m_AnimatedSkeleton, m_Skeletons[iFrame0], m_Skeletons[iFrame1], fInterpolate );
}

void saiMD5Animation::InterpolateSkeletons( FrameSkeleton& finalSkeleton, const FrameSkeleton& skeleton0, const FrameSkeleton& skeleton1, float fInterpolate )
{
    for ( int i = 0; i < m_iNumJoints; ++i )
    {
        SkeletonJoint& finalJoint = finalSkeleton.m_Joints[i];
        const SkeletonJoint& joint0 = skeleton0.m_Joints[i];
        const SkeletonJoint& joint1 = skeleton1.m_Joints[i];

        finalJoint.m_Parent = joint0.m_Parent;

        finalJoint.m_Pos = glm::lerp( joint0.m_Pos, joint1.m_Pos, fInterpolate );
        finalJoint.m_Orient = glm::mix( joint0.m_Orient, joint1.m_Orient, fInterpolate );
    }
}

void saiMD5Animation::Render()
{
    glPointSize( 5.0f );
    glColor3f( 1.0f, 0.0f, 0.0f );

    glPushAttrib( GL_ENABLE_BIT );

    glDisable(GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );

    const SkeletonJointList& joints = m_AnimatedSkeleton.m_Joints;

    // Draw the joint positions
    glBegin( GL_POINTS );
    {
        for ( unsigned int i = 0; i < joints.size(); ++i )
        {
            glVertex3fv( glm::value_ptr(joints[i].m_Pos) );
        }
    }
    glEnd();

    // Draw the bones
    glColor3f( 0.0f, 1.0f, 0.0f );
    glBegin( GL_LINES );
    {
        for ( unsigned int i = 0; i < joints.size(); ++i )
        {
            const SkeletonJoint& j0 = joints[i];
            if ( j0.m_Parent != -1 )
            {
                const SkeletonJoint& j1 = joints[j0.m_Parent];
                glVertex3fv( glm::value_ptr(j0.m_Pos) );
                glVertex3fv( glm::value_ptr(j1.m_Pos) );
            }
        }
    }
    glEnd();

    glPopAttrib();
}

//Model
saiMd5::saiMd5()
{
    m_bHasAnimation = false;
}

saiMd5::~saiMd5()
{
    for(unsigned int i=0;i<m_vecMeshes.size();i++)
    {
        delete m_vecMeshes[i].m_Material;
    }
}

void saiMd5::update(float fDeltaTime)
{
    if(m_bHasAnimation)
    {
        m_Animation.Update(fDeltaTime);
        const saiMD5Animation::FrameSkeleton& skeleton = m_Animation.GetSkeleton();
        for(unsigned int i=0;i<m_vecMeshes.size();++i)
        {
            prepareMesh(m_vecMeshes[i],skeleton);
        }
    }
}

void saiMd5::render()
{
    glPushMatrix();
    glTranslatef(Position.x,Position.y,Position.z);
    glRotatef(Rotation.x-90,1,0,0);
    glRotatef(Rotation.y,0,1,0);
    glRotatef(Rotation.z,0,0,1);
    glScalef(Size.x,Size.y,Size.z);

    for(unsigned int i=0;i<m_vecMeshes.size();++i)
    {
        renderMesh(m_vecMeshes[i]);
    }

    glPopMatrix();
}

void saiMd5::renderMesh(const Mesh& mesh)
{
    glColor3f( 1.0f, 1.0f, 1.0f );
    //glDisable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    mesh.m_Material->use();
    glVertexPointer( 3, GL_FLOAT, 0, &(mesh.m_vecPositionBuffer[0]) );
    glNormalPointer( GL_FLOAT, 0, &(mesh.m_vecNormalBuffer[0]) );
    glTexCoordPointer( 2, GL_FLOAT, 0, &(mesh.m_vecTex2DBuffer[0]) );

    glDrawElements( GL_TRIANGLES, mesh.m_vecIndexBuffer.size(), GL_UNSIGNED_INT, &(mesh.m_vecIndexBuffer[0]) );

    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    /*
    glBegin(GL_LINES);
    for(unsigned int i=0;i<m_vecJoints.size();++i)
    {
        const Joint& j0 = m_vecJoints[i];
        if(j0.m_ParentId != -1)
        {
            const Joint& j1 = m_vecJoints[j0.m_ParentId];
            glVertex3fv(glm::value_ptr(j0.m_Pos));
            glVertex3fv(glm::value_ptr(j1.m_Pos));
        }
    }
    glEnd();

    glBegin( GL_LINES );
    {
        for ( unsigned int i = 0; i < mesh.m_vecPositionBuffer.size(); ++i )
        {
            glm::vec3 p0 = mesh.m_vecPositionBuffer[i];
            glm::vec3 p1 = ( mesh.m_vecPositionBuffer[i] + mesh.m_vecNormalBuffer[i] );

            glVertex3fv( glm::value_ptr(p0) );
            glVertex3fv( glm::value_ptr(p1) );
        }
    }
    glEnd();
    */
}


void saiMd5::prepareMesh(Mesh& mesh)
{
    mesh.m_vecPositionBuffer.clear();
    mesh.m_vecTex2DBuffer.clear();

    for(unsigned int i=0;i<mesh.m_vecVertices.size();++i)
    {
        glm::vec3 finalPos(0);
        Vertex& vert = mesh.m_vecVertices[i];
        vert.m_Pos = glm::vec3(0);
        vert.m_Normal = glm::vec3(0);

        for(int j=0;j<vert.m_WeightCount; ++j)
        {
            Weight& weight = mesh.m_vecWeights[vert.m_StartWeight + j];
            Joint& joint = m_vecJoints[weight.m_JointId];
            glm::vec3 rotPos = joint.m_Orient * weight.m_Pos;
            vert.m_Pos += (joint.m_Pos + rotPos)  * weight.m_Bias;
        }

        mesh.m_vecPositionBuffer.push_back(vert.m_Pos);
        mesh.m_vecTex2DBuffer.push_back(vert.m_Tex0);
    }
}

void saiMd5::prepareMesh(Mesh& mesh,const saiMD5Animation::FrameSkeleton& skel)
{
    for(unsigned int i=0;i<mesh.m_vecVertices.size();++i)
    {
        const Vertex& vert = mesh.m_vecVertices[i];
        glm::vec3& pos = mesh.m_vecPositionBuffer[i];
        glm::vec3& normal = mesh.m_vecNormalBuffer[i];

        pos = glm::vec3(0);
        normal = glm::vec3(0);

        for(int j=0;j<vert.m_WeightCount;++j)
        {
            const Weight& weight  = mesh.m_vecWeights[vert.m_StartWeight + j];
            const saiMD5Animation::SkeletonJoint& joint = skel.m_Joints[weight.m_JointId];
            glm::vec3 rotPos = joint.m_Orient * weight.m_Pos;
            pos += (joint.m_Pos + rotPos) * weight.m_Bias;
            normal += (joint.m_Orient * vert.m_Normal) * weight.m_Bias;
        }
    }
}

void saiMd5::prepareNormals(Mesh& mesh)
{
    mesh.m_vecNormalBuffer.clear();
    for(unsigned int i=0;i<mesh.m_vecTriangles.size();++i)
    {
        glm::vec3 v0 = mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[0]].m_Pos;
        glm::vec3 v1 = mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[1]].m_Pos;
        glm::vec3 v2 = mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[2]].m_Pos;

        glm::vec3 normal = glm::cross(v2-v0,v1-v0);

        mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[0]].m_Normal += normal;
        mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[1]].m_Normal += normal;
        mesh.m_vecVertices[mesh.m_vecTriangles[i].m_Indices[2]].m_Normal += normal;
    }

    for(unsigned int i=0; i<mesh.m_vecVertices.size();++i)
    {
        Vertex& vert = mesh.m_vecVertices[i];

        glm::vec3 normal = glm::normalize(vert.m_Normal);
        mesh.m_vecNormalBuffer.push_back(normal);

        vert.m_Normal = glm::vec3(0);
        for(int j=0;j<vert.m_WeightCount;++j)
        {
            const Weight& weight = mesh.m_vecWeights[vert.m_StartWeight + j];
            const Joint& joint = m_vecJoints[weight.m_JointId];
            vert.m_Normal += (normal * joint.m_Orient) * weight.m_Bias;
        }
    }
}

bool saiMd5::checkAnimation(const saiMD5Animation& animation) const
{
    if(m_iNumJoints != animation.GetNumJoints())
    {
        return false;
    }
    for(unsigned int i=0;i<m_vecJoints.size();++i)
    {
        const Joint& meshJoint = m_vecJoints[i];
        const saiMD5Animation::JointInfo& animJoint = animation.GetJointInfo(i);

        if(meshJoint.m_Name != animJoint.m_Name || meshJoint.m_ParentId != animJoint.m_ParentID)
        {
            return false;
        }
    }
    return true;
}

bool saiMd5::loadAnim(std::string fname)
{
    if(m_Animation.LoadAnimation(fname))
    {
        m_bHasAnimation = checkAnimation(m_Animation);
    }
    return m_bHasAnimation;
}

saiMd5* saiMd5::load(std::string fname)
{
    std::string filename = saiOptions::getPaths().f_sModelpath + fname + ".md5mesh";
    std::vector<std::string> lines = loadTextfile(filename);

    saiMd5* newMdl = new saiMd5();
    int numJoints;
    int numMeshes;

    for(unsigned int i=0;i<lines.size();i++)
    {
        std::size_t found = lines[i].find(" ");
        std::string param = lines[i].substr(0,found);
        if(param == "numJoints")
        {
            int num;
            sscanf(lines[i].c_str(),"numJoints %i",&num);
            newMdl->m_iNumJoints = num;
            numJoints = num;
        }
        else if(param == "numMeshes")
        {
            int num;
            sscanf(lines[i].c_str(),"numMeshes %i",&num);
            newMdl->m_iNumMeshes = num;
            numMeshes = num;
        }
        else if(param == "joints")
        {
            i++;
            while(lines[i].c_str()[0] != '}')
            {
                char nam[32];
                int parId;
                float px,py,pz;
                float rx,ry,rz;
                sscanf(lines[i].c_str(),"\t%s\t%i ( %f %f %f ) ( %f %f %f )",nam,&parId,&px,&py,&pz,&rx,&ry,&rz);
                std::string name(nam);
                name.erase(name.begin());
                name.erase(name.end()-1);

                Joint newJoint;
                newJoint.m_Name = name;
                newJoint.m_ParentId = parId;
                newJoint.m_Pos.x = px;
                newJoint.m_Pos.y = py;
                newJoint.m_Pos.z = pz;
                newJoint.m_Orient.x = rx;
                newJoint.m_Orient.y = ry;
                newJoint.m_Orient.z = rz;
                //std::cout << rx << " " << ry << " " << rz << std::endl;

                //std::cout << "vorher " << newJoint.m_Orient.x << " " << newJoint.m_Orient.y << " " << newJoint.m_Orient.z << " " << newJoint.m_Orient.w << std::endl;
                computeQuatW(newJoint.m_Orient);
                //std::cout << "nachher " << newJoint.m_Orient.x << " " << newJoint.m_Orient.y << " " << newJoint.m_Orient.z << " " << newJoint.m_Orient.w << std::endl;
                newMdl->m_vecJoints.push_back(newJoint);

                i++;
            }
        }
        else if(param == "mesh")
        {
            i++;
            Mesh newMesh;
            while(lines[i].c_str()[0] != '}')
            {
                if(lines[i].c_str()[1] == 's' && lines[i].c_str()[2] == 'h' && lines[i].c_str()[3] == 'a' && lines[i].c_str()[4] == 'd')
                {
                    char nam[32];
                    sscanf(lines[i].c_str(),"\tshader %s",nam);
                    std::string name(nam);
                    name.erase(name.begin());
                    name.erase(name.end()-1);
                    saiMaterial* newMat = saiMaterial::load(name);
                    newMesh.m_Material = newMat;
                }
                else if(lines[i].c_str()[1] == 'n' && lines[i].c_str()[2] == 'u' && lines[i].c_str()[3] == 'm' && lines[i].c_str()[4] == 'v')
                {
                    int numV;
                    sscanf(lines[i].c_str(),"\tnumverts %i",&numV);
                }
                else if(lines[i].c_str()[1] == 'v' && lines[i].c_str()[2] == 'e' && lines[i].c_str()[3] == 'r' && lines[i].c_str()[4] == 't')
                {
                    int vId;
                    float u,v;
                    int sWeight;
                    int wCount;
                    sscanf(lines[i].c_str(),"\tvert %i ( %f %f ) %i %i",&vId,&u,&v,&sWeight,&wCount);
                    Vertex newVert;
                    newVert.m_StartWeight = sWeight;
                    newVert.m_WeightCount = wCount;
                    newVert.m_Tex0.x = u;
                    newVert.m_Tex0.y = v;
                    newMesh.m_vecVertices.push_back(newVert);
                    newMesh.m_vecTex2DBuffer.push_back(newVert.m_Tex0);
                }
                else if(lines[i].c_str()[1] == 'n' && lines[i].c_str()[2] == 'u' && lines[i].c_str()[3] == 'm' && lines[i].c_str()[4] == 't')
                {
                    int numT;
                    sscanf(lines[i].c_str(),"\tnumtris %i",&numT);
                }
                else if(lines[i].c_str()[1] == 't' && lines[i].c_str()[2] == 'r' && lines[i].c_str()[3] == 'i')
                {
                    int tIndex;
                    int v1;
                    int v2;
                    int v3;
                    sscanf(lines[i].c_str(),"\ttri %i %i %i %i",&tIndex,&v1,&v2,&v3);
                    Triangle newTri;
                    newTri.m_Indices[0] = v1;
                    newTri.m_Indices[1] = v2;
                    newTri.m_Indices[2] = v3;
                    newMesh.m_vecTriangles.push_back(newTri);
                    newMesh.m_vecIndexBuffer.push_back((GLuint)newTri.m_Indices[0]);
                    newMesh.m_vecIndexBuffer.push_back((GLuint)newTri.m_Indices[1]);
                    newMesh.m_vecIndexBuffer.push_back((GLuint)newTri.m_Indices[2]);
                }
                else if(lines[i].c_str()[1] == 'n' && lines[i].c_str()[2] == 'u' && lines[i].c_str()[3] == 'm' && lines[i].c_str()[4] == 'w')
                {
                    int numW;
                    sscanf(lines[i].c_str(),"\tnumweights %i",&numW);
                }
                else if(lines[i].c_str()[1] == 'w' && lines[i].c_str()[2] == 'e' && lines[i].c_str()[3] == 'i')
                {
                    int wId,jId;
                    float wBias;
                    float w1,w2,w3;
                    sscanf(lines[i].c_str(),"\tweight %i %i %f ( %f %f %f )",&wId,&jId,&wBias,&w1,&w2,&w3);
                    Weight newWeight;
                    newWeight.m_JointId = jId;
                    newWeight.m_Bias = wBias;
                    newWeight.m_Pos.x = w1;
                    newWeight.m_Pos.y = w2;
                    newWeight.m_Pos.z = w3;
                    newMesh.m_vecWeights.push_back(newWeight);
                }
                i++;
            }
            //
            newMdl->prepareMesh(newMesh);
            newMdl->prepareNormals(newMesh);
            newMdl->m_vecMeshes.push_back(newMesh);
        }
    }

    return newMdl;
}

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _MD5_H
#define _MD5_H

#include <sstream>
#include <algorithm>
#include <iterator>
#include "saiRenderable.h"

class saiMD5Animation
{
public:
    saiMD5Animation();
    virtual ~saiMD5Animation();

    // Load an animation from the animation file
    bool LoadAnimation( const std::string& filename );
    // Update this animation's joint set.
    void Update( float fDeltaTime );
    // Draw the animated skeleton
    void Render();

    // The JointInfo stores the information necessary to build the
    // skeletons for each frame
    struct JointInfo
    {
        std::string m_Name;
        int         m_ParentID;
        int         m_Flags;
        int         m_StartIndex;
    };
    typedef std::vector<JointInfo> JointInfoList;

    struct Bound
    {
        glm::vec3   m_Min;
        glm::vec3   m_Max;
    };
    typedef std::vector<Bound> BoundList;

    struct BaseFrame
    {
        glm::vec3   m_Pos;
        glm::quat   m_Orient;
    };
    typedef std::vector<BaseFrame> BaseFrameList;

    struct FrameData
    {
        int m_iFrameID;
        std::vector<float> m_FrameData;
    };
    typedef std::vector<FrameData> FrameDataList;

    // A Skeleton joint is a joint of the skeleton per frame
    struct SkeletonJoint
    {
        SkeletonJoint()
            : m_Parent(-1)
            , m_Pos(0)
        {}

        SkeletonJoint( const BaseFrame& copy )
            : m_Pos( copy.m_Pos )
            , m_Orient( copy.m_Orient )
        {}

        int         m_Parent;
        glm::vec3   m_Pos;
        glm::quat   m_Orient;
    };
    typedef std::vector<SkeletonJoint> SkeletonJointList;

    // A frame skeleton stores the joints of the skeleton for a single frame.
    struct FrameSkeleton
    {
        SkeletonJointList   m_Joints;
    };
    typedef std::vector<FrameSkeleton> FrameSkeletonList;

    const FrameSkeleton& GetSkeleton() const
    {
        return m_AnimatedSkeleton;
    }

    int GetNumJoints() const
    {
        return m_iNumJoints;
    }

    const JointInfo& GetJointInfo( unsigned int index ) const
    {
        assert( index < m_JointInfos.size() );
        return m_JointInfos[index];
    }

protected:

    JointInfoList       m_JointInfos;
    BoundList           m_Bounds;
    BaseFrameList       m_BaseFrames;
    FrameDataList       m_Frames;
    FrameSkeletonList   m_Skeletons;    // All the skeletons for all the frames

    FrameSkeleton       m_AnimatedSkeleton;

    // Build the frame skeleton for a particular frame
    void BuildFrameSkeleton( FrameSkeletonList& skeletons, const JointInfoList& jointInfo, const BaseFrameList& baseFrames, const FrameData& frameData );
    void InterpolateSkeletons( FrameSkeleton& finalSkeleton, const FrameSkeleton& skeleton0, const FrameSkeleton& skeleton1, float fInterpolate );


private:
    int m_iMD5Version;
    int m_iNumFrames;
    int m_iNumJoints;
    int m_iFramRate;
    int m_iNumAnimatedComponents;

    float m_fAnimDuration;
    float m_fFrameDuration;
    float m_fAnimTime;
};

class saiMd5 : public saiRenderable
{
    public:
        static saiMd5* load(std::string fname);
        virtual ~saiMd5();
        void update(float fDeltaTime);
        void render();
        bool loadAnim(std::string fname);
    private:
        saiMd5();

        struct Vertex
        {
            glm::vec3 m_Pos;
            glm::vec3 m_Normal;
            glm::vec2 m_Tex0;
            int m_StartWeight;
            int m_WeightCount;
        };

        struct Triangle
        {
            int m_Indices[3];
        };

        struct Weight
        {
            int m_JointId;
            float m_Bias;
            glm::vec3 m_Pos;
        };

        struct Joint
        {
            std::string m_Name;
            int m_ParentId;
            glm::vec3 m_Pos;
            glm::quat m_Orient;
        };

        struct Mesh
        {
            saiMaterial* m_Material;
            std::vector<Vertex> m_vecVertices;
            std::vector<Triangle> m_vecTriangles;
            std::vector<Weight> m_vecWeights;
            std::vector<glm::vec3> m_vecPositionBuffer;
            std::vector<glm::vec3> m_vecNormalBuffer;
            std::vector<glm::vec2> m_vecTex2DBuffer;
            std::vector<GLuint> m_vecIndexBuffer;
        };

        int m_iNumJoints;
        int m_iNumMeshes;

        std::vector<Joint> m_vecJoints;
        std::vector<Mesh> m_vecMeshes;

        void prepareMesh(Mesh& mesh);
        void prepareMesh(Mesh& mesh,const saiMD5Animation::FrameSkeleton& skel);
        void prepareNormals(Mesh& mesh);
        void renderMesh(const Mesh& mesh);

        bool checkAnimation(const saiMD5Animation& animation) const;

        bool m_bHasAnimation;
        saiMD5Animation m_Animation;
};

#endif // _MD5_H

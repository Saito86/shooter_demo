////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _MAP_H
#define _MAP_H

#include "saiMaterial.h"
#include "saiSky.h"
#include "saiPhysics.h"
#include "saiMath.h"
#include "saiParticle.h"
#include "saiDoor.h"
#include "saiTrigger.h"
#include "saiEntity.h"
#include "saiDecal.h"
#include "saiItem.h"
#include "saiScriptManager.h"
#include "saiLight.h"
#include "saiTerrain.h"

class saiStaticMesh : public saiRenderable
{
    public:
        saiStaticMesh();
        virtual ~saiStaticMesh();
        void render();
        void setModel(saiObjModel* p_pMdl){m_pMdl = p_pMdl;}
        saiObjModel* getModel(){return m_pMdl;}
    private:
        saiObjModel* m_pMdl;
};

struct mapVertex
{
    float vertex[3];
    float normal[3];
    float color[3];
};

struct mapFace
{
    int index[3];
    float texcoord[6];
    unsigned int matId;
};

struct saiBoundingBox
{
    float Width;
    float Height;
    float Length;
    float posX,posY,posZ;
};

class saiTreeNode
{
    public:
        saiTreeNode();
        ~saiTreeNode();
        std::vector<mapFace*> indices;
        saiTreeNode* children[8];
        saiBoundingBox bBox;
        int depthLevel;
    private:
};

struct saiSpawnpoint
{
    saiVec3 Position;
    float Direction;
    std::string Name;
    int id;
};

class saiMap
{
    public:
        static saiMap* load(std::string fname);
        ~saiMap();
        void render(float fDeltaTime);
        void renderSky();
        void update(float fDeltaTime);
        std::vector<saiSpawnpoint> spawnpoints;
        std::vector<saiDecal*> m_vecDecals;
        std::vector<saiItem*> m_vecItems;
        std::string objType;
    private:
        saiMap();
        void buildOcttree();
        void buildSubtree(saiTreeNode* node);
        bool isInBoundingbox(mapFace* face,saiBoundingBox& box);
        std::vector<saiMaterial*> materials;
        std::vector<mapVertex> vertices;
        std::vector<mapFace*> faces;
        std::vector<mapFace*> collFaces;
        std::vector<saiDoor*> m_Doors;
        std::vector<saiTrigger*> m_Triggers;
        std::vector<saiEntity*> m_vecEntities;
        std::vector<saiStaticMesh*> m_vecStaticmeshes;
        std::vector<saiCollisionObject*> m_vecCollisionObjects;
        saiTreeNode* topLevelNode;
        unsigned int matColl;
        saiSkybox* skyBox;
        saiTerrain* m_Terrain;
        saiCollisionObject* mapCollision;
        bool m_bHasGeometry;
};

#endif // _LEVEL_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiMap.h"

//Staticmesh-------------------------------
saiStaticMesh::saiStaticMesh()
{
    mat = NULL;
    m_pMdl = NULL;
}

saiStaticMesh::~saiStaticMesh()
{
    if(mat != NULL)
        delete mat;
    if(m_pMdl != NULL)
        delete m_pMdl;
}

void saiStaticMesh::render()
{
    if(m_pMdl != NULL)
    {
        m_pMdl->render();
    }
}
//-----------------------------------------

//Octree-----------------------------------
saiTreeNode::saiTreeNode()
{
    children[0] = NULL;
    children[1] = NULL;
    children[2] = NULL;
    children[3] = NULL;
    children[4] = NULL;
    children[5] = NULL;
    children[6] = NULL;
    children[7] = NULL;
}

saiTreeNode::~saiTreeNode()
{
    for(int i=0;i<8;i++)
    {
        if(children[i] != NULL)
            delete children[i];
    }
}
//------------------------------------------

//Map---------------------------------------
saiMap::saiMap()
{
    topLevelNode = NULL;
    skyBox = NULL;
    mapCollision = NULL;
    objType = "level";
    m_bHasGeometry = false;
    m_Terrain = NULL;
}

saiMap::~saiMap()
{
    for(unsigned int i=0;i<materials.size();i++)
    {
        delete materials[i];
    }
    for(unsigned int i=0;i<faces.size();i++)
    {
        delete faces[i];
    }
    delete topLevelNode;
    if(skyBox != NULL)
        delete skyBox;
    if(m_Terrain != NULL)
        delete m_Terrain;
    if(mapCollision != NULL)
    {
        saiPhysics::removeCollisionObject(mapCollision);
        delete mapCollision;
    }
    for(unsigned int i=0;i<m_Doors.size();i++)
    {
        delete m_Doors[i];
    }
    for(unsigned int i=0;i<m_Triggers.size();i++)
    {
        delete m_Triggers[i];
    }
    for(unsigned int i=0;i<m_vecEntities.size();i++)
    {
        delete m_vecEntities[i];
    }
    for(unsigned int i=0;i<m_vecDecals.size();i++)
    {
        delete m_vecDecals[i];
    }
    for(unsigned int i=0;i<m_vecItems.size();i++)
    {
        delete m_vecItems[i];
    }
    for(unsigned int i=0;i<m_vecStaticmeshes.size();i++)
    {
        delete m_vecStaticmeshes[i];
    }
    for(unsigned int i=0;i<m_vecCollisionObjects.size();i++)
    {
        saiPhysics::removeCollisionObject(m_vecCollisionObjects[i]);
    }
}

void saiMap::render(float fDeltaTime)
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    for(unsigned int i=0;i<faces.size();i++)
    {
        materials[faces[i]->matId]->use();
        glBegin(GL_TRIANGLES);
        glColor3f(1.0,1.0,1.0);
        glTexCoord2f(faces[i]->texcoord[0],faces[i]->texcoord[1]);
        glNormal3f(vertices[faces[i]->index[0]].normal[0],vertices[faces[i]->index[0]].normal[1],vertices[faces[i]->index[0]].normal[2]);
        glVertex3f(vertices[faces[i]->index[0]].vertex[0],vertices[faces[i]->index[0]].vertex[1],vertices[faces[i]->index[0]].vertex[2]);
        glTexCoord2f(faces[i]->texcoord[2],faces[i]->texcoord[3]);
        glNormal3f(vertices[faces[i]->index[1]].normal[0],vertices[faces[i]->index[1]].normal[1],vertices[faces[i]->index[1]].normal[2]);
        glVertex3f(vertices[faces[i]->index[1]].vertex[0],vertices[faces[i]->index[1]].vertex[1],vertices[faces[i]->index[1]].vertex[2]);
        glTexCoord2f(faces[i]->texcoord[4],faces[i]->texcoord[5]);
        glNormal3f(vertices[faces[i]->index[2]].normal[0],vertices[faces[i]->index[2]].normal[1],vertices[faces[i]->index[2]].normal[2]);
        glVertex3f(vertices[faces[i]->index[2]].vertex[0],vertices[faces[i]->index[2]].vertex[1],vertices[faces[i]->index[2]].vertex[2]);
        glEnd();
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
    for(unsigned int i=0;i<m_Doors.size();i++)
    {
        m_Doors[i]->render(fDeltaTime);
    }
    for(unsigned int i=0;i<m_vecItems.size();i++)
    {
        m_vecItems[i]->render(fDeltaTime);
    }
    for(unsigned int i=0;i<m_vecEntities.size();i++)
    {
        m_vecEntities[i]->render();
    }
    for(unsigned int i=0;i<m_vecStaticmeshes.size();i++)
    {
        m_vecStaticmeshes[i]->render();
    }
    for(unsigned int i=0;i<m_vecDecals.size();i++)
    {
        m_vecDecals[i]->render();
    }
}

void saiMap::update(float fDeltaTime)
{
    for(unsigned int i=0;i<m_vecEntities.size();i++)
    {
        m_vecEntities[i]->update();
    }
}

void saiMap::renderSky()
{
    if(skyBox != NULL)
        skyBox->render();
}

void saiMap::buildSubtree(saiTreeNode* node)
{
    //create children
    for(int i = 0;i<8;i++)
    {
        node->children[i] = new saiTreeNode();
        node->children[i]->depthLevel = node->depthLevel + 1;
        saiBoundingBox box;
        switch(i)
        {
            case 0:
                box.posX = node->bBox.posX - (node->bBox.Width/2);
                box.posY = node->bBox.posY + (node->bBox.Height/2);
                box.posZ = node->bBox.posZ + (node->bBox.Length/2);
                break;
            case 1:
                box.posX = node->bBox.posX + (node->bBox.Width/2);
                box.posY = node->bBox.posY + (node->bBox.Height/2);
                box.posZ = node->bBox.posZ + (node->bBox.Length/2);
                break;
            case 2:
                box.posX = node->bBox.posX + (node->bBox.Width/2);
                box.posY = node->bBox.posY + (node->bBox.Height/2);
                box.posZ = node->bBox.posZ - (node->bBox.Length/2);
                break;
            case 3:
                box.posX = node->bBox.posX - (node->bBox.Width/2);
                box.posY = node->bBox.posY + (node->bBox.Height/2);
                box.posZ = node->bBox.posZ - (node->bBox.Length/2);
                break;
            case 4:
                box.posX = node->bBox.posX - (node->bBox.Width/2);
                box.posY = node->bBox.posY - (node->bBox.Height/2);
                box.posZ = node->bBox.posZ + (node->bBox.Length/2);
                break;
            case 5:
                box.posX = node->bBox.posX + (node->bBox.Width/2);
                box.posY = node->bBox.posY - (node->bBox.Height/2);
                box.posZ = node->bBox.posZ + (node->bBox.Length/2);
                break;
            case 6:
                box.posX = node->bBox.posX + (node->bBox.Width/2);
                box.posY = node->bBox.posY - (node->bBox.Height/2);
                box.posZ = node->bBox.posZ - (node->bBox.Length/2);
                break;
            case 7:
                box.posX = node->bBox.posX - (node->bBox.Width/2);
                box.posY = node->bBox.posY - (node->bBox.Height/2);
                box.posZ = node->bBox.posZ - (node->bBox.Length/2);
                break;
            default:
                break;
        }
        box.Width = node->bBox.Width/2;
        box.Height = node->bBox.Height/2;
        box.Length = node->bBox.Length/2;
        //std::cout << "Pos: " << box.posX << " " << box.posY << " " << box.posZ << std::endl;
        //std::cout << "Size: " << box.Width << " " << box.Height << " " << box.Length << std::endl;
        node->children[i]->bBox = box;
    }

    //check all faces
    for(unsigned int i=0;i<node->indices.size();i++)
    {
        //for every subnode
        for(int j=0;j<8;j++)
        {
            //if the face is inside the boundingbox
            //append it to the subnode
            if(isInBoundingbox(node->indices[i],node->children[j]->bBox))
            {
                node->children[j]->indices.push_back(node->indices[i]);
            }
        }
    }

    //std::cout << node->depthLevel << std::endl;

    for(int i=0;i<8;i++)
    {
        //std::cout << i << " " << node->children[i]->indices.size() << std::endl;
        if(node->children[i]->indices.size() > 1)
        {
            if(node->depthLevel < 7)
            {
                if(node->children[i]->indices.size() < node->indices.size())
                {
                    //std::cout << i << std::endl;
                    buildSubtree(node->children[i]);
                }
            }
        }
    }
}

bool saiMap::isInBoundingbox(mapFace* face,saiBoundingBox& box)
{
    for(int i=0;i<3;i++)
    {
        mapVertex v = vertices[face->index[i]];
        //std::cout << v.vertex[0] << " " << v.vertex[1] << " " << v.vertex[2] << std::endl;
        if((v.vertex[0] >= box.posX-box.Width) && (v.vertex[0] <= box.posX+box.Width) &&
           (v.vertex[1] >= box.posY-box.Height) && (v.vertex[1] <= box.posY+box.Height) &&
           (v.vertex[2] >= box.posZ-box.Length) && (v.vertex[2] <= box.posZ+box.Length))
        {
            //std::cout << "true\n";
            return true;
        }
    }
    //std::cout << "false\n";
    return false;
}

void saiMap::buildOcttree()
{
    //calculate bounding box for top level
    float minW,maxW = 0;
    float minH,maxH = 0;
    float minL,maxL = 0;
    float px,py,pz = 0;
    for(unsigned int i=0;i<vertices.size();i++)
    {
        if(vertices[i].vertex[0] < minW)
            minW = vertices[i].vertex[0];
        else if(vertices[i].vertex[0] > maxW)
            maxW = vertices[i].vertex[0];

        if(vertices[i].vertex[1] < minH)
            minH = vertices[i].vertex[1];
        else if(vertices[i].vertex[1] > maxH)
            maxH = vertices[i].vertex[1];

        if(vertices[i].vertex[2] < minL)
            minL = vertices[i].vertex[2];
        else if(vertices[i].vertex[2] > maxL)
            maxL = vertices[i].vertex[2];
    }
    px = (maxW + minW)/2;
    py = (maxH + minH)/2;
    pz = (maxL + minL)/2;

    float w = maxW - px;
    float h = maxH - py;
    float l = maxL - pz;

    saiBoundingBox box;
    box.posX = px;
    box.posY = py;
    box.posZ = pz;
    box.Width = w;
    box.Height = h;
    box.Length = l;
    topLevelNode->bBox = box;

    //create children nodes
    buildSubtree(topLevelNode);
}

saiMap* saiMap::load(std::string fname)
{
    std::string filename = saiOptions::getPaths().f_sMappath + fname;
    std::vector<std::string> lines = loadTextfile(filename);
    if(lines.size() == 0)
        return 0;

    saiMap* newMap = new saiMap();
    int meshOffset = 0;
    int oldOffset = 0;
    newMap->topLevelNode = new saiTreeNode();
    newMap->topLevelNode->depthLevel = 0;
    for(unsigned int i=0;i<lines.size();i++)
    {
        if(lines[i].c_str()[0] == 'm' && lines[i].c_str()[1] == 't')
        {
            char nm[32];
            sscanf(lines[i].c_str(),"mt %s",nm);
            std::string name(nm);
            if(name == "mat_collision")
            {
                newMap->matColl = i;
            }
            else
            {
                saiMaterial* newMat = saiMaterial::load(name);
                newMap->materials.push_back(newMat);
            }
        }
        else if(lines[i].c_str()[0] == 'm' && lines[i].c_str()[1] == ' ')
        {
            int vertCount,faceCount;
            char nm[32];
            sscanf(lines[i].c_str(),"m %i %i %s",&vertCount,&faceCount,nm);
            oldOffset = meshOffset;
            meshOffset += vertCount;
        }
        else if(lines[i].c_str()[0] == 'v' && lines[i].c_str()[1] == ' ')
        {
            float px,py,pz;
            float nx,ny,nz;
            int r,g,b;
            sscanf(lines[i].c_str(),"v %f %f %f %f %f %f %i %i %i",&px,&py,&pz,&nx,&ny,&nz,&r,&g,&b);
            mapVertex vert;
            vert.vertex[0] = px*0.01;
            vert.vertex[1] = py*0.01;
            vert.vertex[2] = pz*0.01;
            vert.normal[0] = nx;
            vert.normal[1] = ny;
            vert.normal[2] = nz;
            vert.color[0] = (float)(r/255);
            vert.color[1] = (float)(g/255);
            vert.color[2] = (float)(g/255);
            newMap->vertices.push_back(vert);
            newMap->m_bHasGeometry = true;
        }
        else if(lines[i].c_str()[0] == 'f' && lines[i].c_str()[1] == ' ')
        {
            int v1,v2,v3;
            float a,b,c,d,e,f;
            unsigned int mId;
            sscanf(lines[i].c_str(),"f %i %i %i %f %f %f %f %f %f %i",&v1,&v2,&v3,&a,&b,&c,&d,&e,&f,&mId);
            mapFace* face = new mapFace();
            face->index[0] = v1 + oldOffset;
            face->index[1] = v2 + oldOffset;
            face->index[2] = v3 + oldOffset;
            face->texcoord[0] = a;
            face->texcoord[1] = b;
            face->texcoord[2] = c;
            face->texcoord[3] = d;
            face->texcoord[4] = e;
            face->texcoord[5] = f;
            if(mId-1 > newMap->materials.size())
            {
                std::cout <<  "Error face has wrong materialId. line " << i+1 << std::endl;
                face->matId = 0;
            }
            else
                face->matId = mId-1;
            //std::cout << mId-1 << std::endl;
            if(mId == newMap->matColl)
                newMap->collFaces.push_back(face);
            else
            {
                newMap->faces.push_back(face);
                newMap->topLevelNode->indices.push_back(face);
            }
        }
        else if(lines[i].c_str()[0] == 's' && lines[i].c_str()[1] == 'k')
        {
            char n1[32],n2[32],n3[32],n4[32],n5[32],n6[32];
            sscanf(lines[i].c_str(),"sk %s %s %s %s %s %s",n1,n2,n3,n4,n5,n6);
            std::string nam1(n1);
            std::string nam2(n2);
            std::string nam3(n3);
            std::string nam4(n4);
            std::string nam5(n5);
            std::string nam6(n6);
            newMap->skyBox = new saiSkybox(nam1,nam2,nam3,nam4,nam5,nam6);
        }
        else if(lines[i].c_str()[0] == 's' && lines[i].c_str()[1] == 'p')
        {
            int ID;
            char nm[32];
            float px,py,pz;
            float dir;
            sscanf(lines[i].c_str(),"sp %i %s %f %f %f %f",&ID,nm,&px,&py,&pz,&dir);
            std::string nam(nm);
            saiSpawnpoint sPoint;
            sPoint.id = ID;
            sPoint.Name = nam;
            sPoint.Direction = dir;
            sPoint.Position = saiVec3(px,py,pz);
            newMap->spawnpoints.push_back(sPoint);
        }
        else if(lines[i].c_str()[0] == 'd' && lines[i].c_str()[1] == 'o')
        {
            int trig;
            char nm[32];
            float px,py,pz;
            float rx,ry,rz;
            float sx,sy,sz;
            char mt[32];
            int id,keyid;
            float w,h,l;
            sscanf(lines[i].c_str(),"do %i %s %f %f %f %f %f %f %f %f %f %s %i %i %f %f %f",&trig,nm,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz,mt,&id,&keyid,&w,&h,&l);
            std::string nam(nm);
            std::string mat(mt);
            saiMaterial* newMat = saiMaterial::load(mat);
            saiStaticmodel* newMdl = saiStaticmodel::load(nam);
            newMdl->setPos(px*0.01,py*0.01,pz*0.01);
            newMdl->setRot(rx,ry,rz);
            newMdl->setSize(sx,sy,sz);
            saiDoor* newDoor = new saiDoor();
            newDoor->setInitPos(saiVec3(px*0.01,py*0.01,pz*0.01));
            newDoor->setModel(newMdl);
            newDoor->setMaterial(newMat);
            newDoor->setId(id);
            newDoor->setKeyId(keyid);
            saiCollisionObject* collObj = new saiCollisionObject(px,py+h/2,pz,rx,ry,rz,0.0);
            collObj->createBox(w,h,l);
            collObj->m_sParentName = "Door";
            saiPhysics::addCollisionObject(collObj);
            newDoor->setCollision(collObj);
            saiTrigger* trigger = NULL;
            for(unsigned int i=0;i<newMap->m_Triggers.size();i++)
            {
                if(newMap->m_Triggers[i]->getId() == trig)
                {
                    trigger = newMap->m_Triggers[i];
                }
            }
            if(trigger == NULL)
            {
                std::cout << "Error no trigger with id " << trig << std::endl;
            }
            else
            {
                newDoor->setTrigger(trigger);
            }
            newMap->m_Doors.push_back(newDoor);
        }
        else if(lines[i].c_str()[0] == 't' && lines[i].c_str()[1] == 'r')
        {
            int id;
            float px,py,pz;
            float rx,ry,rz;
            float w,h,l;
            sscanf(lines[i].c_str(),"tr %i %f %f %f %f %f %f %f %f %f",&id,&px,&py,&pz,&rx,&ry,&rz,&w,&h,&l);
            saiTrigger* newTrigger = new saiTrigger(id);
            saiCollisionObject* collObj = new saiCollisionObject(px,py,pz,rx,ry,rz,0.0);
            collObj->createBox(w,h,l);
            collObj->getRigidBody()->setCollisionFlags(collObj->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
            collObj->m_sParentName = "Trigger";
            collObj->m_bCollideWithRays = false;
            saiPhysics::addCollisionObject(collObj);
            newTrigger->setCollision(collObj);
            newMap->m_Triggers.push_back(newTrigger);
        }
        else if(lines[i].c_str()[0] == 'e' && lines[i].c_str()[1] == 'n')
        {
            char nm[32];
            char sc[32];
            char md[32];
            char mt[32];
            char cl[256];
            float px,py,pz;
            float rx,ry,rz;
            float sx,sy,sz;
            sscanf(lines[i].c_str(),"en %s %s",nm,sc);
            sscanf(lines[i+1].c_str(),"e1 %f %f %f %f %f %f %f %f %f",&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
            sscanf(lines[i+2].c_str(),"e2 %s %s",md,mt);
            sscanf(lines[i+3].c_str(),"e3 %s",cl);
            std::string clt(cl);
            saiCollisionObject* colObj=NULL;
            if(clt == "box")
            {
                float w,h,l,m;
                sscanf(lines[i+3].c_str(),"e3 %s %f %f %f %f",cl,&w,&h,&l,&m);
                colObj = new saiCollisionObject(px,py,pz,rx,ry,rz,m);
                colObj->createBox(w,h,l);
            }
            else if(clt == "cylinder")
            {
                float rad,h,m;
                sscanf(lines[i+3].c_str(),"e3 %s %f %f %f",cl,&h,&rad,&m);
                colObj = new saiCollisionObject(px,py,pz,rx,ry,rz,m);
                colObj->createCylinder(rad,h);
            }
            std::string nam(nm);
            std::string scr(sc);
            std::string mdl(md);
            std::string mat(mt);
            saiScript* newScript = new saiScript(scr);
            saiScriptManager::registerScript(newScript->getState());
            saiEntity* newEntity = new saiEntity(nam,newScript);
            newScript->p_EntityPointer = newEntity;
            saiMaterial* newMat = saiMaterial::load(mat);
            saiObjModel* newMdl = saiObjModel::load(mdl);
            newMdl->setMaterial(newMat);
            //newMdl->setPos(px,py,pz);
            //newMdl->setRot(rx,ry,rz);
            //newMdl->setSize(sx,sy,sz);
            newEntity->setMaterial(newMat);
            newEntity->setModel(newMdl);
            if(colObj != NULL)
            {
                newEntity->setCollisionObject(colObj);
                colObj->m_sParentName = "Entity";
                saiPhysics::addCollisionObject(colObj);
            }
            newEntity->init();
            newMap->m_vecEntities.push_back(newEntity);
            i += 3;
        }
        else if(lines[i].c_str()[0] == 's' && lines[i].c_str()[1] == 't')
        {
            char smd[32];
            char smt[32];
            float px,py,pz;
            float rx,ry,rz;
            float sx,sy,sz;
            sscanf(lines[i].c_str(),"st %s %s",smd,smt);
            std::string smdl(smd);
            std::string smat(smt);
            i++;
            sscanf(lines[i].c_str(),"s1 %f %f %f %f %f %f %f %f %f",&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
            saiStaticMesh* newMesh = new saiStaticMesh();
            saiMaterial* newMat = saiMaterial::load(smat);
            saiObjModel* newMdl = saiObjModel::load(smdl);
            newMdl->setMaterial(newMat);
            newMdl->setPos(px*0.01,py*0.01,pz*0.01);
            newMdl->setRot(rx,ry,rz);
            newMdl->setSize(sx,sy,sz);
            newMesh->setMaterial(newMat);
            newMesh->setModel(newMdl);
            newMap->m_vecStaticmeshes.push_back(newMesh);
        }
        else if(lines[i].c_str()[0] == 'c' && lines[i].c_str()[1] == 'l')
        {
            char ty[32];
            sscanf(lines[i].c_str(),"cl %s",ty);
            std::string typ(ty);
            if(typ == "sphere")
            {
                float rad;
                float px,py,pz;
                sscanf(lines[i].c_str(),"cl %s %f %f %f %f",ty,&rad,&px,&py,&pz);
                saiCollisionObject* newCol = new saiCollisionObject(px,py,pz,0.0,0.0,0.0,0.0);
                newCol->createSphere(rad);
                newCol->m_sParentName ="Static";
                newMap->m_vecCollisionObjects.push_back(newCol);
                saiPhysics::addCollisionObject(newCol);
            }
            else if(typ == "box")
            {
                float w,h,l;
                float px,py,pz,rx,ry,rz;
                sscanf(lines[i].c_str(),"cl %s %f %f %f %f %f %f %f %f %f",ty,&w,&h,&l,&px,&py,&pz,&rx,&ry,&rz);
                saiCollisionObject* newCol = new saiCollisionObject(px,py,pz,rx,ry,rz,0.0);
                newCol->createBox(w,h,l);
                newCol->m_sParentName ="Static";
                newMap->m_vecCollisionObjects.push_back(newCol);
                saiPhysics::addCollisionObject(newCol);
            }
        }
        else if(lines[i].c_str()[0] == 'i' && lines[i].c_str()[1] == 't')
        {
            int id;
            float px,py,pz;
            float rx,ry,rz;
            float sx,sy,sz;
            char typ[32];
            int val;
            char nm[32];
            float rad;
            char mt[32];
            sscanf(lines[i].c_str(),"it %i %f %f %f %f %f %f %f %f %f %s %i %s %f %s",&id,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz,typ,&val,nm,&rad,mt);
            std::string type(typ);
            std::string name(nm);
            std::string mat(mt);
            saiItem* newItem = new saiItem(type,id,val);
            saiMaterial* newMat = saiMaterial::load(mat);
            saiObjModel* newMdl = saiObjModel::load(name);
            newMdl->setMaterial(newMat);
            newMdl->setPos(px*0.01,py*0.01,pz*0.01);
            newMdl->setRot(rx,ry,rz);
            newMdl->setSize(sx,sy,sz);
            saiCollisionObject* newCol = new saiCollisionObject(px,py+rad/2,pz,rx,ry,rz,0.0);
            newCol->createSphere(rad);
            newCol->m_sParentName = "Item";
            newCol->getRigidBody()->setCollisionFlags(newCol->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
            newCol->m_bCollideWithRays = false;
            saiPhysics::addCollisionObject(newCol);
            newItem->mat = newMat;
            newItem->mdl = newMdl;
            newItem->collObj = newCol;
            newCol->m_pParentObj = newItem;
            newMap->m_vecItems.push_back(newItem);
        }
        else if(lines[i].c_str()[0] == 'p' && lines[i].c_str()[1] == 'l')
        {
            float px,py,pz;
            float ar,ag,ab;
            float dr,dg,db;
            sscanf(lines[i].c_str(),"pl %f %f %f %f %f %f %f %f %f",&px,&py,&pz,&dr,&dg,&db,&ar,&ag,&ab);
            saiPointLight* newLight = new saiPointLight();
            newLight->setPos(px*0.01,py*0.01,pz*0.01);
            newLight->setAmbient(saiVec3(ar,ag,ab));
            newLight->setDiffuse(saiVec3(dr,dg,db));
            saiLightManager::addLight(newLight);
        }
        else if(lines[i].c_str()[0] == 't' && lines[i].c_str()[1] == 'e')
        {
            char hm[32];
            float fmin,fmax;
            sscanf(lines[i].c_str(),"te %s %f %f",hm,&fmin,&fmax);
            std::string height(hm);
            saiTerrain* newTerrain = saiTerrain::loadFromHeightmap(height,fmin,fmax);
            newMap->m_Terrain = newTerrain;
        }
    }
    if(newMap->m_bHasGeometry)
    {
        //create collision mesh
        newMap->mapCollision = new saiCollisionObject(0,0,0,0,0,0,0);
        std::vector<saiCollisionTriangle> tris;
        for(unsigned int i=0;i<newMap->collFaces.size();i++)
        {
            //std::cout << newMap->collFaces[i]->matId << std::endl;
            //std::cout << newMap->vertices[newMap->collFaces[i]->index[0]].vertex[0] << std::endl;
            saiVec3 v1(newMap->vertices[newMap->collFaces[i]->index[0]].vertex[0],newMap->vertices[newMap->collFaces[i]->index[0]].vertex[1],newMap->vertices[newMap->collFaces[i]->index[0]].vertex[2]);
            saiVec3 v2(newMap->vertices[newMap->collFaces[i]->index[1]].vertex[0],newMap->vertices[newMap->collFaces[i]->index[1]].vertex[1],newMap->vertices[newMap->collFaces[i]->index[1]].vertex[2]);
            saiVec3 v3(newMap->vertices[newMap->collFaces[i]->index[2]].vertex[0],newMap->vertices[newMap->collFaces[i]->index[2]].vertex[1],newMap->vertices[newMap->collFaces[i]->index[2]].vertex[2]);
            //std::cout << v1.x << " " << v1.y << " " << v1.z << std::endl;
            saiCollisionTriangle tri;
            tri.vertices[0] = v1;
            tri.vertices[1] = v2;
            tri.vertices[2] = v3;
            tris.push_back(tri);
        }
        newMap->mapCollision->createTrianglemesh(tris);
        newMap->mapCollision->m_sParentName = "Level";
        saiPhysics::addCollisionObject(newMap->mapCollision);
        newMap->buildOcttree();
    }
    return newMap;
}

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiModel.h"

//SSM File--------------------------------------------
saiStaticmodel::saiStaticmodel()
{
    vertices = NULL;
    faces = NULL;
    mat = NULL;
}

saiStaticmodel::~saiStaticmodel()
{
    delete[] vertices;
    delete[] faces;
}

void saiStaticmodel::render()
{
    glPushMatrix();
    glTranslatef(Position.x,Position.y,Position.z);
    glRotatef(Rotation.x,1,0,0);
    glRotatef(Rotation.y,0,1,0);
    glRotatef(Rotation.z,0,0,1);
    glScalef(Size.x,Size.y,Size.z);
    if(mat != NULL)
        mat->use();
    glColor4f(1.0,1.0,1.0,1.0);
    glDisable(GL_LIGHTING);
    for(int i=0;i<numFaces;i++)
    {
        //std::cout << faces[i].texcoords[1] << " " << faces[i].texcoords[1] << " " << faces[i].texcoords[1] << std::endl;
        glBegin(GL_TRIANGLES);
        glTexCoord2f(faces[i].texcoords[0],faces[i].texcoords[1]);
        glNormal3f(vertices[faces[i].vertices[0]].normal[0],vertices[faces[i].vertices[0]].normal[1],vertices[faces[i].vertices[0]].normal[2]);
        glVertex3f(vertices[faces[i].vertices[0]].vertex[0],vertices[faces[i].vertices[0]].vertex[1],vertices[faces[i].vertices[0]].vertex[2]);
        glTexCoord2f(faces[i].texcoords[2],faces[i].texcoords[3]);
        glNormal3f(vertices[faces[i].vertices[1]].normal[0],vertices[faces[i].vertices[1]].normal[1],vertices[faces[i].vertices[1]].normal[2]);
        glVertex3f(vertices[faces[i].vertices[1]].vertex[0],vertices[faces[i].vertices[1]].vertex[1],vertices[faces[i].vertices[1]].vertex[2]);
        glTexCoord2f(faces[i].texcoords[4],faces[i].texcoords[5]);
        glNormal3f(vertices[faces[i].vertices[2]].normal[0],vertices[faces[i].vertices[2]].normal[1],vertices[faces[i].vertices[2]].normal[2]);
        glVertex3f(vertices[faces[i].vertices[2]].vertex[0],vertices[faces[i].vertices[2]].vertex[1],vertices[faces[i].vertices[2]].vertex[2]);
        glEnd();
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void saiStaticmodel::update()
{
}

saiStaticmodel* saiStaticmodel::load(std::string fname)
{
    saiStaticmodel* newMdl = new saiStaticmodel();
    if(fname.c_str()[fname.size()-1]=='m' && fname.c_str()[fname.size()-2]=='s' && fname.c_str()[fname.size()-3]=='s')
    {
        std::string path = saiOptions::getPaths().f_sModelpath + fname;
        std::ifstream file;
        saiSMHeader header;
        file.open(path.c_str(),std::ios::in|std::ios::binary);
        if(file.fail())
        {
            std::cout << "Error loading model: " << fname << std::endl;
            delete newMdl;
            return NULL;
        }
        file.read((char*)&header,sizeof(saiSMHeader));
        //std::cout << header.faceCount << std::endl;
        //std::cout << header.vertexCount << std::endl;
        newMdl->numFaces = header.faceCount;
        newMdl->numVertices = header.vertexCount;
        newMdl->vertices = new saiSMVertex[header.vertexCount];
        newMdl->faces = new saiSMFace[header.faceCount];
        file.seekg(sizeof(header),std::ios::beg);
        file.read((char*)newMdl->vertices,header.vertexCount*sizeof(saiSMVertex));
        file.seekg(header.vertexCount*sizeof(saiSMVertex)+sizeof(header),std::ios::beg);
        file.read((char*)newMdl->faces,header.faceCount*sizeof(saiSMFace));
        file.close();
        for(int i=0;i<newMdl->numVertices;i++)
        {
            newMdl->vertices[i].vertex[0] *= 0.01;
            newMdl->vertices[i].vertex[1] *= 0.01;
            newMdl->vertices[i].vertex[2] *= 0.01;
        }
    }
    else
    {
        std::cout << "Error loading model, file-format not supported " << fname << std::endl;
        delete newMdl;
        return NULL;
    }
    return newMdl;
}
//-----------------------------------------------------

//OBJ File---------------------------------------------
saiObjModel::saiObjModel()
{

}

saiObjModel::~saiObjModel()
{
    for(unsigned int i=0;i<m_vecVertices.size();i++)
        delete m_vecVertices[i];
    for(unsigned int i=0;i<m_vecNormals.size();i++)
        delete m_vecNormals[i];
    for(unsigned int i=0;i<m_vecTexcoords.size();i++)
        delete m_vecTexcoords[i];
    for(unsigned int i=0;i<m_vecFaces.size();i++)
        delete m_vecFaces[i];
}

void saiObjModel::render()
{
    if(mat != NULL)
        mat->use();
    glPushMatrix();
    glTranslatef(Position.x,Position.y,Position.z);
    glRotatef(Rotation.x,1,0,0);
    glRotatef(Rotation.y,0,1,0);
    glRotatef(Rotation.z,0,0,1);
    glScalef(Size.x,Size.y,Size.z);
    if(mat != NULL)
        glColor4f(mat->getR(),mat->getG(),mat->getB(),mat->getA());
    else
        glColor4f(1.0,1.0,1.0,1.0);
    for(unsigned int i=0;i<m_vecFaces.size();i++)
    {
        glBegin(GL_TRIANGLES);
        glTexCoord2f(m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[0]]->x,m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[0]]->y);
        glNormal3f(m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->x,m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->y,m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->z);
        glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->z);
        glTexCoord2f(m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[1]]->x,m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[1]]->y);
        glNormal3f(m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->x,m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->y,m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->z);
        glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->z);
        glTexCoord2f(m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[2]]->x,m_vecTexcoords[m_vecFaces[i]->m_nTexcoords[2]]->y);
        glNormal3f(m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->x,m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->y,m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->z);
        glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->z);
        glEnd();
        if(saiOptions::bDebugView)
        {
            float nSize = 0.05;
            glBegin(GL_LINES);
            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->z);
            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->x + m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->x*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->y + m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->y*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[0]]->z + m_vecNormals[m_vecFaces[i]->m_nNormals[0]]->z*nSize);

            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->z);
            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->x + m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->x*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->y + m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->y*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[1]]->z + m_vecNormals[m_vecFaces[i]->m_nNormals[1]]->z*nSize);

            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->x,m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->y,m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->z);
            glVertex3f(m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->x + m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->x*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->y + m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->y*nSize,
                       m_vecVertices[m_vecFaces[i]->m_nVertices[2]]->z + m_vecNormals[m_vecFaces[i]->m_nNormals[2]]->z*nSize);
            glEnd();
        }
    }
    glPopMatrix();
}

saiObjModel* saiObjModel::load(std::string p_sName)
{
    std::string filename = saiOptions::getPaths().f_sModelpath + p_sName + ".obj";
    std::vector<std::string> lines = loadTextfile(filename);
    saiObjModel* newMdl = new saiObjModel();
    for(unsigned int i=0;i<lines.size();i++)
    {
        if(lines[i].c_str()[0] == 'v' && lines[i].c_str()[1] == ' ')
        {
            float v0,v1,v2;
            sscanf(lines[i].c_str(),"v %f %f %f",&v0,&v1,&v2);
            saiVec3* newVec = new saiVec3(v0*0.01,v1*0.01,v2*0.01);
            newMdl->m_vecVertices.push_back(newVec);
        }
        else if(lines[i].c_str()[0] == 'v' && lines[i].c_str()[1] == 'n')
        {
            float n0,n1,n2;
            sscanf(lines[i].c_str(),"vn %f %f %f",&n0,&n1,&n2);
            saiVec3* newVec = new saiVec3(n0,n1,n2);
            newMdl->m_vecNormals.push_back(newVec);
        }
        else if(lines[i].c_str()[0] == 'v' && lines[i].c_str()[1] == 't')
        {
            float tx,ty,tz;
            sscanf(lines[i].c_str(),"vt %f %f %f",&tx,&ty,&tz);
            saiVec3* newVec = new saiVec3(tx,1-ty,tz);
            newMdl->m_vecTexcoords.push_back(newVec);
        }
        else if(lines[i].c_str()[0] == 'f' && lines[i].c_str()[1] == ' ')
        {
            int v1,v2,v3;
            int vt1,vt2,vt3;
            int n1,n2,n3;
            sscanf(lines[i].c_str(),"f %i/%i/%i %i/%i/%i %i/%i/%i",&v1,&vt1,&n1,&v2,&vt2,&n2,&v3,&vt3,&n3);
            saiOBJface* newFace = new saiOBJface();
            newFace->m_nVertices[0] = v1-1;
            newFace->m_nVertices[1] = v2-1;
            newFace->m_nVertices[2] = v3-1;
            newFace->m_nNormals[0] = n1-1;
            newFace->m_nNormals[1] = n2-1;
            newFace->m_nNormals[2] = n3-1;
            newFace->m_nTexcoords[0] = vt1-1;
            newFace->m_nTexcoords[1] = vt2-1;
            newFace->m_nTexcoords[2] = vt3-1;
            newMdl->m_vecFaces.push_back(newFace);
        }
    }
    return newMdl;
}
//-----------------------------------------------------

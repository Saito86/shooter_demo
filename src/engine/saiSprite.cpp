////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiSprite.h"

saiSprite::saiSprite(std::string fname)
{
    std::string path = saiOptions::getPaths().f_sTexturepath + fname;
    SDL_Surface* img;
    GLenum textureFormat;
    GLint nOfColors;
    if((img = IMG_Load(path.c_str())))
    {
        nOfColors = img->format->BytesPerPixel;
        width = img->w;
        height = img->h;
        if(nOfColors == 4)
        {
            if(img->format->Rmask == 0x000000ff)
                textureFormat = GL_RGBA;
            else
                textureFormat = GL_BGRA;
        }
        else if(nOfColors == 3)
        {
            if(img->format->Rmask == 0x000000ff)
                textureFormat = GL_RGB;
            else
                textureFormat = GL_BGR;
        }
        else
        {
            std::cout << "Error: image is not truecolor " << fname << std::endl;
            SDL_FreeSurface(img);
            return;
        }
        glGenTextures(1,&texId);
        glBindTexture(GL_TEXTURE_2D,texId);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,nOfColors,width,height,0,textureFormat,GL_UNSIGNED_BYTE,img->pixels);
    }
    else
    {
        std::cout << "Error: loading image " << fname << std::endl;
    }
    if(img)
        SDL_FreeSurface(img);

    posX = saiOptions::getConfig().m_iScreenCenterX;
    posY = saiOptions::getConfig().m_iScreenCenterY;
    ratioX = (float)saiOptions::getConfig().m_iScreenCenterX/width;
    ratioY = (float)saiOptions::getConfig().m_iScreenCenterY/height;
    if(width >= height)
    {
        sizeX = width * ratioX;
        sizeY = height * ratioX;
    }
    else
    {
        sizeX = width * ratioY;
        sizeY = height * ratioY;
    }
    bHidden = false;
    m_Mat = saiMaterial::load("default");
}

saiSprite::~saiSprite()
{
    glDeleteTextures(1,&texId);
    delete m_Mat;
}

void saiSprite::render()
{
    if(!bHidden)
    {
        glDisable(GL_LIGHTING);
        m_Mat->use();
        glBindTexture(GL_TEXTURE_2D,texId);
        glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex2f(posX-sizeX,posY-sizeY);
        glTexCoord2i(0,1);
        glVertex2f(posX-sizeX,posY+sizeY);
        glTexCoord2i(1,1);
        glVertex2f(posX+sizeX,posY+sizeY);
        glTexCoord2i(1,0);
        glVertex2f(posX+sizeX,posY-sizeY);
        glEnd();
        glEnable(GL_LIGHTING);
    }
}

void saiSprite::setPos(float x,float y)
{
    posX = saiOptions::getConfig().m_iScreenCenterX + saiOptions::getConfig().m_iScreenCenterX * x;
    posY = saiOptions::getConfig().m_iScreenCenterY + saiOptions::getConfig().m_iScreenCenterY * y;
}

void saiSprite::setPosX(float x)
{
    posX = saiOptions::getConfig().m_iScreenCenterX + saiOptions::getConfig().m_iScreenCenterX * x;
}

void saiSprite::setPosY(float y)
{
    posY = saiOptions::getConfig().m_iScreenCenterY + saiOptions::getConfig().m_iScreenCenterY * y;
}

void saiSprite::setSize(float x,float y)
{
    if(width >= height)
    {
        sizeX = width * ratioX * x;
        sizeY = height * ratioX * y;
    }
    else
    {
        sizeX = width * ratioY * x;
        sizeY = height * ratioY * y;
    }
}

void saiSprite::setSizeX(float x)
{
    if(width >= height)
    {
        sizeX = width * ratioX * x;
    }
    else
    {
        sizeX = width * ratioY * x;
    }
}

void saiSprite::setSizeY(float y)
{
    if(width >= height)
    {
        sizeY = height * ratioX * y;
    }
    else
    {
        sizeY = height * ratioY * y;
    }
}

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiScreentext.h"

saiScreentext::saiScreentext(std::string txt)
{
    SDL_Color fc = {255,255,255,255};
    color = fc;
    Size = saiOptions::getConfig().m_iScreenHeight/20;
    Text = txt;
    fontFileName = "FreeSans.otf";
    fnt = loadFont(fontFileName);
    texId = loadTexture();
    posX = saiOptions::getConfig().m_iScreenCenterX;
    posY = saiOptions::getConfig().m_iScreenCenterY;
    scaleX = 1;
    scaleY = 1;
    bHidden = false;
    alignment = SAI_ALIGN_LEFT;
    m_Mat = saiMaterial::load("default");
}

saiScreentext::~saiScreentext()
{
    TTF_CloseFont(fnt);
    glDeleteTextures(1,&texId);
    delete m_Mat;
}

void saiScreentext::render()
{
    if(!bHidden)
    {
        glDisable(GL_LIGHTING);
        m_Mat->use();
        glBindTexture(GL_TEXTURE_2D,texId);
        if(alignment == SAI_ALIGN_LEFT)
        {
            glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glTexCoord2i(0,0);
            glVertex2f(posX,posY);
            glTexCoord2i(0,1);
            glVertex2f(posX,posY+height*scaleY);
            glTexCoord2i(1,1);
            glVertex2f(posX+width*scaleX,posY+height*scaleY);
            glTexCoord2i(1,0);
            glVertex2f(posX+width*scaleX,posY);
            glEnd();
        }
        else if(alignment == SAI_ALIGN_RIGHT)
        {
            glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glTexCoord2i(0,0);
            glVertex2f(posX-width*scaleX,posY);
            glTexCoord2i(0,1);
            glVertex2f(posX-width*scaleX,posY+height*scaleY);
            glTexCoord2i(1,1);
            glVertex2f(posX,posY+height*scaleY);
            glTexCoord2i(1,0);
            glVertex2f(posX,posY);
            glEnd();
        }
        glEnable(GL_LIGHTING);
    }
}

void saiScreentext::setText(std::string txt)
{
    Text = txt;
    glDeleteTextures(1,&texId);
    texId = loadTexture();
}

void saiScreentext::setText(int num)
{
    std::string Result;
    std::ostringstream stream;
    stream << num;
    Result = stream.str();
    Text = Result;
    glDeleteTextures(1,&texId);
    texId = loadTexture();
}

TTF_Font* saiScreentext::loadFont(std::string fFile)
{
    std::string path = saiOptions::getPaths().f_sFontpath + fFile;
    TTF_Font* newFnt = TTF_OpenFont(path.c_str(),Size);
    if(!newFnt)
    {
        std::cout << "Error in TTF_OpenFont: " << TTF_GetError() << std::endl;
        return NULL;
    }
    return newFnt;
}

GLuint saiScreentext::loadTexture()
{
    GLuint i;
    SDL_Surface* fntTex = TTF_RenderText_Blended(fnt,Text.c_str(),color);
    if(fntTex == NULL)
        std::cout << "Error: creating font texture\n";
    width = fntTex->w;
    height = fntTex->h;
    GLenum textureFormat;
    GLint nOfColors = fntTex->format->BytesPerPixel;
    if(nOfColors == 4)
    {
        if((fntTex->format->Rmask = 0x000000ff))
            textureFormat = GL_RGBA;
        else
            textureFormat = GL_BGRA;
    }
    else if(nOfColors == 3)
    {
        if((fntTex->format->Rmask = 0x000000ff))
            textureFormat = GL_RGB;
        else
            textureFormat = GL_BGR;
    }
    else
    {
        std::cout << "Error: font-image has wrong format\n";
    }
    glGenTextures(1,&i);
    glBindTexture(GL_TEXTURE_2D,i);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,nOfColors,width,height,0,textureFormat,GL_UNSIGNED_BYTE,fntTex->pixels);
    SDL_FreeSurface(fntTex);

    return i;
}

void saiScreentext::setPos(float x,float y)
{
    posX = saiOptions::getConfig().m_iScreenCenterX + saiOptions::getConfig().m_iScreenCenterX * x;
    posY = saiOptions::getConfig().m_iScreenCenterY + saiOptions::getConfig().m_iScreenCenterY * y;
}

void saiScreentext::setPosX(float x)
{
    posX = saiOptions::getConfig().m_iScreenCenterX + saiOptions::getConfig().m_iScreenCenterX * x;
}

void saiScreentext::setPosY(float y)
{
    posY = saiOptions::getConfig().m_iScreenCenterY + saiOptions::getConfig().m_iScreenCenterY * y;
}

void saiScreentext::setSize(float x,float y)
{
    scaleX = x;
    scaleY = y;
}

void saiScreentext::setSizeX(float x)
{
    scaleX = x;
}

void saiScreentext::setSizeY(float y)
{
    scaleY = y;
}

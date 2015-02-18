////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiTexture.h"

saiTexture::saiTexture()
{

}

saiTexture::~saiTexture()
{
	glDeleteTextures(1,&texId);
}

void saiTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D,texId);
}

saiTexture* saiTexture::load(std::string fname)
{
	std::string filename = saiOptions::getPaths().f_sTexturepath + fname;
	saiTexture* newTex =  new saiTexture();
	SDL_Surface* img;
	if((img = IMG_LoadTyped_RW(SDL_RWFromFile(filename.c_str(),"rb"),1,"TGA")))
	{
		GLenum textureFormat;
		GLint nOfColors = img->format->BytesPerPixel;
		newTex->width = img->w;
		newTex->height = img->h;
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
			std::cout << "Error: wrong color format in " << fname << std::endl;
			SDL_FreeSurface(img);
			delete newTex;
			return NULL;
		}
		glGenTextures(1,&newTex->texId);
		glBindTexture(GL_TEXTURE_2D,newTex->texId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,nOfColors,newTex->width,newTex->height,0,textureFormat,GL_UNSIGNED_BYTE,img->pixels);
	}
	else
	{
		std::cout <<"couldn't load texture " << fname << std::endl;
		delete newTex;
		return NULL;
	}

	SDL_FreeSurface(img);
	return newTex;
}

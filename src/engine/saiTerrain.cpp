#include "saiTerrain.h"

saiTerrain::saiTerrain()
{

}

saiTerrain::~saiTerrain()
{

}

void saiTerrain::render()
{

}

saiTerrain* saiTerrain::loadFromHeightmap(std::string fname,float p_low,float p_high)
{
    saiTerrain* newTerrain = new saiTerrain();
    std::string filename = saiOptions::getPaths().f_sTexturepath + fname;

    SDL_Surface* img;
	if((img = IMG_LoadTyped_RW(SDL_RWFromFile(filename.c_str(),"rb"),1,"TGA")))
    {
        int width = img->w;
        int height = img->h;
        SDL_LockSurface(img);
        for(int y=0;y<height;++y)
        {
            for(int x=0;x<width;++x)
            {

            }
        }
        SDL_UnlockSurface(img);
    }
    else
	{
		std::cout <<"couldn't load texture " << fname << std::endl;
	}

	SDL_FreeSurface(img);

    return newTerrain;
}

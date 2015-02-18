#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "saiRenderable.h"

class saiTerrain : public saiRenderable
{
    public:
        static saiTerrain* loadFromHeightmap(std::string fname,float p_low,float p_high);
        ~saiTerrain();
        void render();
    private:
        saiTerrain();
};

#endif // _TERRAIN_H

////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _DECAL_H
#define _DECAL_H

#include "saiRenderable.h"

class saiDecal : public saiRenderable
{
    public:
        saiDecal();
        virtual ~saiDecal();
        void render();
        static void cleanUp();
    private:
        static saiMaterial* s_Material; //for now all decals have the same material
};

#endif // _DECAL_H

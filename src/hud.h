////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _HUD_H
#define _HUD_H

#include "saiScreentext.h"
#include "saiSprite.h"

class Hud
{
    public:
        Hud();
        ~Hud();
        void render();
        void setAmmo(int a);
        void setHealth(int h);
    private:
        saiScreentext* ammoText;
        saiScreentext* healthText;
        saiSprite* sprHealth;
        saiSprite* sprAmmo;
        saiSprite* crosshair;
        int nAmmo;
        int nHealth;
};

#endif // _HUD_H

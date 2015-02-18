////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "hud.h"

Hud::Hud()
{
    nAmmo = 0;
    nHealth = 0;
    ammoText = new saiScreentext("000");
    ammoText->setPos(-0.525,0.84);
    ammoText->setAlignment(SAI_ALIGN_RIGHT);
    healthText = new saiScreentext("100");
    healthText->setPos(-0.77,0.84);
    healthText->setAlignment(SAI_ALIGN_RIGHT);
    sprHealth = new saiSprite("health.tga");
    sprHealth->setSize(0.05,0.05);
    sprHealth->setPos(-0.925,0.9);
    sprAmmo = new saiSprite("ammo.tga");
    sprAmmo->setSize(0.05,0.05);
    sprAmmo->setPos(-0.68,0.9);
    crosshair = new saiSprite("crosshair.tga");
    crosshair->setSize(0.05,0.05);
}

Hud::~Hud()
{
    delete ammoText;
    delete healthText;
    delete sprHealth;
    delete sprAmmo;
    delete crosshair;
}

void Hud::render()
{
    ammoText->render();
    healthText->render();
    sprHealth->render();
    sprAmmo->render();
    crosshair->render();
}

void Hud::setAmmo(int a)
{
    if(a != nAmmo)
    {
        nAmmo = a;
        ammoText->setText(a);
    }
}

void Hud::setHealth(int h)
{
    if(h != nHealth)
    {
        nHealth = h;
        healthText->setText(h);
    }
}

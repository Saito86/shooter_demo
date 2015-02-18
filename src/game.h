////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _GAME_H
#define _GAME_H

#include "saiFramework.h"
#include "saiSound.h"
#include "saiOption.h"
#include "saiInput.h"
#include "saiMap.h"
#include "saiCamera.h"
#include "saiPhysics.h"
#include "player.h"
#include "enemy.h"
#include "saiParticle.h"
#include "saiLight.h"

class Game
{
    public:
        Game();
        ~Game();
        bool init();
        void startMainloop();
    private:
        bool loadLevel(std::string fname);
        saiFramework fWork;
        saiInput input;
        saiPhysics physics;
        Hud* hud;
        saiMap* level;
        saiCamera* cam;
        Player* player;
        std::vector<Enemy*> enemies;
};

#endif // _GAME_H

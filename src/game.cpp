////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "game.h"

//GAME
Game::Game()
{
    level = NULL;
    player = NULL;
    cam = NULL;
    hud = NULL;
}

Game::~Game()
{
    saiMaterial::cleanupShaders();
    delete level;
    delete player;
    delete cam;
    delete hud;
    for(unsigned int i=0;i<enemies.size();i++)
        delete enemies[i];
    saiDecal::cleanUp();
    saiSoundManager::cleanUp();
    saiParticleManager::cleanup();
    saiLightManager::cleanUp();
}

bool Game::init()
{
    //init engine framework
    if(!fWork.init())
        return false;

    //init input
    //doesn't do anything yet
    if(!input.init())
        return false;

    //shader need to be compiled at runtime
    //at the beginnig of the program
    //after the framework has initialized
    saiMaterial::compileShaders();

    if(!saiSoundManager::init())
        return false;

    //loads a level
    //hardcoded for now
    if(!loadLevel("testroom2.smp"))
        return false;

    if(!saiParticleManager::init())
        return false;

    hud = new Hud();
    cam = new saiCamera();

    player = new Player(cam,hud);
    player->setMap(level);

    return true;
}

void Game::startMainloop()
{
    float deltaTime = 0.0;
    int thisTime = 0;
    int lastTime = 0;

    while(saiOptions::isRunning)
    {
        //time since last frame in seconds
        //is needed in the update functions
        //for framerate-indipendent movement
        thisTime = SDL_GetTicks();
        deltaTime = (float)(thisTime - lastTime)/1000;
        lastTime = thisTime;

        //update key events
        //returns false on Quit event
        if(!input.update())
            saiOptions::isRunning = false;

        //updates the timer
        fWork.update();

        //bullet step simulation
        physics.update(deltaTime);

        //update enemies
        for(unsigned int i=0;i<enemies.size();i++)
            enemies[i]->update(deltaTime);

        level->update(deltaTime);
        player->update(deltaTime);

        //clear buffer
        fWork.beginScene();

        //set perspective view matrix
        fWork.set3d();

        //update cam
        cam->update();

        //render sky
        level->renderSky();

        //transform the scene
        //must be after render sky
        //or sky won't work properly
        cam->applyCameraMatrix();

        //sort lights by distance to camera
        //doesn't work properly yet
        saiLightManager::setNearestLights(cam->pos);

        //render map
        level->render(deltaTime);
        for(unsigned int i=0;i<enemies.size();i++)
            enemies[i]->render(deltaTime);
        player->render(deltaTime);

        //render collision objects and mesh normals
        if(saiOptions::bDebugView)
            physics.render();

        //render particles
        saiParticleManager::render(deltaTime);

        //set orthographic view
        fWork.set2d();

        //render gui
        hud->render();

        //swap buffers
        fWork.endScene();

        //reset stats on collision objects
        physics.resetObjects();

        //limit framerate to 60 fps
        fWork.capFPS(60);
    }
}

bool Game::loadLevel(std::string fname)
{
    //load the map
    level = saiMap::load(fname);

    //check for errors
    if(level == NULL)
        return false;

    //spawn actors
    for(unsigned int i=0;i<level->spawnpoints.size();i++)
    {
        saiSpawnpoint spawn = level->spawnpoints[i];
        if(spawn.id > 0)
        {
            if(spawn.Name == "enemySpawn")
            {
                Enemy* newEnemy = new Enemy(spawn.Position.x,spawn.Position.y,spawn.Position.z,spawn.Direction);
                enemies.push_back(newEnemy);
            }
        }
    }

    return true;
}

//MAIN
int main(int argc,char* args[])
{
    //create game objects
    Game game;
    //init game, which also inits all engine subsystems
    if(!game.init())
        return 1;
    //start the mainloop
    game.startMainloop();
    return 0;
}

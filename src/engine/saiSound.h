////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _SOUND_H
#define _SOUND_H

#include "saiBase.h"
#include <SDL2/SDL_mixer.h>
#include "saiOption.h"

class saiSound
{
    public:
        saiSound(std::string p_sName);
        virtual ~saiSound();
        void play();
        std::string getName(){return m_sName;}
    private:
        Mix_Chunk *sound;
        std::string m_sName;
};

class saiSoundManager
{
    public:
        static bool init();
        static void cleanUp();
        static void play(std::string p_sName);
    private:
        static std::vector<saiSound*> s_vecSounds;
};

#endif // _SOUND_H

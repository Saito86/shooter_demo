////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiSound.h"

std::vector<saiSound*> saiSoundManager::s_vecSounds;

//Sound
saiSound::saiSound(std::string p_sName)
{
    std::string filename = saiOptions::getPaths().f_sSoundpath + p_sName;
    sound = Mix_LoadWAV(filename.c_str());
    if(sound == NULL)
    {
        std::cout << "Error loading Sound " << filename << std::endl;
    }
    m_sName = p_sName;
}

saiSound::~saiSound()
{
    Mix_FreeChunk(sound);
}

void saiSound::play()
{
    Mix_PlayChannel(-1,sound,0);
}


//Sound Manager
bool saiSoundManager::init()
{
    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)== -1)
    {
        return false;
    }

    std::vector<std::string> names = getFilesFromDir(saiOptions::getPaths().f_sSoundpath);
    for(unsigned int i=0;i<names.size();i++)
    {
        saiSound* newSound = new saiSound(names[i]);
        s_vecSounds.push_back(newSound);
    }
    return true;
}

void saiSoundManager::cleanUp()
{
    for(unsigned int i=0;i<s_vecSounds.size();i++)
    {
        delete s_vecSounds[i];
    }
    Mix_CloseAudio();
}

void saiSoundManager::play(std::string p_sName)
{
    for(unsigned int i=0;i<s_vecSounds.size();i++)
    {
        if(s_vecSounds[i]->getName() == p_sName)
        {
            s_vecSounds[i]->play();
        }
    }
}

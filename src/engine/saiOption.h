////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "saiBase.h"

class saiOptions
{
    public:

        typedef struct
        {
            int m_iScreenWidth;
            int m_iScreenHeight;
            int m_iScreenCenterX;
            int m_iScreenCenterY;
            int m_iScreenPosX;
            int m_iScreenPosY;
            float m_fFov;
            float m_fNearDistance;
            float m_fFarDistance;
            bool m_bFullscreen;
            std::string m_sCaption;
            int m_iMusicVolume;
            int m_iSoundVolume;
            std::string m_sTexFilter;
            float m_fColorRed;
            float m_fColorGreen;
            float m_fColorBlue;
        }saiConfiguration;

        typedef struct
        {
            std::string f_sModelpath;
            std::string f_sTexturepath;
            std::string f_sShaderpath;
            std::string f_sSoundpath;
            std::string f_sMappath;
            std::string f_sMaterialpath;
            std::string f_sScriptpath;
            std::string f_sFontpath;
            std::string f_sAnimationpath;
        }saiPaths;

        static void loadOptions();
        static void loadOptions(std::string fname);

        static int screenWidth;
        static int screenHeight;
        static int screenCenterX;
        static int screenCenterY;
        static bool isRunning;
        static float nearDistance;
        static float farDistance;
        static bool bDebugView;
        static saiConfiguration getConfig(){return m_Config;}
        static saiPaths getPaths(){return m_Paths;}
    private:
        static saiConfiguration m_Config;
        static saiPaths m_Paths;
};

#endif // _OPTIONS_H

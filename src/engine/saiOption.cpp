////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiOption.h"

saiOptions::saiConfiguration saiOptions::m_Config;
saiOptions::saiPaths saiOptions::m_Paths;

float saiOptions::nearDistance = 0.1*0.01f;
float saiOptions::farDistance = 3000.0f*0.01;

bool saiOptions::isRunning = true;
bool saiOptions::bDebugView = false;

void saiOptions::loadOptions()
{
    m_Config.m_iScreenWidth = 640;
    m_Config.m_iScreenHeight = 480;
    m_Config.m_iScreenCenterX = 320;
    m_Config.m_iScreenCenterY = 240;
    m_Config.m_bFullscreen = false;
    m_Config.m_iScreenPosX = 50;
    m_Config.m_iScreenPosY = 50;
    m_Config.m_sCaption = "game";
    m_Config.m_fFov = 45.0;
    m_Config.m_fFarDistance = 1000.0;
    m_Config.m_fNearDistance = 0.1;
    m_Config.m_iMusicVolume = 100;
    m_Config.m_iSoundVolume = 100;
    m_Config.m_sTexFilter = "linear";
    m_Config.m_fColorRed = 0.2;
    m_Config.m_fColorGreen = 0.3;
    m_Config.m_fColorBlue = 0.8;
    m_Config.m_iMusicVolume = 100;
    m_Config.m_iSoundVolume = 100;

    m_Paths.f_sModelpath = "../assets/models/";
    m_Paths.f_sTexturepath = "../assets/textures/";
    m_Paths.f_sShaderpath = "../assets/shaders/";
    m_Paths.f_sSoundpath = "../assets/sounds/";
    m_Paths.f_sMappath = "../assets/maps/";
    m_Paths.f_sMaterialpath = "../assets/materials/";
    m_Paths.f_sScriptpath = "../scripts/";
    m_Paths.f_sFontpath = "../assets/fonts/";
    m_Paths.f_sAnimationpath = "../assets/animations/";
}

void saiOptions::loadOptions(std::string fname)
{
    std::cout << "loading config-file:" << fname << std::endl;
    loadOptions();
    std::vector<std::string> lines = loadTextfile(fname);
    if(lines.size() > 0)
    {
        for(unsigned int i=0;i<lines.size();i++)
        {
            if(getParam(lines[i]) == "screen")
            {
                i++;
                while(lines[i][0] != '}')
                {
                    if(getParam(lines[i]) == "width")
                    {
                        int width;
                        sscanf(lines[i].c_str(),"width = %i",&width);
                        m_Config.m_iScreenWidth = width;
                        m_Config.m_iScreenCenterX = width/2;
                    }
                    else if(getParam(lines[i]) == "height")
                    {
                        int height;
                        sscanf(lines[i].c_str(),"height = %i",&height);
                        m_Config.m_iScreenHeight = height;
                        m_Config.m_iScreenCenterY = height/2;
                    }
                    else if(getParam(lines[i]) == "caption")
                    {
                        char cap[32];
                        sscanf(lines[i].c_str(),"caption = %s",cap);
                        std::string caption(cap);
                        m_Config.m_sCaption = caption;
                    }
                    else if(getParam(lines[i]) == "posX")
                    {
                        int posx;
                        sscanf(lines[i].c_str(),"posX = %i",&posx);
                        m_Config.m_iScreenPosX = posx;
                    }
                    else if(getParam(lines[i]) == "posY")
                    {
                        int posy;
                        sscanf(lines[i].c_str(),"posY = %i",&posy);
                        m_Config.m_iScreenPosY = posy;
                    }
                    i++;
                }
            }
            else if(getParam(lines[i]) == "graphics")
            {
                i++;
                while(lines[i][0] != '}')
                {
                    if(getParam(lines[i]) == "neardistance")
                    {
                        float nearD;
                        sscanf(lines[i].c_str(),"neardistance = %f",&nearD);
                        m_Config.m_fNearDistance = nearD*0.01;
                    }
                    else if(getParam(lines[i]) == "fardistance")
                    {
                        float farD;
                        sscanf(lines[i].c_str(),"fardistance = %f",&farD);
                        m_Config.m_fFarDistance = farD*0.01;
                    }
                    else if(getParam(lines[i]) == "fov")
                    {
                        float fFov;
                        sscanf(lines[i].c_str(),"fov = %f",&fFov);
                        m_Config.m_fFov = fFov;
                    }
                    else if(getParam(lines[i]) == "texturefilter")
                    {
                        char fil[32];
                        sscanf(lines[i].c_str(),"texturefilter = %s",fil);
                        std::string filter(fil);
                        m_Config.m_sTexFilter = filter;
                    }
                    else if(getParam(lines[i]) == "screencolor")
                    {
                        float r,g,b;
                        sscanf(lines[i].c_str(),"screencolor = %f %f %f",&r,&g,&b);
                        m_Config.m_fColorRed = r;
                        m_Config.m_fColorGreen = g;
                        m_Config.m_fColorBlue = b;
                    }
                    i++;
                }
            }
            else if(getParam(lines[i]) == "sound")
            {
                i++;
                while(lines[i][0] != '}')
                {
                    if(getParam(lines[i]) == "musicvolume")
                    {
                        int music;
                        sscanf(lines[i].c_str(),"musicvolume = %i",&music);
                        m_Config.m_iMusicVolume = music;
                    }
                    else if(getParam(lines[i]) == "soundvolume")
                    {
                        int sound;
                        sscanf(lines[i].c_str(),"soundvolume = %i",&sound);
                        m_Config.m_iSoundVolume = sound;
                    }
                    i++;
                }
            }
            else if(getParam(lines[i]) == "paths")
            {
                i++;
                while(lines[i][0] != '}')
                {
                    if(getParam(lines[i]) == "modelpath")
                    {
                        char mdl[32];
                        sscanf(lines[i].c_str(),"modelpath = %s",mdl);
                        std::string model(mdl);
                        m_Paths.f_sModelpath = model;
                    }
                    else if(getParam(lines[i]) == "texturepath")
                    {
                        char tex[32];
                        sscanf(lines[i].c_str(),"texturepath = %s",tex);
                        std::string texture(tex);
                        m_Paths.f_sTexturepath = texture;
                    }
                    else if(getParam(lines[i]) == "shaderpath")
                    {
                        char sha[32];
                        sscanf(lines[i].c_str(),"shaderpath = %s",sha);
                        std::string shader(sha);
                        m_Paths.f_sShaderpath = shader;
                    }
                    else if(getParam(lines[i]) == "soundpath")
                    {
                        char sou[32];
                        sscanf(lines[i].c_str(),"soundpath = %s",sou);
                        std::string sound(sou);
                        m_Paths.f_sSoundpath = sound;
                    }
                    else if(getParam(lines[i]) == "mappath")
                    {
                        char mp[32];
                        sscanf(lines[i].c_str(),"mappath = %s",mp);
                        std::string mapp(mp);
                        m_Paths.f_sMappath = mapp;
                    }
                    else if(getParam(lines[i]) == "materialpath")
                    {
                        char mt[32];
                        sscanf(lines[i].c_str(),"materialpath = %s",mt);
                        std::string mat(mt);
                        m_Paths.f_sMaterialpath = mat;
                    }
                    else if(getParam(lines[i]) == "scriptpath")
                    {
                        char scr[32];
                        sscanf(lines[i].c_str(),"scriptpath = %s",scr);
                        std::string scri(scr);
                        m_Paths.f_sScriptpath = scri;
                    }
                    else if(getParam(lines[i]) == "fontpath")
                    {
                        char fnt[32];
                        sscanf(lines[i].c_str(),"fontpath = %s",fnt);
                        std::string font(fnt);
                        m_Paths.f_sFontpath = font;
                    }
                    else if(getParam(lines[i]) == "animationpath")
                    {
                        char ani[32];
                        sscanf(lines[i].c_str(),"animationpath = %s",ani);
                        std::string anim(ani);
                        m_Paths.f_sAnimationpath = anim;
                    }
                    i++;
                }
            }
        }
    }
    else
    {
        std::cout << "error: couldn't load configuration\n";
    }
}

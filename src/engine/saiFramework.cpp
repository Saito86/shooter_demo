////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiFramework.h"

SDL_Window* saiFramework::window;

saiFramework::saiFramework()
{
    flags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
    startTicks = 0;
}

saiFramework::~saiFramework()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

bool saiFramework::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    saiOptions::loadOptions("../options.cfg");

    //create window
    window = SDL_CreateWindow(saiOptions::getConfig().m_sCaption.c_str(),saiOptions::getConfig().m_iScreenPosX,saiOptions::getConfig().m_iScreenPosY,saiOptions::getConfig().m_iScreenWidth,saiOptions::getConfig().m_iScreenHeight,flags);
    if(!window)
    {
        std::cout << "Error: couldn't create Window...\n";
        return false;
    }

    glContext = SDL_GL_CreateContext(window);

    //needed for modern opengl
    GLenum status = glewInit();
    if(status != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW\n";
        return false;
    }

    //print supported opengl version
    const unsigned char* glTxt = glGetString(GL_VERSION);
    std::cout << "Opengl version: " << glTxt << std::endl;

    //set background color
    glClearColor(saiOptions::getConfig().m_fColorRed,saiOptions::getConfig().m_fColorGreen,saiOptions::getConfig().m_fColorBlue,1.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    if(TTF_Init() == -1)
    {
        std::cout << "Error loading ttf-library\n";
        return false;
    }

    return true;
}

void saiFramework::beginScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void saiFramework::endScene()
{
    SDL_GL_SwapWindow(window);
}

void saiFramework::set3d()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(saiOptions::getConfig().m_fFov,(float)saiOptions::getConfig().m_iScreenWidth/saiOptions::getConfig().m_iScreenHeight,saiOptions::getConfig().m_fNearDistance,saiOptions::getConfig().m_fFarDistance);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void saiFramework::set2d()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,saiOptions::getConfig().m_iScreenWidth,saiOptions::getConfig().m_iScreenHeight,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void saiFramework::update()
{
    startTicks = SDL_GetTicks();
}

void saiFramework::capFPS(int fps)
{
    if(getTicks() < 1000/fps)
    {
        SDL_Delay((1000/fps)-getTicks());
    }
}

int saiFramework::getTicks()
{
    return SDL_GetTicks() - startTicks;
}

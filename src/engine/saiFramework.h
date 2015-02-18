////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H

#include "saiBase.h"
#include "saiOption.h"

class saiFramework
{
    public:
        saiFramework();
        ~saiFramework();
        bool init();
        void beginScene();
        void endScene();
        void set3d();
        void set2d();
        static SDL_Window* window;
        void capFPS(int fps);
        void update();
    private:
        SDL_GLContext glContext;
        Uint32 flags;
        int getTicks();
        int startTicks;
};

#endif // _FRAMEWORK_H

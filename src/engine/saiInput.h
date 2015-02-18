////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#ifndef _INPUT_H
#define _INPUT_H

#include "saiFramework.h"

//store relevant keys in a struct
struct saiKeyMap
{
    bool up;
    bool left;
    bool right;
    bool down;
    int mousePosX;
    int mousePosY;
    bool mouseLeft;
    bool mouseRight;
    bool mouseMiddle;
    bool jump;
    bool sprint;
    bool sneak;
    bool use;
    bool reload;
};

class saiInput
{
    public:
        saiInput();
        ~saiInput();
        bool init();
        bool update();
        static saiKeyMap keyMap;
        static void warpMouse(int x,int y);
        static void showCursor(bool b);
    private:
        SDL_Event evt;
        SDL_GameController* m_Controller1;
};

#endif // _INPUT_H

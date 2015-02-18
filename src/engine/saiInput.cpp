////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiInput.h"

saiKeyMap saiInput::keyMap;

saiInput::saiInput()
{
    m_Controller1 = NULL;
}

saiInput::~saiInput()
{
    if(m_Controller1 != NULL)
        SDL_GameControllerClose(m_Controller1);
}

bool saiInput::init()
{
    for(int i=0;i<SDL_NumJoysticks();++i)
    {
        if(SDL_IsGameController(i))
        {
            m_Controller1 = SDL_GameControllerOpen(i);
            if(m_Controller1)
            {
                break;
            }
            else
            {
                std::cout << "Error: couldn't open gamecontroller " << i << " " << SDL_GetError() << std::endl;
            }
        }
    }
    return true;
}

void saiInput::warpMouse(int x,int y)
{
    SDL_WarpMouseInWindow(saiFramework::window,x,y);
}

void saiInput::showCursor(bool b)
{
    if(b)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

bool saiInput::update()
{
    SDL_GetMouseState(&keyMap.mousePosX,&keyMap.mousePosY); // get mouse input
    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                if(evt.key.keysym.sym == SDLK_w)
                {
                    keyMap.up = true;
                }
                else if(evt.key.keysym.sym == SDLK_s)
                {
                    keyMap.down = true;
                }
                else if(evt.key.keysym.sym == SDLK_a)
                {
                    keyMap.left = true;
                }
                else if(evt.key.keysym.sym == SDLK_d)
                {
                    keyMap.right = true;
                }
                else if(evt.key.keysym.sym == SDLK_SPACE)
                {
                    keyMap.jump = true;
                }
                else if(evt.key.keysym.sym == SDLK_LSHIFT)
                {
                    keyMap.sprint = true;
                }
                else if(evt.key.keysym.sym == SDLK_LCTRL)
                {
                    keyMap.sneak = true;
                }
                else if(evt.key.keysym.sym == SDLK_r)
                {
                    keyMap.reload = true;
                }
                break;
            case SDL_KEYUP:
                if(evt.key.keysym.sym == SDLK_w)
                {
                    keyMap.up = false;
                }
                else if(evt.key.keysym.sym == SDLK_s)
                {
                    keyMap.down = false;
                }
                else if(evt.key.keysym.sym == SDLK_a)
                {
                    keyMap.left = false;
                }
                else if(evt.key.keysym.sym == SDLK_d)
                {
                    keyMap.right = false;
                }
                else if(evt.key.keysym.sym == SDLK_SPACE)
                {
                    keyMap.jump = false;
                }
                else if(evt.key.keysym.sym == SDLK_LSHIFT)
                {
                    keyMap.sprint = false;
                }
                else if(evt.key.keysym.sym == SDLK_LCTRL)
                {
                    keyMap.sneak = false;
                }
                else if(evt.key.keysym.sym == SDLK_r)
                {
                    keyMap.reload = false;
                }
                else if(evt.key.keysym.sym == SDLK_ESCAPE)
                {
                    return false;
                }
                else if(evt.key.keysym.sym == SDLK_F12)
                {
                    return false;
                }
                else if(evt.key.keysym.sym == SDLK_F11)
                {
                    if(saiOptions::bDebugView)
                        saiOptions::bDebugView = false;
                    else
                        saiOptions::bDebugView = true;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(evt.button.button == SDL_BUTTON_LEFT)
                {
                    keyMap.mouseLeft = true;
                }
                else if(evt.button.button == SDL_BUTTON_RIGHT)
                {
                    keyMap.mouseRight = true;
                }
                else if(evt.button.button == SDL_BUTTON_MIDDLE)
                {
                    keyMap.mouseMiddle = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(evt.button.button == SDL_BUTTON_LEFT)
                {
                    keyMap.mouseLeft = false;
                }
                else if(evt.button.button == SDL_BUTTON_RIGHT)
                {
                    keyMap.mouseRight = false;
                }
                else if(evt.button.button == SDL_BUTTON_MIDDLE)
                {
                    keyMap.mouseMiddle = false;
                }
                break;
            default:
                break;
        }
    }
    return true;
}

#ifndef __EVENT_BASE_H__
#define __EVENT_BASE_H__

#include "SDL2/SDL.h"

namespace Engine
{
    class EventBase 
    {
        public:
        virtual void handleKeyUp(SDL_Keycode key);
        virtual void handleKeyDown(SDL_Keycode key);
        virtual void handleText(char* characters);
    };
}

#endif
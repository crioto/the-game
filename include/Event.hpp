#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "EventBase.hpp"


namespace Engine 
{
    typedef std::vector<EventBase*> EventSubscriptions;

    class Event
    {
        public:
        Event();
        ~Event();
        void process(SDL_Event* event);
        void subscribe(EventBase* eb);
        void keyUp(SDL_Keycode key);
        void keyDown(SDL_Keycode key);
        void keyText(char* characters);
        private:
        EventSubscriptions _events;
    };
}

#endif

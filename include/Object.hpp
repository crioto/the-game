#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Engine {
    class Object {
        public:
        Object(SDL_Renderer *renderer, const std::string& filename);
        ~Object();
        bool Load();
        void setPosition(int x, int y);
        void Render();
        private:
        std::string _filename;
        SDL_Renderer *_renderer;
        SDL_Texture *_texture;
        int _width;
        int _height;
        int _x;
        int _y;
    };
};

#endif
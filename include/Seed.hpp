#ifndef __SEED_H__
#define __SEED_H__

#include <cmath>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include "ConsoleCommand.hpp"

// Perlin noise implementation based on https://flafla2.github.io/2014/08/09/perlinnoise.html

namespace Engine
{
    class Seed : public ConsoleCommand
    { 
        public:
        // static const int permutationSize = 512;
        Seed(SDL_Renderer* renderer, int seed);
        ~Seed();

        bool handleConsoleCommand(const std::string& command);

        double perlin(double x, double y, double z);
        double fade(double t);
        int inc(int num);
        double grad(int hash, double x, double y, double z);
        double lerp(double a, double b, double x);
        void render();
        void toggleDebug();
        int convert(double v);
        private:
        SDL_Renderer* _renderer;
        bool _debug;
        int _seed;
        int _repeat;
        static int p[512];
    };
}

#endif
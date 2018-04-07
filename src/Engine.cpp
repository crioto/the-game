#include "Engine.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

namespace Engine {

//int roll(int min, int max)
//{
//    srand(time(NULL));
//
//	return (rand() % 3) + 1;
//}

Engine::Engine(std::vector<std::string> args)
{
    _args = args;
    _running = false;
    _sim = new Simulation();
}

Engine::~Engine() {
    TTF_Quit();
    SDL_Quit();
}

void Engine::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL2: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Failed to initialize SDL2 hinting: " << SDL_GetError()
                  << std::endl;
        return;
    }

    if ((_window = SDL_CreateWindow("My SDL Game", SDL_WINDOWPOS_UNDEFINED,
             SDL_WINDOWPOS_UNDEFINED, 1024, 768,
             SDL_WINDOW_SHOWN))
        == NULL) {
        std::cout << "Failed to initialize SDL2 window: " << SDL_GetError()
                  << std::endl;
        return;
    }

    // _surface = SDL_GetWindowSurface(_window);

    if ((_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        std::cout << "Failed to create SDL Renderer: " << SDL_GetError()
                  << std::endl;
        return;
    }

    if (TTF_Init() < 0) 
    {
        std::cout << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x88, 0xFF);
}

void Engine::deinitialize()
{
    std::cout << "Deinitializing" << std::endl;
}

int Engine::run()
{
    Console *console = new Console(_renderer);
    console->subscribe(_sim);
    Event *eventSystem = new Event();

    // Add random here
    Level* level = new Level("0");
    console->subscribe(level);

    Seed* seed = new Seed(_renderer, 0);
    console->subscribe(seed);

    Scene* scene = new Scene(_renderer);
    int offset = 0;
    for (int y = -100; y < 300; y = y + 32) {
        if (offset == 0) {
            offset = 64;
        } else {
            offset = 0;
        }
        for (int x = -100; x < 1000; x = x + 64) {
            Object* obj = new Object(_renderer, "../assets/box_grass.png");
            obj->Load();
            obj->setPosition(x + offset, y);
            scene->addObject(obj);
        }
    }

    // int cur = 1;
    // int ycur = 0;

    // for (int y = -100; y < 1000; y = y + 16) {
    //     if (offset == 0) {
    //         offset = 16;
    //     } else {
    //         offset = 0;
    //     }
    //     ycur++;
    //     if (ycur >= 4) {
    //         ycur = 1;
    //     }
    //     cur = ycur;
    //     for (int x = -100; x < 1000; x = x + 32) {
    //         cur++;
    //         if (cur >= 4) {
    //             cur = 1;
    //         }
    //         char filename[128];
    //         std::sprintf(filename, "../assets/grass_%d.png", cur);
    //         Object* obj = new Object(_renderer, std::string(filename));
    //         obj->Load();
    //         obj->setPosition(x + offset, y);
    //         scene->addObject(obj);
    //     }
    // }


    Object* th = new Object(_renderer, "../assets/treehouse.png");
    th->Load();
    th->setPosition(400, 420);
    scene->addObject(th);

    Object* w1 = new Object(_renderer, "../assets/wall2_n.png");
    w1->Load();
    w1->setPosition(128, 128);
    scene->addObject(w1);

    Object* window = new Object(_renderer, "../assets/window_n.png");
    window->Load();
    window->setPosition(128, 128);
    scene->addObject(window);

    Object* w2 = new Object(_renderer, "../assets/wall2_n.png");
    w2->Load();
    w2->setPosition(128 + 32, 128 - 16);
    scene->addObject(w2);

    Object* w3 = new Object(_renderer, "../assets/wall_w.png");
    w3->Load();
    w3->setPosition(128 - 32, 128);
    scene->addObject(w3);

    Object* w4 = new Object(_renderer, "../assets/wall_w.png");
    w4->Load();
    w4->setPosition(128 - 64, 128 - 16);
    scene->addObject(w4);

    Object* door = new Object(_renderer, "../assets/door_center_w.png");
    door->Load();
    door->setPosition(128 - 64, 128 - 16);
    scene->addObject(door);

    Building *building = new Building(_renderer, 202220, 300, 400);
    building->generate();

    eventSystem->subscribe(console);

    SDL_Event event;
    _running = true;
    while (_sim->getState() != SIM_SHUTDOWN) {
        while (SDL_PollEvent(&event))
        {
            eventSystem->process(&event);
            //genericEvent->process(&event);
        }
        // switch (event.type) {
        // case SDL_QUIT:
        //     _running = false;
        //     break;
        // case SDL_KEYDOWN:
        //     if (event.key.keysym.sym == SDLK_q) {
        //         console->activate();
        //     }
        //     break;
        // case SDL_TEXTINPUT:
        //     console->handleText(std::string(event.text.text));
        //     break;
        // }
        SDL_RenderClear(_renderer);
        scene->Render();
        building->render();
        seed->render();
        console->Render();
        SDL_RenderPresent(_renderer);
    }
    deinitialize();
    delete console;
    return 0;
}
}
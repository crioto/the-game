#include <iostream>

#include "Engine.hpp"

std::vector<std::string> fill_args(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (auto i = 1; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    return args;
}

int main(int argc, char* argv[]) {
    Engine::Engine engine(fill_args(argc, argv));
    engine.initialize();
    return engine.run();
}
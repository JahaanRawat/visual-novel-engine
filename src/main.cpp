#include "Game.h"
#include <iostream>
#include <exception>

int main(int /* argc */, char* /* argv */[]) {
    try {
        auto game = std::make_unique<Game>();
        
        if (!game->Initialize("Visual Novel Game", 1280, 720)) {
            std::cerr << "Failed to initialize game!" << std::endl;
            return -1;
        }
        
        game->Run();
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
        return -1;
    }
}
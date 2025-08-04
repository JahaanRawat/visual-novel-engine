#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class SDLManager {
private:
    bool initialized = false;
    
public:
    SDLManager() = default;
    ~SDLManager() {
        cleanup();
    }
    
    // Non-copyable, non-movable
    SDLManager(const SDLManager&) = delete;
    SDLManager& operator=(const SDLManager&) = delete;
    SDLManager(SDLManager&&) = delete;
    SDLManager& operator=(SDLManager&&) = delete;
    
    bool initialize() {
        if (initialized) return true;
        
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            return false;
        }
        
        if (!TTF_Init()) {
            SDL_Quit();
            return false;
        }
        
        initialized = true;
        return true;
    }
    
    void cleanup() {
        if (initialized) {
            TTF_Quit();
            SDL_Quit();
            initialized = false;
        }
    }
    
    bool isInitialized() const { return initialized; }
};
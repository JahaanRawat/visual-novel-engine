#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include <memory>
#include "SDLWrappers.h"

class ResourceManager {
private:
    static std::unique_ptr<ResourceManager> instance;
    std::map<std::string, std::shared_ptr<SDL_Texture>> textures;
    SDL_Renderer* renderer;
    
    ResourceManager() : renderer(nullptr) {}
    
public:
    // Allow make_unique to access constructor
    struct PrivateTag {};
    ResourceManager(PrivateTag) : renderer(nullptr) {}
    ~ResourceManager() { UnloadAll(); }
    
    static ResourceManager& GetInstance();
    static void Initialize();
    static void Shutdown();
    
    void SetRenderer(SDL_Renderer* renderer);
    std::shared_ptr<SDL_Texture> LoadTexture(const std::string& path);
    std::shared_ptr<SDL_Texture> GetTexture(const std::string& path);
    void UnloadTexture(const std::string& path);
    void UnloadAll();
};
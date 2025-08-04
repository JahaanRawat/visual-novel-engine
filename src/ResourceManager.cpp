#include "ResourceManager.h"
#include <iostream>

std::unique_ptr<ResourceManager> ResourceManager::instance = nullptr;

ResourceManager& ResourceManager::GetInstance() {
    if (!instance) {
        instance = std::make_unique<ResourceManager>(PrivateTag{});
    }
    return *instance;
}

void ResourceManager::Initialize() {
    if (!instance) {
        instance = std::make_unique<ResourceManager>(PrivateTag{});
    }
}

void ResourceManager::Shutdown() {
    if (instance) {
        instance->UnloadAll();
        instance.reset();
    }
}

// Destructor is defaulted in header

void ResourceManager::SetRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(const std::string& path) {
    // Check if texture is already loaded
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }
    
    // Load new texture
    auto surface = make_surface_from_file(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << path << " Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    auto texture = make_texture_from_surface(renderer, surface.get());
    if (!texture) {
        std::cerr << "Failed to create texture: " << path << " Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    // Convert unique_ptr to shared_ptr for caching
    auto shared_texture = std::shared_ptr<SDL_Texture>(texture.release(), SDLTextureDeleter());
    textures[path] = shared_texture;
    return shared_texture;
}

std::shared_ptr<SDL_Texture> ResourceManager::GetTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }
    return LoadTexture(path);
}

void ResourceManager::UnloadTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        textures.erase(it); // shared_ptr handles cleanup automatically
    }
}

void ResourceManager::UnloadAll() {
    textures.clear(); // shared_ptr handles cleanup automatically
}
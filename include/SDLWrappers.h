#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

// Custom deleters for SDL resources
struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const {
        if (window) SDL_DestroyWindow(window);
    }
};

struct SDLRendererDeleter {
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) SDL_DestroyRenderer(renderer);
    }
};

struct SDLTextureDeleter {
    void operator()(SDL_Texture* texture) const {
        if (texture) SDL_DestroyTexture(texture);
    }
};

struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        if (surface) SDL_DestroySurface(surface);
    }
};

struct TTFFontDeleter {
    void operator()(TTF_Font* font) const {
        if (font) TTF_CloseFont(font);
    }
};

// Smart pointer type aliases
using SDLWindowPtr = std::unique_ptr<SDL_Window, SDLWindowDeleter>;
using SDLRendererPtr = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>;
using SDLTexturePtr = std::unique_ptr<SDL_Texture, SDLTextureDeleter>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, SDLSurfaceDeleter>;
using TTFFontPtr = std::unique_ptr<TTF_Font, TTFFontDeleter>;

// Helper factory functions
inline SDLWindowPtr make_window(const char* title, int w, int h, Uint32 flags) {
    return SDLWindowPtr(SDL_CreateWindow(title, w, h, flags));
}

inline SDLRendererPtr make_renderer(SDL_Window* window, const char* name) {
    return SDLRendererPtr(SDL_CreateRenderer(window, name));
}

inline SDLTexturePtr make_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface) {
    return SDLTexturePtr(SDL_CreateTextureFromSurface(renderer, surface));
}

inline SDLSurfacePtr make_surface_from_file(const char* file) {
    return SDLSurfacePtr(IMG_Load(file));
}

inline TTFFontPtr make_font(const char* file, int ptsize) {
    return TTFFontPtr(TTF_OpenFont(file, ptsize));
}
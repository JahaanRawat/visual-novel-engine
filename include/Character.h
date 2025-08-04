#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "SDLWrappers.h"

enum class CharacterLayer {
    BASE,
    HAIR,
    EYES,
    OUTFIT,
    ACCESSORY
};

struct CharacterPart {
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect sourceRect;
    SDL_Color tintColor;
    
    CharacterPart() : texture(nullptr), tintColor{255, 255, 255, 255} {
        sourceRect = {0, 0, 0, 0};
    }
};

class Character {
private:
    std::map<CharacterLayer, CharacterPart> layers;
    SDL_Point position;
    float scale;
    
    // Animation properties
    int currentFrame;
    float animationTime;
    float frameTime;
    bool isAnimating;
    
public:
    Character();
    ~Character();
    
    void SetPart(CharacterLayer layer, std::shared_ptr<SDL_Texture> texture, const SDL_Rect& sourceRect);
    void SetPartColor(CharacterLayer layer, const SDL_Color& color);
    void SetPosition(int x, int y);
    void SetScale(float s);
    
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    
    void StartAnimation();
    void StopAnimation();
    
    SDL_Point GetPosition() const { return position; }
};
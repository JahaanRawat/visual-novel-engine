#include "Character.h"

Character::Character() : scale(1.0f), currentFrame(0), animationTime(0.0f), 
                        frameTime(0.1f), isAnimating(false) {
    position.x = 640;
    position.y = 360;
}

Character::~Character() {
    // Textures are managed by shared_ptr, so automatic cleanup
}

void Character::SetPart(CharacterLayer layer, std::shared_ptr<SDL_Texture> texture, const SDL_Rect& sourceRect) {
    layers[layer].texture = texture;
    layers[layer].sourceRect = sourceRect;
}

void Character::SetPartColor(CharacterLayer layer, const SDL_Color& color) {
    if (layers.find(layer) != layers.end()) {
        layers[layer].tintColor = color;
    }
}

void Character::SetPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Character::SetScale(float s) {
    scale = s;
}

void Character::Update(float deltaTime) {
    if (isAnimating) {
        animationTime += deltaTime;
        if (animationTime >= frameTime) {
            animationTime = 0.0f;
            currentFrame = (currentFrame + 1) % 4;
        }
    }
}

void Character::Render(SDL_Renderer* renderer) {
    // Render each layer in order
    for (auto layer : {CharacterLayer::BASE, CharacterLayer::OUTFIT, 
                      CharacterLayer::HAIR, CharacterLayer::EYES, 
                      CharacterLayer::ACCESSORY}) {
        
        auto it = layers.find(layer);
        if (it != layers.end() && it->second.texture) {
            SDL_FRect destRect;
            destRect.w = static_cast<float>(it->second.sourceRect.w * scale);
            destRect.h = static_cast<float>(it->second.sourceRect.h * scale);
            destRect.x = static_cast<float>(position.x - destRect.w / 2);
            destRect.y = static_cast<float>(position.y - destRect.h / 2);
            
            // Apply tint color
            SDL_SetTextureColorMod(it->second.texture.get(), 
                                  it->second.tintColor.r,
                                  it->second.tintColor.g,
                                  it->second.tintColor.b);
            SDL_SetTextureAlphaMod(it->second.texture.get(), it->second.tintColor.a);
            
            // Calculate source rect for animation
            SDL_FRect srcRect;
            srcRect.x = static_cast<float>(it->second.sourceRect.x);
            srcRect.y = static_cast<float>(it->second.sourceRect.y);
            srcRect.w = static_cast<float>(it->second.sourceRect.w);
            srcRect.h = static_cast<float>(it->second.sourceRect.h);
            if (isAnimating && layer == CharacterLayer::BASE) {
                srcRect.x = static_cast<float>(currentFrame * it->second.sourceRect.w);
            }
            
            SDL_RenderTexture(renderer, it->second.texture.get(), &srcRect, &destRect);
        }
    }
}

void Character::StartAnimation() {
    isAnimating = true;
    currentFrame = 0;
    animationTime = 0.0f;
}

void Character::StopAnimation() {
    isAnimating = false;
    currentFrame = 0;
}
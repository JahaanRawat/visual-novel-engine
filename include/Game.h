#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include "Character.h"
#include "DialogueSystem.h"
#include "ResourceManager.h"
#include "SDLWrappers.h"
#include "SDLManager.h"

class Game {
private:
    SDLManager sdlManager;
    SDLWindowPtr window;
    SDLRendererPtr renderer;
    bool isRunning;
    
    int windowWidth;
    int windowHeight;
    
    std::unique_ptr<Character> playerCharacter;
    std::unique_ptr<DialogueSystem> dialogueSystem;
    
    std::shared_ptr<SDL_Texture> backgroundTexture;
    
public:
    Game();
    ~Game();
    
    bool Initialize(const std::string& title, int width, int height);
    void Run();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void Clean();
    
    SDL_Renderer* GetRenderer() const { return renderer.get(); }
    bool IsRunning() const { return isRunning; }
};
#include "Game.h"
#include <iostream>
#include "ResourceManager.h"

Game::Game() : isRunning(false), windowWidth(1280), windowHeight(720) {}

Game::~Game() {
    Clean();
}

bool Game::Initialize(const std::string& title, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    if (!sdlManager.initialize()) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = make_window(title.c_str(), windowWidth, windowHeight, 0);
    
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = make_renderer(window.get(), nullptr);
    
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    isRunning = true;
    
    // Initialize ResourceManager
    ResourceManager::Initialize();
    ResourceManager::GetInstance().SetRenderer(renderer.get());
    
    // Initialize player character
    playerCharacter = std::make_unique<Character>();
    
    // Initialize dialogue system
    dialogueSystem = std::make_unique<DialogueSystem>(renderer.get());
    if (!dialogueSystem->Initialize()) {
        std::cerr << "Failed to initialize dialogue system" << std::endl;
        return false;
    }
    
    // Load test dialogue
    DialogueNode testDialogue;
    testDialogue.speaker = "Player";
    testDialogue.text = "Welcome to our visual novel game! Press SPACE to continue, Arrow keys to move.";
    dialogueSystem->AddDialogue(testDialogue);
    
    testDialogue.speaker = "System";
    testDialogue.text = "You can customize your character using the number keys.";
    dialogueSystem->AddDialogue(testDialogue);
    
    dialogueSystem->StartDialogue();
    
    return true;
}

void Game::Run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    float deltaTime = 0.0f;
    
    while (isRunning) {
        frameStart = SDL_GetTicks();
        
        HandleEvents();
        Update(deltaTime);
        Render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        
        deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
    }
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                isRunning = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    isRunning = false;
                } else if (event.key.key == SDLK_SPACE) {
                    if (dialogueSystem->IsActive()) {
                        dialogueSystem->NextDialogue();
                    }
                } else if (event.key.key == SDLK_LEFT) {
                    auto pos = playerCharacter->GetPosition();
                    playerCharacter->SetPosition(pos.x - 10, pos.y);
                    playerCharacter->StartAnimation();
                } else if (event.key.key == SDLK_RIGHT) {
                    auto pos = playerCharacter->GetPosition();
                    playerCharacter->SetPosition(pos.x + 10, pos.y);
                    playerCharacter->StartAnimation();
                } else if (event.key.key == SDLK_UP) {
                    auto pos = playerCharacter->GetPosition();
                    playerCharacter->SetPosition(pos.x, pos.y - 10);
                    playerCharacter->StartAnimation();
                } else if (event.key.key == SDLK_DOWN) {
                    auto pos = playerCharacter->GetPosition();
                    playerCharacter->SetPosition(pos.x, pos.y + 10);
                    playerCharacter->StartAnimation();
                } else if (event.key.key >= SDLK_1 && event.key.key <= SDLK_5) {
                    // Character customization with number keys
                    int option = event.key.key - SDLK_1;
                    SDL_Color colors[] = {
                        {255, 100, 100, 255}, // Red
                        {100, 255, 100, 255}, // Green
                        {100, 100, 255, 255}, // Blue
                        {255, 255, 100, 255}, // Yellow
                        {255, 100, 255, 255}  // Magenta
                    };
                    playerCharacter->SetPartColor(CharacterLayer::HAIR, colors[option]);
                }
                break;
            case SDL_EVENT_KEY_UP:
                if (event.key.key == SDLK_LEFT || event.key.key == SDLK_RIGHT ||
                    event.key.key == SDLK_UP || event.key.key == SDLK_DOWN) {
                    playerCharacter->StopAnimation();
                }
                break;
        }
    }
}

void Game::Update(float deltaTime) {
    playerCharacter->Update(deltaTime);
    dialogueSystem->Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer.get(), 30, 30, 40, 255);
    SDL_RenderClear(renderer.get());
    
    // Render background if available
    if (backgroundTexture) {
        SDL_RenderTexture(renderer.get(), backgroundTexture.get(), nullptr, nullptr);
    }
    
    // Render character
    playerCharacter->Render(renderer.get());
    
    // Render dialogue
    dialogueSystem->Render();
    
    SDL_RenderPresent(renderer.get());
}

void Game::Clean() {
    playerCharacter.reset();
    dialogueSystem.reset();
    backgroundTexture.reset();
    
    ResourceManager::Shutdown();
    
    // Smart pointers handle SDL resource cleanup automatically
    renderer.reset();
    window.reset();
    
    // SDLManager handles SDL cleanup automatically
}
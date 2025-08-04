#include "DialogueSystem.h"
#include <iostream>

DialogueSystem::DialogueSystem(SDL_Renderer* renderer) : 
    renderer(renderer), typewriterSpeed(30.0f), typewriterTime(0.0f), 
    currentCharIndex(0), isActive(false), isTyping(false) {
    
    // Set UI positions
    textboxRect = {100, 500, 1080, 180};
    textRect = {120, 540, 1040, 120};
    speakerRect = {120, 510, 200, 30};
}

DialogueSystem::~DialogueSystem() {
    // Smart pointers handle cleanup automatically
}

bool DialogueSystem::Initialize() {
    // Try multiple font paths
    const char* fontPaths[] = {
        "assets/fonts/arial.ttf",
        "/System/Library/Fonts/Arial.ttf",  // macOS system font
        "/System/Library/Fonts/Helvetica.ttc",  // macOS fallback
        nullptr
    };
    
    for (int i = 0; fontPaths[i] != nullptr; ++i) {
        font = make_font(fontPaths[i], 24);
        if (font) {
            std::cout << "Loaded font: " << fontPaths[i] << std::endl;
            break;
        }
    }
    
    if (!font) {
        std::cerr << "Failed to load any font. Please add arial.ttf to assets/fonts/ or install system fonts." << std::endl;
        return false;
    }
    
    // Create textbox background
    auto surface = SDLSurfacePtr(SDL_CreateSurface(textboxRect.w, textboxRect.h, SDL_PIXELFORMAT_RGBA8888));
    SDL_FillSurfaceRect(surface.get(), nullptr, SDL_MapSurfaceRGBA(surface.get(), 20, 20, 30, 230));
    
    textboxTexture = make_texture_from_surface(renderer, surface.get());
    
    return true;
}

void DialogueSystem::AddDialogue(const DialogueNode& dialogue) {
    dialogueQueue.push(dialogue);
}

void DialogueSystem::StartDialogue() {
    if (!dialogueQueue.empty()) {
        currentDialogue = dialogueQueue.front();
        dialogueQueue.pop();
        displayedText.clear();
        currentCharIndex = 0;
        typewriterTime = 0.0f;
        isActive = true;
        isTyping = true;
    }
}

void DialogueSystem::NextDialogue() {
    if (isTyping) {
        // Skip typewriter effect
        displayedText = currentDialogue.text;
        currentCharIndex = currentDialogue.text.length();
        isTyping = false;
    } else if (!currentDialogue.hasChoices) {
        if (!dialogueQueue.empty()) {
            StartDialogue();
        } else {
            isActive = false;
        }
    }
}

void DialogueSystem::SelectChoice(int choiceIndex) {
    if (currentDialogue.hasChoices && choiceIndex >= 0 && static_cast<size_t>(choiceIndex) < currentDialogue.choices.size()) {
        // Handle choice selection - in a full implementation, this would trigger events
        NextDialogue();
    }
}

void DialogueSystem::Update(float deltaTime) {
    if (!isActive || !isTyping) return;
    
    typewriterTime += deltaTime * typewriterSpeed;
    
    while (typewriterTime >= 1.0f && currentCharIndex < currentDialogue.text.length()) {
        displayedText += currentDialogue.text[currentCharIndex];
        currentCharIndex++;
        typewriterTime -= 1.0f;
    }
    
    if (currentCharIndex >= currentDialogue.text.length()) {
        isTyping = false;
    }
}

void DialogueSystem::Render() {
    if (!isActive) return;
    
    // Render textbox background
    SDL_FRect fTextboxRect = {static_cast<float>(textboxRect.x), static_cast<float>(textboxRect.y), static_cast<float>(textboxRect.w), static_cast<float>(textboxRect.h)};
    SDL_RenderTexture(renderer, textboxTexture.get(), nullptr, &fTextboxRect);
    
    // Render speaker name
    if (!currentDialogue.speaker.empty()) {
        SDL_Color color = {255, 200, 100, 255};
        auto speakerSurface = SDLSurfacePtr(TTF_RenderText_Blended(font.get(), 
                                                                    currentDialogue.speaker.c_str(), 
                                                                    0, color));
        if (speakerSurface) {
            auto speakerTexture = make_texture_from_surface(renderer, speakerSurface.get());
            
            SDL_Rect speakerDest = speakerRect;
            speakerDest.w = speakerSurface->w;
            speakerDest.h = speakerSurface->h;
            
            SDL_FRect fSpeakerDest = {static_cast<float>(speakerDest.x), static_cast<float>(speakerDest.y), static_cast<float>(speakerDest.w), static_cast<float>(speakerDest.h)};
            SDL_RenderTexture(renderer, speakerTexture.get(), nullptr, &fSpeakerDest);
        }
    }
    
    // Render dialogue text
    if (!displayedText.empty()) {
        SDL_Color color = {255, 255, 255, 255};
        auto textSurface = SDLSurfacePtr(TTF_RenderText_Blended_Wrapped(font.get(), 
                                                                        displayedText.c_str(), 
                                                                        0, color, 
                                                                        textRect.w));
        if (textSurface) {
            auto textTexture = make_texture_from_surface(renderer, textSurface.get());
            
            SDL_Rect textDest = textRect;
            textDest.w = textSurface->w;
            textDest.h = textSurface->h;
            
            SDL_FRect fTextDest = {static_cast<float>(textDest.x), static_cast<float>(textDest.y), static_cast<float>(textDest.w), static_cast<float>(textDest.h)};
            SDL_RenderTexture(renderer, textTexture.get(), nullptr, &fTextDest);
        }
    }
    
    // Render choices if available
    if (!isTyping && currentDialogue.hasChoices) {
        int yOffset = 0;
        for (size_t i = 0; i < currentDialogue.choices.size(); i++) {
            SDL_Color color = {200, 200, 255, 255};
            auto choiceSurface = SDLSurfacePtr(TTF_RenderText_Blended(font.get(), 
                                                                      currentDialogue.choices[i].text.c_str(), 
                                                                      0, color));
            if (choiceSurface) {
                auto choiceTexture = make_texture_from_surface(renderer, choiceSurface.get());
                
                SDL_Rect choiceDest = {textRect.x, textRect.y - 40 - (yOffset * 35), 
                                      choiceSurface->w, choiceSurface->h};
                
                SDL_FRect fChoiceDest = {static_cast<float>(choiceDest.x), static_cast<float>(choiceDest.y), static_cast<float>(choiceDest.w), static_cast<float>(choiceDest.h)};
                SDL_RenderTexture(renderer, choiceTexture.get(), nullptr, &fChoiceDest);
            }
            
            yOffset++;
        }
    }
}
#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "SDLWrappers.h"

struct DialogueChoice {
    std::string text;
    int nextDialogueId;
};

struct DialogueNode {
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;
    bool hasChoices;
    
    DialogueNode() : hasChoices(false) {}
};

class DialogueSystem {
private:
    TTFFontPtr font;
    SDLTexturePtr textboxTexture;
    SDL_Renderer* renderer;
    
    std::queue<DialogueNode> dialogueQueue;
    DialogueNode currentDialogue;
    
    // Text rendering
    std::string displayedText;
    float typewriterSpeed;
    float typewriterTime;
    size_t currentCharIndex;
    
    // UI positions
    SDL_Rect textboxRect;
    SDL_Rect textRect;
    SDL_Rect speakerRect;
    
    bool isActive;
    bool isTyping;
    
public:
    DialogueSystem(SDL_Renderer* renderer);
    ~DialogueSystem();
    
    bool Initialize();
    void AddDialogue(const DialogueNode& dialogue);
    void StartDialogue();
    void NextDialogue();
    void SelectChoice(int choiceIndex);
    
    void Update(float deltaTime);
    void Render();
    
    bool IsActive() const { return isActive; }
    bool HasChoices() const { return currentDialogue.hasChoices; }
    const std::vector<DialogueChoice>& GetChoices() const { return currentDialogue.choices; }
};
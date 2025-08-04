# Visual Novel Game Engine (SDL3)

A custom C++ visual novel game engine built from scratch without using any existing game engines. Features a layered character customization system, dialogue management, and player-controlled animations. Now upgraded to use SDL3 for modern graphics support.

## Prerequisites

Install SDL3 libraries on macOS:
```bash
brew install sdl3 sdl3_image sdl3_ttf pkg-config
```

## Building

Using Make:
```bash
make
```

Using CMake:
```bash
mkdir build
cd build
cmake ..
make
```

## Running
```bash
./VisualNovelGame
```

## Controls
- **SPACE**: Advance dialogue
- **Arrow Keys**: Move character (with animation)
- **Number Keys 1-5**: Change hair color
- **ESC**: Exit game

## Features
- **Modern C++ Memory Management**: Smart pointers throughout (unique_ptr, shared_ptr)
- **RAII Design**: Automatic resource cleanup with custom deleters
- **Exception Safety**: Proper error handling and resource management
- **Layered Character System**: Sprite-based customization with color tinting
- **Typewriter Dialogue Effect**: Smooth text animation with customizable speed
- **Player-Controlled Animations**: Movement with frame-based animation
- **Modular Architecture**: Easy to extend and modify

## Project Structure

```
ren_cpp/
├── CMakeLists.txt      # CMake build configuration
├── Makefile           # Alternative Make build
├── README.md          # This file
├── include/           # Header files
│   ├── Game.h         # Main game class
│   ├── Character.h    # Character system with layered sprites
│   ├── DialogueSystem.h # Visual novel dialogue management
│   └── ResourceManager.h # Texture loading and caching
├── src/               # Implementation files
│   ├── main.cpp       # Entry point
│   ├── Game.cpp       # Game loop and event handling
│   ├── Character.cpp  # Character rendering and animation
│   ├── DialogueSystem.cpp # Dialogue rendering and typewriter effect
│   └── ResourceManager.cpp # Resource management implementation
└── assets/            # Game assets (create these directories)
    ├── sprites/       # Character sprite sheets
    ├── backgrounds/   # Background images
    ├── fonts/         # TTF fonts (requires arial.ttf)
    └── ui/            # UI elements

## Memory Management

The project uses modern C++ memory management practices:

### Smart Pointers
- **std::unique_ptr**: Used for exclusive ownership (Game components, SDL resources)
- **std::shared_ptr**: Used for shared resources (textures in ResourceManager)
- **Custom Deleters**: Proper cleanup for SDL resources (SDLWindowDeleter, SDLTextureDeleter, etc.)

### RAII Classes
- **SDLManager**: Handles SDL initialization/cleanup
- **ResourceManager**: Singleton with smart pointer management
- **Custom SDL Wrappers**: Type-safe wrappers around SDL C APIs

### Exception Safety
- Exception handling in main function
- Automatic cleanup on exceptions
- No manual memory management required

## Architecture Overview

### Core Systems

1. **Game Engine (`Game.h/cpp`)**
   - SDL3-based window management
   - 60 FPS fixed timestep game loop
   - Modern event handling with SDL3's updated API
   - Scene rendering pipeline

2. **Character System (`Character.h/cpp`)**
   - Layered sprite rendering (base, hair, eyes, outfit, accessories)
   - Real-time color tinting for customization
   - Sprite animation with frame cycling
   - Position and scale management

3. **Dialogue System (`DialogueSystem.h/cpp`)**
   - Visual novel-style text boxes
   - Typewriter text effect with adjustable speed
   - Speaker name display
   - Multiple choice support
   - Dialogue queue management

4. **Resource Manager (`ResourceManager.h/cpp`)**
   - Singleton pattern with smart pointer management
   - shared_ptr texture caching to prevent duplicate loads
   - Automatic cleanup via RAII
   - Exception-safe resource loading

## API Reference

### Character Class
```cpp
// Set character parts
void SetPart(CharacterLayer layer, SDL_Texture* texture, const SDL_Rect& sourceRect);
void SetPartColor(CharacterLayer layer, const SDL_Color& color);

// Animation control
void StartAnimation();
void StopAnimation();

// Transform
void SetPosition(int x, int y);
void SetScale(float scale);
```

### DialogueSystem Class
```cpp
// Add dialogue to queue
void AddDialogue(const DialogueNode& dialogue);

// Control dialogue flow
void StartDialogue();
void NextDialogue();
void SelectChoice(int choiceIndex);

// Query state
bool IsActive() const;
bool HasChoices() const;
```

## Adding Assets

### Character Sprites
Place character sprite sheets in `assets/sprites/` with the following structure:
- Each layer should be a separate PNG file with transparency
- Animation frames should be arranged horizontally
- Recommended size: 256x256 pixels per frame

### Backgrounds
- Place in `assets/backgrounds/`
- Recommended size: 1280x720 pixels (or your target resolution)
- Format: PNG or JPG

### Fonts
- Place TTF fonts in `assets/fonts/`
- Default font: `arial.ttf` (required)
- Additional fonts can be added and loaded via ResourceManager

## Customization Guide

### Adding New Character Parts
1. Create new entries in the `CharacterLayer` enum
2. Add rendering logic in `Character::Render()`
3. Load textures using `ResourceManager::LoadTexture()`

### Creating New Dialogue Effects
1. Extend `DialogueNode` structure for new properties
2. Modify `DialogueSystem::Update()` for new effects
3. Update rendering in `DialogueSystem::Render()`

### Implementing Scenes
1. Create a base `Scene` class with virtual update/render methods
2. Inherit from `Scene` for specific game scenes
3. Add scene management to the `Game` class

## Memory Safety & Performance

### Performance Considerations
- **Smart Pointer Overhead**: Minimal - shared_ptr only for cached textures
- **Texture Caching**: Prevents duplicate loads, automatic reference counting
- **Fixed 60 FPS**: Consistent frame timing with efficient rendering
- **RAII**: Zero-cost abstraction over manual resource management
- **Minimal Runtime Allocations**: Resources loaded upfront

### Memory Safety Features
- **No Manual Memory Management**: All done via smart pointers
- **Automatic Resource Cleanup**: No memory leaks possible
- **Exception Safety**: Resources cleaned up even on exceptions
- **Type Safety**: Custom SDL wrappers prevent misuse

## Future Enhancements

- [ ] Scene transition effects
- [ ] Save/Load game state
- [ ] Audio system integration
- [ ] Particle effects for visual polish
- [ ] Script-based dialogue loading
- [ ] More character customization options
- [ ] Background animation support

## Troubleshooting

### SDL3 Not Found
If you get SDL3-related errors during compilation:
```bash
# For M1/M2 Macs
export CPATH=/opt/homebrew/include
export LIBRARY_PATH=/opt/homebrew/lib
export PKG_CONFIG_PATH=/opt/homebrew/lib/pkgconfig
```

### Vim/Neovim Setup
The project includes configuration files for Vim/Neovim:
- `.vimrc` - Vim configuration with C++ settings
- `init.lua` - Neovim configuration with LSP support
- `compile_commands.json` - For clangd language server
- `.clang-format` - Code formatting rules

See `VIM_SETUP.md` for detailed setup instructions.

### Missing Font Error
Create the fonts directory and add a TTF font:
```bash
mkdir -p assets/fonts
# Copy any TTF font to assets/fonts/arial.ttf
```

## License

This project is created for educational purposes. Feel free to use and modify as needed.
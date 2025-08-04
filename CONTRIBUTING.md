# Contributing to Visual Novel Engine

Thank you for your interest in contributing to the Visual Novel Engine! This document provides guidelines for contributing to the project.

## Development Setup

### Prerequisites
- macOS (primary development platform)
- SDL3, SDL3_image, SDL3_ttf
- Modern C++ compiler (C++17 support)
- Vim/Neovim (recommended)

### Getting Started
1. Fork the repository
2. Clone your fork: `git clone https://github.com/your-username/visual-novel-engine.git`
3. Install dependencies: `brew install sdl3 sdl3_image sdl3_ttf`
4. Build: `make`
5. Run: `make run`

## Code Style

### C++ Guidelines
- Follow the existing code style (see `.clang-format`)
- Use modern C++17 features
- Prefer smart pointers over raw pointers
- Use RAII for resource management
- Keep functions focused and small

### Formatting
- Run `make format` before committing
- Use 4 spaces for indentation
- 100 character line limit
- Include guards for all headers

### Memory Management
- Use `std::unique_ptr` for exclusive ownership
- Use `std::shared_ptr` for shared resources
- Never use `new`/`delete` directly
- All SDL resources must use custom deleters

## Commit Guidelines

### Commit Messages
- Use present tense ("Add feature" not "Added feature")
- Keep first line under 50 characters
- Reference issues/PRs when applicable
- Include `🤖 Generated with [Claude Code](https://claude.ai/code)` for AI-assisted commits

### Example
```
Add character animation blending system

- Implement smooth transitions between animation states
- Add configurable blend duration
- Update Character class with new blend methods
- Add unit tests for animation blending

Fixes #42

🤖 Generated with [Claude Code](https://claude.ai/code)
Co-Authored-By: Claude <noreply@anthropic.com>
```

## Pull Request Process

1. Create a feature branch: `git checkout -b feature/your-feature`
2. Make your changes
3. Add tests if applicable
4. Ensure code builds: `make clean && make`
5. Format code: `make format`
6. Commit changes with descriptive messages
7. Push to your fork
8. Create a Pull Request

### PR Requirements
- [ ] Code builds without warnings
- [ ] All tests pass (when implemented)
- [ ] Code is formatted (`make format`)
- [ ] Documentation updated if needed
- [ ] No memory leaks (use smart pointers)

## Project Structure

```
visual-novel-engine/
├── src/           # Implementation files
├── include/       # Header files
├── assets/        # Game assets
├── .github/       # GitHub workflows
├── Makefile       # Build system
├── CMakeLists.txt # Alternative build
└── README.md      # Project documentation
```

## Areas for Contribution

### High Priority
- [ ] Scene management system
- [ ] Save/load functionality
- [ ] Audio system integration
- [ ] More character customization options
- [ ] Linux build support

### Medium Priority
- [ ] Particle effects
- [ ] Background animations
- [ ] More dialogue effects
- [ ] Script-based dialogue loading
- [ ] Unit tests

### Low Priority
- [ ] Visual effects (screen shake, transitions)
- [ ] Multiple language support
- [ ] Plugin system
- [ ] Performance profiling tools

## Testing

Currently, the project uses manual testing. When adding features:
1. Test on macOS (primary platform)
2. Verify no memory leaks with smart pointers
3. Check that all SDL resources are properly managed
4. Test edge cases (missing assets, etc.)

## Questions?

- Open an issue for bugs or feature requests
- Check existing issues before creating new ones
- Use clear, descriptive titles
- Provide reproduction steps for bugs

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help newcomers get started
- Maintain a positive learning environment

Thank you for contributing! 🎮
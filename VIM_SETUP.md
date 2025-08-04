# Vim/Neovim Development Setup

## Quick Start

### Building and Running
```bash
# Build the project
make

# Run the game
./VisualNovelGame

# Clean build artifacts
make clean

# Build and run in one command
make run
```

### Using CMake (Alternative)
```bash
mkdir build && cd build
cmake ..
make
./VisualNovelGame
```

## Vim Configuration

### Project-Specific Setup
The project includes a `.vimrc` file with C++ optimized settings. To use it:

```bash
# Source project .vimrc in your session
:source .vimrc

# Or add to your main .vimrc:
# if filereadable('.vimrc')
#     source .vimrc
# endif
```

### Key Mappings
- `F5` - Build project (`make`)
- `F6` - Build and run (`make run`)  
- `F7` - Clean build (`make clean`)
- `<leader>g` - Grep word under cursor in project
- `<leader>h` - Switch to header file (.h)
- `<leader>c` - Switch to source file (.cpp)

## Neovim Configuration

### Project Setup
The project includes `init.lua` with Neovim-specific configuration:

```bash
# Source project config
:luafile init.lua

# Or add to your init.lua:
# local project_config = vim.fn.getcwd() .. '/init.lua'
# if vim.fn.filereadable(project_config) == 1 then
#     dofile(project_config)
# end
```

### LSP Support (clangd)
Install clangd for C++ language server support:

```bash
# macOS
brew install llvm

# The project includes compile_commands.json for clangd
```

## Development Workflow

### File Navigation
```vim
" Open file under cursor
gf

" Find files by name
:find Game.h

" Search in project
:grep -r "function_name" src/

" Navigate between header/source
<leader>h  " Go to header
<leader>c  " Go to source
```

### Code Completion & LSP
If you have nvim-lspconfig and clangd installed:
- Auto-completion with `<Tab>`
- Go to definition with `gd`
- Find references with `gr`
- Hover documentation with `K`
- Rename symbol with `<leader>rn`

### Building & Testing
```vim
" Build project
:make

" See build errors in quickfix
:copen

" Navigate build errors
:cnext
:cprev

" Run specific make targets
:make clean
:make run
```

## Plugin Recommendations

### Essential Plugins
```vim
" For Vim
Plug 'prabirshrestha/vim-lsp'
Plug 'mattn/vim-lsp-settings'
Plug 'junegunn/fzf.vim'
Plug 'tpope/vim-commentary'
Plug 'jiangmiao/auto-pairs'

" For Neovim
use 'neovim/nvim-lspconfig'
use 'nvim-treesitter/nvim-treesitter'
use 'nvim-telescope/telescope.nvim'
use 'numToStr/Comment.nvim'
use 'windwp/nvim-autopairs'
```

### Advanced Setup
```vim
" Install vim-plug first, then add to .vimrc:
call plug#begin()
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
Plug 'tpope/vim-fugitive'
Plug 'airblade/vim-gitgutter'
call plug#end()

" Useful mappings
nnoremap <C-p> :Files<CR>
nnoremap <C-f> :Rg<CR>
```

## Debugging

### GDB Integration
```bash
# Compile with debug symbols
make DEBUG=1

# Debug with GDB
gdb ./VisualNovelGame
(gdb) run
(gdb) bt    # backtrace on crash
```

### Vim GDB Plugin
```vim
" Install termdebug (built into Vim 8+)
:packadd termdebug
:Termdebug ./VisualNovelGame

" Set breakpoints
:Break main.cpp:10
:Run
```

## Code Formatting

### Using clang-format
```bash
# Format a file
clang-format -i src/Game.cpp

# Format all source files
find src include -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### Vim Integration
```vim
" Format current file
:!clang-format -i %

" Format selection
:'<,'>!clang-format
```

## Project Structure Quick Reference

```
ren_cpp/
├── src/           # Source files (.cpp)
├── include/       # Header files (.h)
├── assets/        # Game assets (fonts, sprites)
├── Makefile       # Build configuration
├── CMakeLists.txt # Alternative build system
├── .vimrc         # Project Vim config
├── init.lua       # Project Neovim config
└── compile_commands.json  # For clangd LSP
```

## Tips & Tricks

### Quick File Creation
```vim
" Create new files quickly
:e src/NewClass.cpp
:e include/NewClass.h
```

### Project-Wide Search & Replace
```vim
" Search and replace across project
:args src/*.cpp include/*.h
:argdo %s/old_function/new_function/gc | update
```

### Tags for Navigation
```bash
# Generate tags file
ctags -R src/ include/

# In Vim:
# Ctrl+] - Jump to definition
# Ctrl+T - Jump back
# :tag function_name - Find function
```

### Build Automation
Add to your `.vimrc`:
```vim
" Auto-build on save
autocmd BufWritePost *.cpp,*.h silent make!
```
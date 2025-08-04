" Project-specific Vim configuration for Visual Novel Game
" Place this in your project root or source it from your main .vimrc

" C++ settings
set cindent
set autoindent
set smartindent
set tabstop=4
set shiftwidth=4
set expandtab
set smarttab

" File type detection
filetype plugin indent on
syntax on

" Include path for this project
set path+=./include
set path+=./src
set path+=/opt/homebrew/include

" Useful mappings for C++ development
nnoremap <F5> :make<CR>
nnoremap <F6> :make run<CR>
nnoremap <F7> :make clean<CR>

" Search for word under cursor in project
nnoremap <leader>g :grep -r <cword> src/ include/<CR>

" Quick header/source switching
nnoremap <leader>h :e %:r.h<CR>
nnoremap <leader>c :e %:r.cpp<CR>

" Tag support (if you use ctags)
set tags=tags,./tags,../tags

" Error format for make
set errorformat=%f:%l:%c:\ %t%*[^:]:\ %m

" Enable mouse support
set mouse=a

" Line numbers and visual aids
set number
set relativenumber
set cursorline
set showmatch

" Search settings
set hlsearch
set incsearch
set ignorecase
set smartcase
-- Neovim configuration for Visual Novel Game project
-- Place this in your project root as init.lua or add to your main config

-- Basic settings
vim.opt.cindent = true
vim.opt.autoindent = true
vim.opt.smartindent = true
vim.opt.tabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true
vim.opt.smarttab = true

-- File type detection
vim.cmd('filetype plugin indent on')
vim.cmd('syntax on')

-- Include paths for this project
vim.opt.path:append('./include')
vim.opt.path:append('./src')
vim.opt.path:append('/opt/homebrew/include')

-- Key mappings
vim.keymap.set('n', '<F5>', ':make<CR>', { desc = 'Build project' })
vim.keymap.set('n', '<F6>', ':make run<CR>', { desc = 'Build and run' })
vim.keymap.set('n', '<F7>', ':make clean<CR>', { desc = 'Clean build' })

-- Search for word under cursor
vim.keymap.set('n', '<leader>g', function()
    local word = vim.fn.expand('<cword>')
    vim.cmd('grep -r ' .. word .. ' src/ include/')
end, { desc = 'Grep word under cursor' })

-- Header/source switching
vim.keymap.set('n', '<leader>h', function()
    local file = vim.fn.expand('%:r') .. '.h'
    vim.cmd('e ' .. file)
end, { desc = 'Switch to header' })

vim.keymap.set('n', '<leader>c', function()
    local file = vim.fn.expand('%:r') .. '.cpp'
    vim.cmd('e ' .. file)
end, { desc = 'Switch to source' })

-- Visual settings
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.cursorline = true
vim.opt.showmatch = true

-- Search settings
vim.opt.hlsearch = true
vim.opt.incsearch = true
vim.opt.ignorecase = true
vim.opt.smartcase = true

-- Mouse support
vim.opt.mouse = 'a'

-- LSP setup (if you have nvim-lspconfig)
local function setup_lsp()
    local ok, lspconfig = pcall(require, 'lspconfig')
    if not ok then return end
    
    -- Setup clangd for C++
    lspconfig.clangd.setup({
        cmd = {
            'clangd',
            '--compile-commands-dir=.',
            '--header-insertion=iwyu',
            '--clang-tidy',
            '--background-index',
        },
        filetypes = { 'c', 'cpp', 'objc', 'objcpp' },
        root_dir = lspconfig.util.root_pattern('CMakeLists.txt', 'Makefile', '.git'),
    })
end

setup_lsp()

-- Autocommands for this project
vim.api.nvim_create_autocmd('BufRead', {
    pattern = { '*.h', '*.cpp' },
    callback = function()
        vim.opt_local.commentstring = '// %s'
    end,
})

print("Visual Novel Game project config loaded!")
vim.g.mapleader = ' '
vim.g.maplocalleader = ' '

vim.opt.backspace = '2'
vim.opt.showcmd = true
vim.opt.laststatus = 2
vim.opt.autowrite = true
vim.opt.cursorline = true
vim.opt.autoread = true

-- use spaces for tabs and whatnot
vim.opt.tabstop = 2
vim.opt.shiftwidth = 2
vim.opt.shiftround = true
vim.opt.expandtab = true

-- Habilitar números de línea
vim.opt.number = true

-- Habilitar números relativos
vim.opt.relativenumber = true


-- Keymaps for clipboard copy/paste
local keymap = vim.api.nvim_set_keymap
local opts = { noremap = true, silent = true }

-- Copy to clipboard in visual mode
keymap("v", "<C-c>", '"+y', opts)

-- Paste from clipboard in normal mode
keymap("n", "<C-p>", '"+p', opts)

-- Paste from clipboard in visual mode (replace selected text)
keymap("v", "<C-p>", '"+p', opts)

-- Copy to clipboard in normal mode (optional, if needed)
keymap("n", "<C-c>", '"+yy', opts)

-- Indentar hacia la derecha con Tab en modo visual
keymap('v', '<Tab>', '>gv', opts)

-- Indentar hacia la izquierda con Shift+Tab en modo visual
keymap('v', '<S-Tab>', '<gv', opts)


vim.keymap.set('n', '<leader>h', ':nohlsearch<CR>')

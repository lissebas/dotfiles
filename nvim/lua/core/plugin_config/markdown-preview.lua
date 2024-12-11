-- Set up markdown-preview.nvim

-- Limit the plugin to markdown files
vim.g.mkdp_filetypes = { "markdown" }

-- Auto-install dependencies (if npm is unavailable, you can remove this)
vim.fn["mkdp#util#install"]()

-- Optional: Customize behavior (example: auto start preview)
vim.g.mkdp_auto_start = 1
vim.g.mkdp_auto_close = 1
vim.g.mkdp_refresh_slow = 0
vim.g.mkdp_theme = 'dark'


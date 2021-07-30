syntax on

" {{{ Set Commands
set noerrorbells
set tabstop=4 softtabstop=4
set shiftwidth=4
set expandtab
set smartindent
set nu
set rnu
set nowrap
set smartcase
"set noswapfile"
set nobackup
set undodir=~/.config/.vim/undodir
set undofile
set incsearch
set encoding=utf-8
set foldmethod=marker
set noea
set hlsearch

set colorcolumn=150
highlight Colorcolumn ctermbg=0 guibg=lightgrey

" }}}

"{{{ Plugins"
call plug#begin('~/.config/.vim/plugged')

Plug 'morhetz/gruvbox'
"Plug 'tpope/vim-fugitive'"
Plug 'reewr/vim-monokai-phoenix'
Plug 'vim-utils/vim-man'
"Plug 'neoclide/coc.nvim' "Recommended auto complete
Plug 'preservim/nerdtree'
Plug 'ctrlpvim/ctrlp.vim'
Plug 'mbbill/undotree'
"Plug 'tomasr/molokai'
Plug 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}
"Plug 'fatih/vim-go',{'do':':GoUpdateBinaries'}"
"Plug 'sickill/vim-monokai'

call plug#end()
"}}}"

"{{{ Markdowm preview config
let g:mkdp_auto_close = 0
let g:mkdp_echo_preview_url = 1
let g:mkdp_port = '8080'
let g:mkdp_filetypes = ['markdown']

" a custom vim function name to open preview page
" this function will receive url as param
" default is empty
" let g:mkdp_browserfunc = ''  " TODO
"}}}"

colorscheme gruvbox
set background=dark

"let g:ctrlp_user_command = ['.git/', 'git --git-dir=%s/.git ls-files -oc --exclude-standard']
let g:ctrlp_use_caching = 0

let mapleader = " "

let g:netrw_browse_split = 2
let g:netrw_banner = 0
let g:netrw_winsize = 25
"let g:python_host_prog  = '/usr/bin/python'

"{{{ Key remaping 
nnoremap <leader>h :wincmd h<CR>
nnoremap <leader>j :wincmd j<CR>
nnoremap <leader>k :wincmd k<CR>
nnoremap <leader>l :wincmd l<CR>
nnoremap <leader>u :UndotreeShow<CR>
nnoremap <leader>up :UndotreeFocus<CR>
"nnoremap <leader>pv :wincmd v<bar> :Ex<bar> :vertical resize 30<bar> :wincmd j<CR> " Don't need this hack because i have nerd tree
nnoremap <silent><leader>n :NERDTreeToggle<CR>
nnoremap <silent><leader>f :NERDTreeFind<CR>
nnoremap <leader>wm :vertical resize 30<CR>
nnoremap <leader>wn :vertical resize 100<CR>
nnoremap <silent> <leader>. :vertical resize +5<CR>
nnoremap <silent> <leader>, :vertical resize -5<CR>
nnoremap <silent> <C-b> :nohlsearch<CR>
inoremap <C-v> <ESC>"+pa
nnoremap <C-v> "+p
vnoremap <C-c> "+y
vnoremap <C-x> "+d
"}}}

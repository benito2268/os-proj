" =============================
"   Plugin Manager: vim-plug
" =============================
call plug#begin('~/.vim/plugged')

" Syntax & language support
Plug 'vim-syntastic/syntastic'       " On-the-fly linting
Plug 'shirk/vim-gas'                 " GNU as (AT&T syntax) highlighting
Plug 'vim-scripts/c.vim'             " Better C support

" Navigation & autocomplete
Plug 'neoclide/coc.nvim', {'branch': 'release'} " Autocomplete / LSP
Plug 'preservim/tagbar'              " Code structure viewer
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'               " Fuzzy file search

" Quality of life
Plug 'tpope/vim-commentary'           " gcc to comment code
Plug 'itchyny/lightline.vim'          " Clean status bar
Plug 'jiangmiao/auto-pairs'           " Auto-close brackets

call plug#end()

" =============================
"   General Settings
" =============================
syntax on
filetype plugin indent on

set number             " Line numbers
set relativenumber     " Relative numbers for movement
set tabstop=4          " Tabs = 4 spaces
set shiftwidth=4       " Auto-indent width
set expandtab          " Use spaces instead of tabs
set smartindent        " Auto-indent for C
set colorcolumn=80     " Vertical guide
set background=dark
colorscheme desert     " Change if you prefer

" =============================
"   Syntastic Settings
" =============================
let g:syntastic_c_checkers = ['gcc']
let g:syntastic_asm_checkers = ['gas']  " GNU as
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1

" =============================
"   Tagbar Settings
" =============================
nmap <F8> :TagbarToggle<CR>

" =============================
"   FZF Shortcuts
" =============================
nnoremap <leader>f :Files<CR>
nnoremap <leader>g :GFiles<CR>
nnoremap <leader>r :Rg<CR>

" =============================
"   OS Dev Build Shortcuts
" =============================
" Compile & run kernel in QEMU
nnoremap <F9> :w<CR>:!make run<CR>

" Compile & run QEMU with GDB stub
nnoremap <F10> :w<CR>:!make debug<CR>

" Attach GDB in Vim terminal
nnoremap <F11> :w<CR>:terminal gdb build/kernel.elf<CR>

" =============================
"   Auto Commands
" =============================
" Auto run ctags after saving
autocmd BufWritePost *.c,*.S,*.h silent! !ctags -R .

" Quick compile for C files
autocmd FileType c,cpp nnoremap <buffer> <F5> :w<CR>:!gcc -m32 -c % -o %:r.o<CR>

" Quick assemble for GNU as files
autocmd FileType asm nnoremap <buffer> <F5> :w<CR>:!as --32 % -o %:r.o<CR>

" =============================
"   COC (Intellisense) Settings
" =============================
" Use clangd for C/C++
let g:coc_global_extensions = ['coc-clangd']

" Better tab completion
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ coc#expandableOrJumpable() ? "\<C-r>=coc#rpc#request('doKeymap', ['snippets-expand-jump',''])\<CR>" :
      \ CheckBackspace() ? "\<TAB>" :
      \ coc#refresh()

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1] =~ '\s'
endfunction

" =============================
"   Statusline
" =============================
let g:lightline = {
      \ 'colorscheme': 'wombat',
      \ }


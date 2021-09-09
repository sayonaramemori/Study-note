set nu
set noshowmode
set cursorline
set showcmd
set autoindent
set expandtab
set shiftwidth=4
set softtabstop=4
set tabstop=4
"""colorscheme
syntax on
set relativenumber
set wildmenu
filetype plugin indent on
set ignorecase
set list
set listchars=tab:>-,trail:-
set foldmethod=indent
""zo zc za zM zR

inoremap { {<cr>}<esc>kA<cr>

noremap <C-s> <Plug>MarkdownPreview
nnoremap <M-s> <Plug>MarkdownPreviewStop
nnoremap <C-p> <Plug>MarkdownPreviewToggle

nnoremap <C-h> <c-w><c-h>
nnoremap <c-l> <c-w><c-l>
nnoremap <c-k> <c-w><c-k>
nnoremap <c-j> <c-w><c-j>
nnoremap tn :tabnew<RETURN>
nnoremap <Right> :vertical resize +5<Return>
nnoremap <Left> :vertical resize -5<Return>
nnoremap <Up> :resize +5<Return>
nnoremap <Down> :resize -5<Return>

call plug#begin()
Plug 'preservim/tagbar'
Plug 'vim-airline/vim-airline'
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}
Plug 'connorholyday/vim-snazzy'
call plug#end()

let g:cpp_no_function_highlight = 1
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_posix_standard = 1
let g:cpp_experimental_simple_template_highlight = 1
let g:cpp_experimental_template_highlight = 1
let g:cpp_concepts_highlight = 1

let g:mkdp_auto_start = 0
let g:mkdp_auto_close = 1
let g:mkdp_refresh_slow = 0
let g:mkdp_command_for_global = 0
let g:mkdp_open_to_the_world = 0
let g:mkdp_open_ip = ''
let g:mkdp_browser = 'firefox'
let g:mkdp_echo_preview_url = 0
let g:mkdp_browserfunc = ''
let g:mkdp_markdown_css = ''
let g:mkdp_highlight_css = ''
let g:mkdp_port = ''
let g:mkdp_filetypes = ['markdown']

"""mapping caplocks into esc
au VimEnter * silent! !xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'
au VimLeave * silent! !xmodmap -e 'clear Lock' -e 'keycode 0x42 = Caps_Lock'

colorscheme snazzy

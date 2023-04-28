"отступы
set expandtab "включает замену табов на пробелы
set smarttab "при нажатии таба в начале строки добавляет количество пробелов равное shiftwidth
set tabstop=4 "количество пробелов в одном обычном табе
set softtabstop=4 "количество пробелов в табе при удалении
set shiftwidth=4
"set termguicolors "делает всё более серым


call plug#begin('~/.vim/bundle') "Начать искать плагины в этой директории
    "Plug 'rhysd/vim-clang-format', {'for' : ['c', 'cpp']}
    Plug 'jiangmiao/auto-pairs' "автозакрытие скобок
    Plug 'vim-python/python-syntax' "синтакс питона
    "semshi не работает в вим
    "Plug 'numirias/semshi', { 'do': ':UpdateRemotePlugins' }
    "Plug 'python-mode/python-mode' "цвет питона
    Plug 'vim-airline/vim-airline' "улучшенная строка состояния
    Plug 'ryanoasis/vim-devicons' "Иконочки
    Plug 'tomasiser/vim-code-dark' "цветовая схема
    Plug 'sonph/onehalf', { 'rtp': 'vim' }
    Plug 'scrooloose/nerdtree', { 'on': 'NERDTreeToggle' }
	Plug 'neoclide/coc.nvim', {'branch': 'release'}
	Plug 'ludovicchabant/vim-gutentags' "Для ситэгов
    Plug 'preservim/tagbar' "отображение дерева проекта покруче
    Plug 'puremourning/vimspector' "VIMSPECTOR
    Plug 'cdelledonne/vim-cmake' "make конфигурация
    Plug 'tpope/vim-fugitive' "среда git
    Plug 'sodapopcan/vim-twiggy' "ещё кучка фич к гиту
    Plug 'junegunn/gv.vim' "удобный просмотр дерева веток
    Plug 'junegunn/fzf.vim'
    Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
call plug#end()

"Дополнительно
set number "нумерация строк
set cmdheight=2 "Увеличение командной строки
set mouse=a "включение мыши
set foldcolumn=2 "отступ от левой части окна
set number relativenumber "нумерация строк относительно позиции курсора
filetype plugin indent on "Включает определение типа файла, загрузку соответствующих ему плагинов и файлов отступов
set termencoding=utf-8 "кодировка терминала
" возможные кодировки файлов и последовательность определения.
set encoding=utf-8 "Ставит кодировку UTF-8
set nocompatible "Отключает обратную совместимость с Vi
syntax on "Включает подсветку синтаксиса
colorscheme codedark "активация цветовой схемы
set guifont=:Hack\ Regular\ Nerd\ Font\ Complete:h16 "Это light версия
let &path.="~/VsCode/**,~/Arduino/libraries/**,/usr/include/**,/var/lib/flatpak/app/cc.arduino.arduinoide/x86_64/stable/275ee51aa035c21aabdf6a2d0328350b39c12289f4f4d102160bde47b01449ac/files/Arduino/**, /usr/include/qt/** /usr/lib/qt/**"

let g:airline_powerline_fonts = 1 "Включить поддержку Powerline шрифтов
let g:airline#extensions#keymap#enabled = 0 "Не показывать текущий маппинг
let g:airline_section_z = "\ue0a1:%l/%L Col:%c" "Кастомная графа положения курсора
let g:Powerline_symbols='unicode' "Поддержка unicode
let g:airline#extensions#xkblayout#enabled = 0 "
"Change warning symbol:
let airline#extensions#coc#warning_symbol = 'Warning:'
"Change error symbol:
let airline#extensions#coc#error_symbol = 'Error:'
"Change error format:
let airline#extensions#coc#stl_format_err = '%C(L%L)'
"Change warning format:
let airline#extensions#coc#stl_format_warn = '%C(L%L)'


set ignorecase
set smartcase

"set hlsearch "подсветка результатов поиска
set incsearch "показ первого шаблона поиска

"autocmd FileType cpp setl textwidth=80

" CTRL-X and SHIFT-Del are Cut
vnoremap <C-X> "+x
vnoremap <S-Del> "+x
" CTRL-C and CTRL-Insert are Copy
vnoremap <C-C> "+y

"PYTHON_MODE-------------------------------------------->
"let g:pymode_syntax_all = 1
let g:python_highlight_all = 1
"Cmake***********************************************************
let g:cmake_link_compile_commands = 1
nmap <leader>cg :CMakeGenerate<cr>
nmap <leader>cb :CMakeBuild<cr>
"Cmake_End*****************************************************

"VIMSPECTOR***********************************************
command! -nargs=+ Vfb call vimspector#AddFunctionBreakpoint(<f-args>)

nnoremap <localleader>gd :call vimspector#Launch()<cr>
nnoremap <localleader>gc :call vimspector#Continue()<cr>
nnoremap <localleader>gs :call vimspector#Stop()<cr>
nnoremap <localleader>gR :call vimspector#Restart()<cr>
nnoremap <localleader>gp :call vimspector#Pause()<cr>
nnoremap <localleader>gb :call vimspector#ToggleBreakpoint()<cr>
nnoremap <localleader>gB :call vimspector#ToggleConditionalBreakpoint()<cr>
nnoremap <localleader>ga :call vimspector#ClearBreakpoints()<cr>
nnoremap <localleader>gn :call vimspector#StepOver()<cr>
nnoremap <localleader>gi :call vimspector#StepInto()<cr>
nnoremap <localleader>go :call vimspector#StepOut()<cr>
nnoremap <localleader>gr :call vimspector#RunToCursor()<cr>
nnoremap <localleader>ge :call vimspector#Reset()<cr>

"End+VIMSPECTOR*******************************************

"Удавление лишних пробелов
highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s\+$/
au BufWinEnter * match ExtraWhitespace /\s\+$/
au InsertEnter * match ExtraWhitespace /\s\+\%#\@<!$/
au InsertLeave * match ExtraWhitespace /\s\+$/
au BufWinLeave * call clearmatches()

"Сочетание для алтоматического удаления
nnoremap <silent> <leader>rs :let _s=@/ <Bar> :%s/\s\+$//e <Bar> :let @/=_s <Bar> :nohl <Bar> :unlet _s <CR>

set tags=./tags;
let g:gutentags_ctags_exclude_wildignore = 1
let g:gutentags_ctags_exclude = [
  \'node_modules', '_build', 'build', 'CMakeFiles', '.mypy_cache', 'venv',
  \'*.md', '*.tex', '*.css', '*.html', '*.json', '*.xml', '*.xmls', '*.ui']


nmap <F8> :TagbarToggle<CR>
let g:tagbar_autofocus = 1

let g:tagbar_scopestrs = {
    \    'class': "\uf0e8",
    \    'const': "\uf8ff",
    \    'constant': "\uf8ff",
    \    'enum': "\uf702",
    \    'field': "\uf30b",
    \    'func': "\uf794",
    \    'function': "\uf794",
    \    'getter': "\ufab6",
    \    'implementation': "\uf776",
    \    'interface': "\uf7fe",
    \    'map': "\ufb44",
    \    'member': "\uf02b",
    \    'method': "\uf6a6",
    \    'setter': "\uf7a9",
    \    'variable': "\uf71b",
    \ }

nnoremap <leader>n :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTreeToggle<CR>
nnoremap <C-f> :NERDTreeFind<CR>

"CocNVIM---------------------------------------------------->
" Some servers have issues with backup files, see #649.
set nobackup
set nowritebackup

" Having longer updatetime (default is 4000 ms = 4 s) leads to noticeable
" delays and poor user experience.
set updatetime=300

" Always show the signcolumn, otherwise it would shift the text each time
" diagnostics appear/become resolved.
set signcolumn=yes

" Use tab for trigger completion with characters ahead and navigate.
" NOTE: There's always complete item selected by default, you may want to enable
" no select by `"suggest.noselect": true` in your configuration file.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

" Make <CR> to accept selected completion item or notify coc.nvim to format
" <C-g>u breaks current undo, please make your own choice.
inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

" Use <c-space> to trigger completion.
if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif

" Use `[g` and `]g` to navigate diagnostics
" Use `:CocDiagnostics` to get all diagnostics of current buffer in location list.
nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)

" GoTo code navigation.
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gs :call CocAction('jumpDefinition', 'split')<CR>
nmap <silent> gn :call CocAction('jumpDefinition', 'tabe')<CR>
nmap <silent> gv :call CocAction('jumpDefinition', 'vsplit')<CR>
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)

" Use K to show documentation in preview window.
nnoremap <silent> K :call ShowDocumentation()<CR>

function! ShowDocumentation()
  if CocAction('hasProvider', 'hover')
    call CocActionAsync('doHover')
  else
    call feedkeys('K', 'in')
  endif
endfunction

" Highlight the symbol and its references when holding the cursor.
autocmd CursorHold * silent call CocActionAsync('highlight')

" Symbol renaming.
nmap <leader>rn <Plug>(coc-rename)

" Formatting selected code.
xmap <leader>f  <Plug>(coc-format-selected)
nmap <leader>f  <Plug>(coc-format-selected)

augroup mygroup
  autocmd!
  " Setup formatexpr specified filetype(s).
  autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
  " Update signature help on jump placeholder.
  autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
augroup end

" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)

" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)

" Run the Code Lens action on the current line.
nmap <leader>cl  <Plug>(coc-codelens-action)

" Map function and class text objects
" NOTE: Requires 'textDocument.documentSymbol' support from the language server.
xmap if <Plug>(coc-funcobj-i)
omap if <Plug>(coc-funcobj-i)
xmap af <Plug>(coc-funcobj-a)
omap af <Plug>(coc-funcobj-a)
xmap ic <Plug>(coc-classobj-i)
omap ic <Plug>(coc-classobj-i)
xmap ac <Plug>(coc-classobj-a)
omap ac <Plug>(coc-classobj-a)

" Remap <C-f> and <C-b> for scroll float windows/popups.
if has('nvim-0.4.0') || has('patch-8.2.0750')
  nnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  nnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
  inoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<Right>"
  inoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<Left>"
  vnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  vnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
endif

" Use CTRL-S for selections ranges.
" Requires 'textDocument/selectionRange' support of language server.
nmap <silent> <C-s> <Plug>(coc-range-select)
xmap <silent> <C-s> <Plug>(coc-range-select)

" Add `:Format` command to format current buffer.
command! -nargs=0 Format :call CocActionAsync('format')

" Add `:Fold` command to fold current buffer.
command! -nargs=? Fold :call     CocAction('fold', <f-args>)

" Add `:OR` command for organize imports of the current buffer.
command! -nargs=0 OR   :call     CocActionAsync('runCommand', 'editor.action.organizeImport')

" Add (Neo)Vim's native statusline support.
" NOTE: Please see `:h coc-status` for integrations with external plugins that
" provide custom statusline: lightline.vim, vim-airline.
set statusline^=%{coc#status()}%{get(b:,'coc_current_function','')}

" Mappings for CoCList
" Show all diagnostics.
nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
" Manage extensions.
nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
" Show commands.
nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
" Find symbol of current document.
nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
" Search workspace symbols.
nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
" Do default action for next item.
nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
" Do default action for previous item.
nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
" Resume latest coc list.
nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>
"CocNVIM----------------END--------------------------------->


autocmd CursorHold * silent call CocActionAsync('highlight')
let g:coc_default_semantic_highlight_groups = 1

autocmd FileType python set foldmethod=indent
autocmd FileType python set foldnestmax=1

"let python_highlight_all = 1
autocmd FileType python let b:coc_root_patterns =
				\ [".vim/", ".venv/", "src/"]

" autocmd FileType yml let b:coc_root_patterns =
" 				\ [".vim/"]
"
autocmd FileType yaml let b:coc_root_patterns =
				\ [".vim/", "README.md"]

autocmd FileType go let b:coc_root_patterns =
				\ ["go.mod", ".vim/", ".git/"]

autocmd FileType c,cpp,objc,h let b:coc_root_patterns =
				\ [".vim/", ".git/"]

"autocmd FileType go hi link CocSemNamespace TSNamespace
"autocmd FileType go hi link CocSemKeyword TSKeyword
if &t_Co >= 256
    let g:codedark_term256=1
elseif !exists("g:codedark_term256")
    let g:codedark_term256=0
endif

fun! <sid>hi(group, fg, bg, attr, sp)
  if !empty(a:fg)
    exec "hi " . a:group . " guifg=" . a:fg.gui . " ctermfg=" . (g:codedark_term256 ? a:fg.cterm256 : a:fg.cterm)
  endif
  if !empty(a:bg)
    exec "hi " . a:group . " guibg=" . a:bg.gui . " ctermbg=" . (g:codedark_term256 ? a:bg.cterm256 : a:bg.cterm)
  endif
  if a:attr != ""
    exec "hi " . a:group . " gui=" . a:attr . " cterm=" . a:attr
  endif
  if !empty(a:sp)
    exec "hi " . a:group . " guisp=" . a:sp.gui
  endif
endfun

" Terminal colors (base16):
let s:cterm00 = "00"
let s:cterm03 = "08"
let s:cterm05 = "07"
let s:cterm07 = "15"
let s:cterm08 = "01"
let s:cterm0A = "03"
let s:cterm0B = "02"
let s:cterm0C = "06"
let s:cterm0D = "04"
let s:cterm0E = "05"
if exists('base16colorspace') && base16colorspace == "256"
  let s:cterm01 = "18"
  let s:cterm02 = "19"
  let s:cterm04 = "20"
  let s:cterm06 = "21"
  let s:cterm09 = "16"
  let s:cterm0F = "17"
else
  let s:cterm01 = "00"
  let s:cterm02 = "08"
  let s:cterm04 = "07"
  let s:cterm06 = "07"
  let s:cterm09 = "06"
  let s:cterm0F = "03"
endif

"autocmd FileType go hi link CocSemType TSType
let s:cdBlueGreen = {'gui': '#4EC9B0', 'cterm': s:cterm0F, 'cterm256': '43'}
let s:cdGreen = {'gui': '#ff33ff', 'cterm': s:cterm0B, 'cterm256': '77'}
call <sid>hi('Include', s:cdBlueGreen, {}, 'none', {})

if g:codedark_italics | call <sid>hi('Comment', s:cdGreen, {}, 'italic', {}) | else | call <sid>hi('Comment', s:cdGreen, {}, 'none', {}) | endif

call <sid>hi('Comment', s:cdGreen, {}, 'none', {})
let g:LanguageClient_serverCommands = {
 \ 'cpp': ['clangd', '-background-index',],
 \ }

"Форматирование кода
"let g:clang_format#style_options = {
"    \ "Standard" : "C++17"
"}
" map to <Leader>cf in C++ code
"autocmd FileType c,cpp,objc nnoremap <buffer><Leader> :<C-u>ClangFormat<CR>
"autocmd FileType c,cpp,objc vnoremap <buffer><Leader><C-t> :ClangFormat<CR>


"Сниппеты тип для добавления базового кода
"Clang-completer
" Включить дополнительные подсказки (аргументы функций, шаблонов и т.д.)
let g:clang_snippets=1
" Использоать ultisnips для дополнительных подскахок (чтобы подсказки шаблонов
" автогенерации были в выпадающих меню)
let g:clang_snippets_engine = 'ultisnips'
" Периодически проверять проект на ошибки
let g:clang_periodic_quickfix=1
" Подсвечивать ошибки
let g:clang_hl_errors=1

"ARDUINO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
au BufRead,BufNewFile *.ino,*.pde set filetype=c++

autocmd bufnewfile *.cpp so /home/lenow/.vim/name_templ/cpp_header.txt
autocmd bufnewfile *.cpp exe "1," . 10 . "g/Filename:.*/s//Filename: " .expand("%")
autocmd bufnewfile *.cpp exe "1," . 10 . "g/Creation Date:.*/s//Creation Date: " .strftime("%d-%m-%Y")
autocmd Bufwritepre,filewritepre *.cpp execute "normal ma"
autocmd Bufwritepre,filewritepre *.cpp exe "1," . 10 . "g/Last Modified:.*/s/Last Modified:.*/Last Modified : " .strftime("%c")
autocmd bufwritepost,filewritepost *.cpp execute "normal `a"


highlight CocHighlightText ctermbg=237 guibg=#3D3D40

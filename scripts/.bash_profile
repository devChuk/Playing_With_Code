

#Just some shorter and faster commands
alias s='sublime-text'
c() { cd "$@" && ls --color=auto; }
alias spull='git smart-pull'
alias gstatus='git status'
alias gdiff='git diff'

# Load the default .profile
[[ -s "$HOME/.profile" ]] && source "$HOME/.profile" 

# Load RVM into a shell session *as a function*
[[ -s "$HOME/.rvm/scripts/rvm" ]] && source "$HOME/.rvm/scripts/rvm" 

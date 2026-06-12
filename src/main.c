#include <termios.h>
#include <unistd.h>
#include "../include/input.h"
#include "../include/editor.h"

int main(){
    Editor* e = edit_new("/home/miskyr/projects/c/vim/input.txt");
    edit_init_term(e);
    while(e->running){
        edit_render(e);
        Key key = inp_read_key();
        edit_handle_key(e, key);
    }
    edit_free(e);
}
#include "../include/editor.h"
#include "../include/input.h"
#include <stdbool.h>
#include <stdlib.h>

Editor* edit_new(const char* file_name){
	Editor* e = malloc(sizeof(Editor));
	e->running = true;
	term_get_size(&e->H, &e->W);
    e->W -= 2;
    e->H -= 2;
	e->buf = buf_create(e->W, e->H);
	e->curs = curs_new();
	e->txt = text_new();
	text_load_from_file(e->txt, file_name);
	text_add_line(e->txt, "HELLO");
	e->mode = NORMAL;
	return e;
}

void edit_init_term(Editor* e){
	term_enable_raw();
	term_clear();
	term_cursor_to_start();
}

void edit_handle_key(Editor* e, Key key){
	if(e->mode == NORMAL){
		if(key.ch == 'q'){
	        e->running = false;
	    } else if(key.ch == 'i'){
	        e->mode = INSERT;
	    } else if(key.code == KEY_RIGHT){
        	curs_move(e->curs, e->txt, e->buf, RIGHT);
	    } else if(key.code == KEY_LEFT){
	        curs_move(e->curs, e->txt, e->buf, LEFT);
	    } else if(key.code == KEY_UP){
	        curs_move(e->curs, e->txt, e->buf, UP);
	    } else if(key.code == KEY_DOWN){
	        curs_move(e->curs, e->txt, e->buf, DOWN);
	    }
	} else if(e->mode == INSERT){
		if(key.code == KEY_ESC){
			e->mode = NORMAL;
		}if(key.code == KEY_RIGHT){
	        curs_move(e->curs, e->txt, e->buf, RIGHT);
	    } else if(key.code == KEY_LEFT){
	        curs_move(e->curs, e->txt, e->buf, LEFT);
	    } else if(key.code == KEY_UP){
	        curs_move(e->curs, e->txt, e->buf, UP);
	    } else if(key.code == KEY_DOWN){
	        curs_move(e->curs, e->txt, e->buf, DOWN);
	    }else if (key.code == KEY_UNKNOWN && key.ch >= 32 && key.ch < 127) {
	        curs_add_char(e->curs, e->txt, e->buf, key.ch);
	    }else if (key.code == KEY_BACKSPACE) {
	        curs_backspace(e->curs, e->txt, e->buf);
	    } else if(key.code == KEY_ENTER){
	        curs_enter(e->curs, e->txt, e->buf);
	    } else if(key.code == KEY_TAB){
	        curs_add_char(e->curs, e->txt, e->buf, '\t');
	    }
	} else if(e->mode == VILUAL){
		if(key.code == KEY_RIGHT){
	        curs_move(e->curs, e->txt, e->buf, RIGHT);
	    } else if(key.code == KEY_LEFT){
	        curs_move(e->curs, e->txt, e->buf, LEFT);
	    } else if(key.code == KEY_UP){
	        curs_move(e->curs, e->txt, e->buf, UP);
	    } else if(key.code == KEY_DOWN){
	        curs_move(e->curs, e->txt, e->buf, DOWN);
	    }
	} else if(e->mode == COMMAND){

	}
}

void edit_free(Editor *e){
	buf_free(e->buf);
	curs_free(e->curs);
	text_free(e->txt);
	free(e);
}

void edit_render(Editor *e){
	term_cursor_to_start();
    buf_fill(e->buf, ' ');
    text_render(e->txt, e->buf, e->curs);
    curs_render(e->curs, e->buf);
    buf_print(e->buf);
}
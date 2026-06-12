#include "../include/buffer.h"
#include "../include/terminal.h"
#include "../include/input.h"
#include "../include/vector.h"
#include "../include/text.h"
#include "../include/cursor.h"
#include "../include/log.h"
#include "../include/mode.h"
#include <stdbool.h>
#include <termios.h>

typedef struct{
	Mode mode;
	int W, H;
	bool running;
	Rect text_area;
	Buffer* buf;
	Text* txt;
	Cursor* curs;
} Editor;

Editor* edit_new(const char* file_name);
void edit_free(Editor* e);
void edit_init_term(Editor* e);
void edit_handle_key(Editor* e, Key key);
void edit_render(Editor* e);
void edit_render_mode(Editor* e);
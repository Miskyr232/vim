#include "../include/terminal.h"

void term_enable_raw(){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
    t.c_iflag &= ~(IXON | ICRNL);
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void term_clear(){
    printf("\033[2J");
}

void term_cursor_to_start(){
    printf("\033[1;1H");
}

void term_enable_invert(){
    printf("\033[7m");
}

void term_disable_invert(){
    printf("\033[m");
}

void term_get_size(int *rows, int *cols) {
    struct winsize w;
    // STDOUT_FILENO указывает на стандартный вывод (терминал)
    // TIOCGWINSZ — это команда "Get Window Size"
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    *rows = w.ws_row;
    *cols = w.ws_col;
}

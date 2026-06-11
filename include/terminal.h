#pragma once

#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <unistd.h>

void term_get_size(int *rows, int *cols);
void term_enable_raw();
void term_clear();
void term_cursor_to_start();
void term_enable_invert();
void term_disable_invert();
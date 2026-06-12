#pragma once

typedef enum{
	INSERT, NORMAL, VILUAL, COMMAND,
} Mode;

const char* mode_to_string(Mode mode);
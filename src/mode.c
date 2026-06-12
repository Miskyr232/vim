#include "../include/mode.h"

const char* mode_to_string(Mode mode){
	switch (mode) {
		case COMMAND: return "COMMAND";
		case INSERT: return "INSERT";	
		case VILUAL: return "VILUAL";	
		case NORMAL: return "NORMAL";	
	}
}
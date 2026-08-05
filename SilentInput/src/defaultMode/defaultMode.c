#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/defaultMode/defaultMode.h"

static struct termios *terminal_ptr = NULL;

void restoreMode (void) {

	if (terminal_ptr != NULL) {
		tcsetattr(STDIN_FILENO, TCSANOW, terminal_ptr);
	}

}

void setDefaultOptionsTerminal (struct termios * terminal) {

	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

}


void setDefaultMode (struct termios *terminal) {
	terminal_ptr = terminal;
	atexit(restoreMode);
}
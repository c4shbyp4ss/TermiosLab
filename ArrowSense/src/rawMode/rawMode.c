#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/rawMode/rawMode.h"

static struct termios terminalOriginal;

void restauraTerminal (void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void ativaModoRaw (struct termios *terminal) {
	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	terminalOriginal = *terminal;
	atexit(restauraTerminal);

	struct termios rawTerminal = *terminal;
	rawTerminal.c_lflag &= ~(ECHO | ICANON | IEXTEN);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTerminal);
}

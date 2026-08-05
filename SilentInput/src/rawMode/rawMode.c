#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/defaultMode/defaultMode.h"
#include "../../include/rawMode/rawMode.h"

void rawMode (struct termios * terminal) {
	struct termios rawTerminal;

	setDefaultOptionsTerminal(terminal);

	rawTerminal = *terminal;

	// desligando flags

	rawTerminal.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTerminal);

}
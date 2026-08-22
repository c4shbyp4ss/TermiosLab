#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/timeoutMode/timeoutMode.h"

static struct termios terminalOriginal;

void restauraTerminal (void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void ativaModoComTimeout (struct termios *terminal) {
	/*
		VMIN=0, VTIME=10: read() espera até 1 segundo (VTIME em décimos de segundo)
		por 1 byte; se nada chegar nesse intervalo, retorna 0 (tempo esgotado)
	*/
	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	terminalOriginal = *terminal;
	atexit(restauraTerminal);

	struct termios modo = *terminal;
	modo.c_lflag &= ~(ECHO | ICANON);
	modo.c_cc[VMIN] = 0;
	modo.c_cc[VTIME] = 10;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo);
}

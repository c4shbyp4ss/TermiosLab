#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/nonBlockingMode/nonBlockingMode.h"

static struct termios terminalOriginal;

void restauraTerminal (void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void ativaModoNaoBloqueante (struct termios *terminal) {
	/*
		VMIN=0, VTIME=0: read() nunca bloqueia — retorna na hora, com ou sem
		tecla disponível no buffer
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
	modo.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo);
}

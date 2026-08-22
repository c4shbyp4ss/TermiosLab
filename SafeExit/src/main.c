#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../include/terminalMode/terminalMode.h"

struct termios terminal;

int main () {
	// declarações

	char c;

	// execução

	ativaModoSeguro(&terminal);

	printf("Modo raw ativo.\n");

	ativaModoRaw(&terminal);

	while (1) {
		read(STDIN_FILENO, &c, 1);

		if (c == 'q') {
			exit(0);
		}
	}

	return 0;
}

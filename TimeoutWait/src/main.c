#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../include/timeoutMode/timeoutMode.h"

struct termios terminal;

int main () {
	ativaModoComTimeout(&terminal);

	char c;

	while (1) {
		printf("Aguardando tecla (1s)...\n");

		ssize_t lidos = read(STDIN_FILENO, &c, 1);

		if (lidos == 0) {
			printf("tempo esgotado\n");
			continue;
		}

		if (c == 'q') {
			break;
		}

		printf("Tecla recebida: '%c'\n", c);
	}

	return 0;
}

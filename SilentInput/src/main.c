#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../include/defaultMode/defaultMode.h"
#include "../include/rawMode/rawMode.h"

struct termios terminal;

int main () {
	setDefaultMode(&terminal);

	// declarações
	char character;
	// execuções

	printf("Iniciando SilentInput...\n\n");

	// modo raw

	rawMode(&terminal);

	while (1) {

		printf("Digite uma tecla: "); read(STDIN_FILENO, &character, 1);
		putchar('\n');
		printf("Tecla digitada, código: %d\n", character);

		if (character == 'q') {
			printf("Fim de SilentInput!\n\n");
			exit(1);
		}
	}


	return 0;
}
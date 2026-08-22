#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "../include/rawMode/rawMode.h"

struct termios terminal;

int main () {
	ativaModoRaw(&terminal);

	printf("Eco desligado\n");
	printf("Pressione 'e' para alternar o eco, 'q' para sair.\n");

	char c;

	while (1) {
		read(STDIN_FILENO, &c, 1);

		if (c == 'q') {
			break;
		}

		if (c == 'e') {
			alternaEco();
		}
	}

	return 0;
}

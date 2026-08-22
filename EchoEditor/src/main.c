#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../include/rawMode/rawMode.h"

#define TAM_MAX 128

struct termios terminal;

int main () {
	ativaModoRaw(&terminal);

	char buffer[TAM_MAX];
	int tamanho = 0;
	char c;

	printf("Digite algo: ");
	fflush(stdout);

	while (1) {
		read(STDIN_FILENO, &c, 1);

		if (c == '\r' || c == '\n') {
			break;
		}

		if (c == 127 || c == 8) { // Backspace: DEL (127) na maioria dos terminais, BS (8) em alguns
			if (tamanho > 0) {
				tamanho--;
				printf("\b \b"); // volta um espaço, apaga com espaço, volta de novo
				fflush(stdout);
			}
			continue;
		}

		if (tamanho < TAM_MAX - 1) {
			buffer[tamanho++] = c;
			putchar(c); // eco manual, já que o modo raw desliga o eco automático
			fflush(stdout);
		}
	}

	buffer[tamanho] = '\0';
	printf("\n\nVocê digitou: %s\n", buffer);

	return 0;
}

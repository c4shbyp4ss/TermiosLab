#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../include/nonBlockingMode/nonBlockingMode.h"

struct termios terminal;

int main () {
	ativaModoNaoBloqueante(&terminal);

	int passo = 0;
	char c;

	while (1) {
		ssize_t lidos = read(STDIN_FILENO, &c, 1);

		if (lidos == 1) {
			if (c == ' ') {
				passo += 10;
				printf("Tecla capturada: (espaco)   (passo %d)\n", passo);
			} else if (c == 'q') {
				break;
			}
		} else {
			printf("Simulando passo %d... (nenhuma tecla)\n", passo);
		}

		passo++;
		usleep(100000); // ~100ms
	}

	return 0;
}

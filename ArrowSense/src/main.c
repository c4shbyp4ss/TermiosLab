#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "../include/rawMode/rawMode.h"
#include "../include/arrowKeys/arrowKeys.h"

struct termios terminal;

int main () {
	ativaModoRaw(&terminal);

	printf("Setas para navegar, 'q' para sair.\n");

	while (1) {
		char direcao = leSeta();

		switch (direcao) {
			case SETA_CIMA:     printf("Seta para cima\n"); break;
			case SETA_BAIXO:    printf("Seta para baixo\n"); break;
			case SETA_DIREITA:  printf("Seta para direita\n"); break;
			case SETA_ESQUERDA: printf("Seta para esquerda\n"); break;
			case 'q': exit(0);
			default: break;
		}
	}

	return 0;
}

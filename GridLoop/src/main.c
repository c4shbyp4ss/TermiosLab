#include <stdio.h>
#include <unistd.h>
#include "../include/terminal/terminal.h"

int main () {
	terminal_ativar_raw();

	printf("Loop iniciado. Setas para navegar, 'q' para sair.\n");

	int passo = 0;
	char tecla;

	while (1) {
		int resultado = terminal_ler_entrada(&tecla);

		switch (resultado) {
			case SETA_CIMA:     printf("Seta para cima\n"); break;
			case SETA_BAIXO:    printf("Seta para baixo\n"); break;
			case SETA_DIREITA:  printf("Seta para direita\n"); break;
			case SETA_ESQUERDA: printf("Seta para esquerda\n"); break;
			case TECLA_NORMAL:
				if (tecla == 'q') {
					printf("Encerrando, terminal restaurado.\n");
					return 0;
				}
				break;
			default:
				break; // SETA_NENHUMA: nada chegou nesta rodada do loop
		}

		printf("Passo %d simulado.\n", passo);
		passo++;
		usleep(100000); // ~100ms, mesmo ritmo do PulseCounter
	}

	return 0;
}

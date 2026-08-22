#include <stdio.h>
#include "../include/terminal/terminal.h"

int main () {
	terminal_ativar_raw();

	printf("Módulo TermCore ativo. Pressione 'q' para sair.\n");

	while (1) {
		char c = terminal_ler_tecla();

		if (c == 'q') {
			break;
		}

		printf("Tecla lida via terminal_ler_tecla: %d\n", c);
	}

	return 0;
}

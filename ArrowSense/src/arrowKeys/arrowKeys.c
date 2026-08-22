#include <unistd.h>
#include "../../include/arrowKeys/arrowKeys.h"

char leSeta (void) {
	/*
		Lê um byte do teclado. Se for ESC, tenta reconhecer a sequência de escape
		de uma seta (ESC + '[' + 'A'/'B'/'C'/'D'). Retorna a constante SETA_* quando
		reconhece a sequência, ou o próprio caractere lido caso contrário.
	*/
	char c;

	if (read(STDIN_FILENO, &c, 1) != 1) {
		return SETA_NENHUMA;
	}

	if (c != '\x1b') {
		return c;
	}

	char seq[2];

	if (read(STDIN_FILENO, &seq[0], 1) != 1) return c;
	if (read(STDIN_FILENO, &seq[1], 1) != 1) return c;

	if (seq[0] == '[') {
		switch (seq[1]) {
			case 'A': return SETA_CIMA;
			case 'B': return SETA_BAIXO;
			case 'C': return SETA_DIREITA;
			case 'D': return SETA_ESQUERDA;
		}
	}

	return SETA_NENHUMA;
}

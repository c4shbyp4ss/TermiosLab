#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../../include/terminal/terminal.h"

static struct termios terminalOriginal;

void terminal_restaurar (void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void terminal_ativar_raw (void) {
	/*
		Ativa o modo raw não-bloqueante (VMIN=0, VTIME=0), com restauração garantida
		via atexit() — reúne SafeExit + PulseCounter num único módulo
	*/
	if (tcgetattr(STDIN_FILENO, &terminalOriginal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	atexit(terminal_restaurar);

	struct termios modo = terminalOriginal;
	modo.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	modo.c_cc[VMIN] = 0;
	modo.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo);
}

int terminal_ler_entrada (char *tecla) {
	/*
		Lê a entrada disponível sem bloquear (herdado do modo não-bloqueante).
		Se reconhecer uma sequência de seta (ESC + '[' + 'A'/'B'/'C'/'D'), devolve
		a constante SETA_*. Se ler um caractere normal, preenche *tecla e devolve
		TECLA_NORMAL. Se não havia nada para ler, devolve SETA_NENHUMA.
	*/
	char c;

	if (read(STDIN_FILENO, &c, 1) != 1) {
		return SETA_NENHUMA;
	}

	if (c == '\x1b') {
		char seq[2];

		if (read(STDIN_FILENO, &seq[0], 1) != 1) return SETA_NENHUMA;
		if (read(STDIN_FILENO, &seq[1], 1) != 1) return SETA_NENHUMA;

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

	*tecla = c;
	return TECLA_NORMAL;
}

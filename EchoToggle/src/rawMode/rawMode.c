#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/rawMode/rawMode.h"

static struct termios terminalOriginal;
static struct termios terminalAtual;
static int ecoLigado = 0;

void restauraTerminal (void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void ativaModoRaw (struct termios *terminal) {
	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	terminalOriginal = *terminal;
	atexit(restauraTerminal);

	terminalAtual = *terminal;
	terminalAtual.c_lflag &= ~(ICANON | IEXTEN | ECHO); // começa com eco desligado

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalAtual);
}

void alternaEco (void) {
	/*
		Liga ou desliga a flag ECHO em tempo de execução, chamando tcsetattr()
		de novo no mesmo processo, sem nunca sair do modo raw
	*/
	ecoLigado = !ecoLigado;

	if (ecoLigado) {
		terminalAtual.c_lflag |= ECHO;
		printf("Eco ligado\n");
	} else {
		terminalAtual.c_lflag &= ~ECHO;
		printf("Eco desligado\n");
	}

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalAtual);
}

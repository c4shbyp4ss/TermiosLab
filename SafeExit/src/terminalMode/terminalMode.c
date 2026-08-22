#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../../include/terminalMode/terminalMode.h"

// guarda o estado original do terminal para restauração garantida
static struct termios terminalOriginal;

void restauraTerminal (void) {
	/*
		Restaura o terminal ao estado original, não importa como o programa termine
		(saída normal, exit() forçado ou sinal capturado)
	*/
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
	printf("\nTerminal restaurado antes de encerrar.\n");
}

void tratadorSinal (int sinal) {
	/*
		Tratador de SIGINT (Ctrl+C): não sai "na marra", deixa o exit() disparar
		o atexit() e restaurar o terminal normalmente
	*/
	(void) sinal;
	putchar('\n');
	exit(0);
}

void ativaModoSeguro (struct termios *terminal) {
	/*
		Salva o estado original do terminal, registra a restauração garantida (atexit)
		e passa a capturar Ctrl+C (SIGINT) para sair de forma limpa
	*/
	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	terminalOriginal = *terminal;

	atexit(restauraTerminal);
	signal(SIGINT, tratadorSinal);
}

void ativaModoRaw (struct termios *terminal) {
	/*
		Ativa o modo raw a partir do estado já salvo em ativaModoSeguro()
	*/
	struct termios rawTerminal = *terminal;

	rawTerminal.c_lflag &= ~(ECHO | ICANON | IEXTEN);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTerminal);
}

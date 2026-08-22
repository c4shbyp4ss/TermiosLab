#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../../include/terminal/terminal.h"

// estado do terminal fica encapsulado dentro do módulo — main.c não precisa
// conhecer struct termios nenhuma

static struct termios terminalOriginal;

void terminal_restaurar (void) {
	/*
		Restaura o terminal ao estado salvo antes de ativar o modo raw
	*/
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalOriginal);
}

void terminal_ativar_raw (void) {
	/*
		Salva o estado atual do terminal, registra a restauração automática (atexit)
		e ativa o modo raw (sem eco, sem modo canônico)
	*/
	if (tcgetattr(STDIN_FILENO, &terminalOriginal) == -1) {
		perror("tcgetattr");
		exit(1);
	}

	atexit(terminal_restaurar);

	struct termios rawTerminal = terminalOriginal;
	rawTerminal.c_lflag &= ~(ECHO | ICANON | IEXTEN);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTerminal);
}

char terminal_ler_tecla (void) {
	/*
		Lê uma tecla do terminal em modo raw (bloqueante, uma tecla por chamada)
	*/
	char c = 0;
	read(STDIN_FILENO, &c, 1);
	return c;
}

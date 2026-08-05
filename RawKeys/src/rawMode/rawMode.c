#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../../include/rawMode/rawMode.h"

// inicializando funções
void ativa_modoRaw(struct termios *terminal) {
	// declarando um struct temporario
	struct termios rawTermial;
	// setando as flags do estado atual do terminal

	if (tcgetattr(STDIN_FILENO, terminal) == -1) {
		perror("tcgetattr");
		exit(1);
		// exução do restaurador do terminal
	}
	// copiando atributos e valores da struct terminal para a struct temporaria
	rawTermial = *terminal;

	// desligando as flgs do modo raw

	// desativando as flags locais

	rawTermial.c_lflag &= ~(ECHO | ICANON | IEXTEN);

	// ativando o modo raw

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawTermial);
}
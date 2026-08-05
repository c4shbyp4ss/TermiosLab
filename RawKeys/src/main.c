#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "../include/rawMode/rawMode.h"

// struct terminal

struct termios terminal;



// funções e procedimentos

// procedimentos
void restaura_terminal ();
// funções

int main () {
	atexit(restaura_terminal); // fazendo a função ser executada ao final do programa, sempre

	// declaração

	char c;
	// execução

	printf("Iniciando exibidor de teclas...\n [ Bem-Vindo ao RawKeys ]\n\n");

	// iniciando o modo raw

	ativa_modoRaw(&terminal);

	// iniciando o contador de teclas
	while (1) {

		read(STDIN_FILENO, &c, 1);
		printf("Cod.Tecla: %d\n", c);
		if (c == 'q') {
			putchar('\n');
			printf("Obrigado por utilizar o RawKeys!!\n\n");
			exit(0);
		} 
	}
	
	return 0;
}




// inicialização de funções e procedimentos


// procedimentos


void restaura_terminal () {

	/*
		Função para restaurar a forma padrão do terminal (executada ao final do programa)
	*/

	// setando estado atual do terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);

}
// funções

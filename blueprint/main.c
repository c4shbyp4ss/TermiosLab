// #include <termios.h> // trabalhando com manipulação bit a bit do terminal, alterando seu estado 'canonical' para 'raw (não canonico)'

// // alteramos caracteristicas a partir de um unico struct

// struct termios {
// 	tcflag_t c_iflag; // flags de entrada (input)
// 	tcflag_t c_oflag; // flgas de saida (output)
// 	tcflag_t c_cflag; // flags de controle (control)
// 	tcflag_t c_lflag; // flags locais (local)
// 	cc_t     c_cc[NCCS]; // caracteres de controle especiais 
// }


// // utilizamos duas funções que usamos em par (uma seguida da outra)

// int tcgetattr (int fd, struct termios * termios_p); // ler o estado atual do terminal para dentro do struct padrão
// int tcgsetattr (int fd, int optional_actions, const struct termios * termios_p); // aplica a strcut já modificado de volta ao terminal

// /*

// 	argumentos das funções

// 	parametro int fd => descritivo do arquivo de terminal (STDIN_FILENO) -> pois mudamos como a entrada padrão se comporta
// 	parametro int optional_actions => quando aplicamos a mudança? Podemos usar as seguintes opções:

// 		* TCSANOW -> Aplica a mudança imediatamente
// 		* TCSADRAIN -> Espera todo o output pendente ser escrito antes de ser aplicado
// 		* TCSAFLUSH -> Espera todo o output a ser escrito porém descarta todo input ainda não lido
// */ 


// realizando um exemplo básico: Pegando as configurações atuais do Terminal

// #include <stdio.h>
// #include <termios.h>
// #include <unistd.h>


// int main () {

// 	struct termios opt_terminal; // declarando o struct padrão do termios com suas flags

// 	if (tcgetattr(STDIN_FILENO, &opt_terminal) == -1) {

// 		// verificando se a função de pegar as configurações atuais do teclado retorna -1
// 		// se sim, isso valida um erro e é retornado no stderr (saida de erro padrao)
// 		perror("tcgetattr");
// 		return 1;
// 	}

// 	printf("Configuração atual do terminal lida!\n");
// 	printf("c_lflag => %d\n", opt_terminal.c_lflag);

// 	return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios terminal;

void configuracoes_padroes () {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

void bloqueante () {
	atexit(configuracoes_padroes);
	struct termios blok;
	if ( tcgetattr(STDIN_FILENO, &terminal) == -1) {
		printf("Error\n");
		exit(1);
	}

	blok = terminal;

	blok.c_lflag &= ~(ECHO | ICANON);
	blok.c_cc[VMIN] = 0;
	blok.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &blok);
}

int main () {

	bloqueante();
	int i = 0;
	char c;
	while (1) {

		int n = scanf("%c", &c);

		if (n == 1 && c == 'q') {
			break;
		}

		if (n == 1) {
			printf("\rTecla capturada: %c(passo %d)", c, i);
		}else {
			printf("\rSimulando passo %d... (nenhuma tecla)", i);
		}

		fflush(stdout);

		i++;
		usleep(200000);
	}
	return 0;
}
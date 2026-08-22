#ifndef TERMINAL_H
#define TERMINAL_H

// versão estendida do TermCore: modo raw não-bloqueante + detecção de setas,
// prontas para virar a base de entrada dos visualizadores do GridForge

#define SETA_CIMA     1
#define SETA_BAIXO    2
#define SETA_DIREITA  3
#define SETA_ESQUERDA 4
#define SETA_NENHUMA  0
#define TECLA_NORMAL -1

void terminal_ativar_raw (void);
void terminal_restaurar (void);
int terminal_ler_entrada (char *tecla);

#endif

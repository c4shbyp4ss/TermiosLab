#ifndef TERMINAL_H
#define TERMINAL_H

// módulo reutilizável de terminal, base para os projetos interativos do GridForge

void terminal_ativar_raw (void);
void terminal_restaurar (void);
char terminal_ler_tecla (void);

#endif

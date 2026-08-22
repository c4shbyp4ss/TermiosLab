#ifndef NON_BLOCKING_MODE_H
#define NON_BLOCKING_MODE_H

#include <termios.h>

void ativaModoNaoBloqueante (struct termios *terminal);
void restauraTerminal (void);

#endif

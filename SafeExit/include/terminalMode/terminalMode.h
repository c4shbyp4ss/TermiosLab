#ifndef TERMINAL_MODE_H
#define TERMINAL_MODE_H

#include <termios.h>

void ativaModoSeguro (struct termios *terminal);
void ativaModoRaw (struct termios *terminal);
void restauraTerminal (void);

#endif

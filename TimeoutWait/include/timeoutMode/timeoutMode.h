#ifndef TIMEOUT_MODE_H
#define TIMEOUT_MODE_H

#include <termios.h>

void ativaModoComTimeout (struct termios *terminal);
void restauraTerminal (void);

#endif

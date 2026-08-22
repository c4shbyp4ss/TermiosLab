#ifndef RAW_MODE_H
#define RAW_MODE_H

#include <termios.h>

void ativaModoRaw (struct termios *terminal);
void alternaEco (void);
void restauraTerminal (void);

#endif

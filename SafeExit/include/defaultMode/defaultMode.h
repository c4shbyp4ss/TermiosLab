#ifndef DEFAULT_MODE_H
#define DEFAULT_MODE_H

#include <termios.h>


void setDefaultMode (struct termios * terminal);
void setDefaultOptionsTerminal (struct termios * terminal);
void restoreMode (void);


#endif
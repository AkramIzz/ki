#ifndef KI_INPUT_H
#define KI_INPUT_H

#ifdef _WIN32
char* readline(char *prompt);
void add_history(char *line);

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

#endif
#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#define PAUSE() while (getchar() != '\n')
#define TG 10 // tamanio de la grilla
char * read_line (char * buf, size_t length);
int de_tres_letras(const int i, const int j, const char sentido);
#endif

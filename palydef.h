#ifndef PALYDEF_H
#define PALYDEF_H

char pal[50][5], def[50][40];

void palydef_inicializar(void);
void palydef_elegir_palabras(int * respuestas[][2], const char sentido);
char * palydef_definicion(const int palabra);
int palydef_coincide(char * palabra, int respuesta);
//(n): esta bien (n = cantidad de puntos)
//(0): esta mal (carga las estadísticas!)
void palydef_estadisticas(void);
#endif

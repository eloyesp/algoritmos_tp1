// Tamanio de la grilla
# define TG 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palydef.h"

// variables globales:
char sentido;             // sentido en el que se juega el crucigrama.
char grilla[TG][TG];      // letras escritas en la grilla.
int respuestas[TG][2];    // listado de palabras elegidas al azar.

// Funciones
void bienvenida(void);
int menu(); // retorna falso si el usuario elige terminar ('t' o 'T')
void jugar(void);
void despedida(void);

// Funcion main
int main(void) {

	bienvenida();

	while (menu())
		jugar();

	despedida();

	return 0;
}


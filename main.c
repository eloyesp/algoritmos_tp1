// Tamanio de la grilla
#define TG 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palydef.h"

/**
  Variables globales:
*/
char sentido;             // sentido en el que se juega el crucigrama. Que puede ser H O V.
char grilla[TG][TG];      // letras escritas en la grilla.
int respuestas[TG][2];    // listado de palabras elegidas al azar.

/**
  Prototipos de Funciones
*/
void bienvenida(void);
int menu(); // retorna falso si el usuario elige terminar ('t' o 'T')
void jugar(void);
void despedida(void);
void vaciar_grilla(void);
void mostrar_grilla(void);
int cargar_palabra(void);
void resultados(void);
void elegir_palabras(void);
char * read_line (char * buf, size_t length);

// Funcion main
int main(void) {
	cargar_diccionario();
	bienvenida();

	while (menu())
		jugar();

	despedida();

	return 0;
}

void bienvenida(){
	printf("Hola...\n");
}

//menu elije entre jugar o salir.
int menu(){
	int opcion;
	printf("Si desea jugar ingrese 1 sino 0:\n");
	scanf("%d",&opcion);
	
	if (opcion==1)
		return 1;
	else
		return 0;
}

void jugar(){
	printf("Un juego\n");
	printf("%s\n",pal[0]);
	printf("%s\n",pal[20]);
	printf("Elegiste Horizontal, muy bien\n");
	sentido='H';
	vaciar_grilla();
	elegir_palabras();

	mostrar_grilla();
	
	while (cargar_palabra());
	resultados();
}

void despedida(){
	printf("Chau\n");
}

void vaciar_grilla(){
	int i,j;
	for (i=0;i<TG;i++){
		for (j=0;j<TG;j++){
			grilla[i][j] = '-';
		}
	}
}

void mostrar_grilla(){
	int i,j;
	for(i=0;i<TG;i++){
		for(j=0;j<TG;j++){
			printf(" %c ", grilla[i][j]);
		}
		printf("\n");
	}
	//Mostramos las definiciones de la grilla.
	for(i=0;i<TG;i++){
		for(j=0; j<2; j++){
			printf("Fila %d - Pal %d: %s \n", i, j, def[respuestas[i][j]]);
		}
	}
}

int cargar_palabra(){
	int fila, n, i;
	char c, palabra[10];
	printf("Ingrese la fila. (o -1 para salir)");
	scanf("%d",&fila);
	printf("Que palabra va a ingresar (1 = primera, 2 = segunda): ");
	scanf("%d", &n);
	if (fila - 1 >= 0 && fila - 1  < TG) {
		printf("Ingrese la palabra (de 3 letras): ");
		i = 0;
		while (i < 5 && (c = getchar()) != '\n' && c != '\0') {
			palabra[i] = c;
			i++;
		}
		palabra[i+1] = '\0';
		
		i = 0;
		while (palabra[i] != '\0' && palabra[i] != '\n') {
			grilla[0][i] = palabra [i];
		}
		return 1;
	} else {
		printf("Veo que aun no estas listo para cargar ninguna palabra 'T'...\n");
		return 0;
	}
}

void resultados(){
	printf("Muy bien...\n");
}

void elegir_palabras() {
	int i;
	for(i=0;i<TG;i++) {
		respuestas[i][0] = 0;
		respuestas[i][1] = 0;
	}
}

// Robado de home.datacomm.ch/t_wolf/tw/c/getting_input.html#skip

char * read_line (char * buf, size_t length)
	/**** Read at most 'length'-1 characters from the file 'f' into
	'buf' and zero-terminate this character sequence. If the
	line contains more characters, discard the rest.
	*/
{
	char *p;
	
	if ((p = fgets (buf, length, stdin))) {
		size_t last = strlen (buf) - 1;
		
		if (buf[last] == '\n') {
			/**** Discard the trailing newline */
			buf[last] = '\0';
		} else {
			/**** There's no newline in the buffer, therefore there must be
			more characters on that line: discard them!
			*/
			fscanf (stdin, "%*[^\n]");
			/**** And also discard the newline... */
			(void) fgetc (stdin);
		} /* end if */
	} /* end if */
	return p;
} /* end read_line */

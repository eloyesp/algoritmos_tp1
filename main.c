// Tamanio de la grilla
# define TG 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palydef.h"

// variables globales:
char sentido;             // sentido en el que se juega el crucigrama. Que puede ser H O V.
char grilla[TG][TG];      // letras escritas en la grilla.
int respuestas[TG][2];    // listado de palabras elegidas al azar.

// Funciones
void bienvenida(void);
int menu(); // retorna falso si el usuario elige terminar ('t' o 'T')
void jugar(void);
void despedida(void);
void vaciar_grilla(void);
void mostrar_grilla(void);
int cargar_palabra(void);
void resultados(void);
void elegir_palabras(void);

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

// Solicita al usuario el ingreso de una palabra del crucigrama.
// retorna 0 si el usuario desea terminar.
int cargar_palabra(){
	int fila, n, i;
	char c, palabra[6];
	printf("Ingrese la fila. (o -1 para salir): ");
	scanf("%d",&fila);
	while (getchar() != '\n'); // Limpio el buffer
	printf("Que palabra va a ingresar (1 = primera, 2 = segunda): ");
	scanf("%d", &n);
	while (getchar() != '\n'); // Limpio el buffer
	if (fila - 1 >= 0 && fila - 1  < TG) {
		printf("Ingrese la palabra (de 3 letras): ");
		i = 0;
		while (i < 6 && (c = getchar()) != '\n') {
			palabra[i] = c;
			i++;
		}
		if (i >= 6) {
			printf("Ingresaste muchas letras");
			while (getchar() != '\n'); // Limpio el buffer
		} else {
			// corto la palabra
			palabra[i] = '\0';
			if (strlen(palabra) == 3) {
				i = 0;
				while (palabra[i] != '\0') {
					grilla[0][i] = palabra [i];
				}
			} else {
				printf("Ingresaste pocas letras");
			}
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


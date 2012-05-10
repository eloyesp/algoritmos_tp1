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
}

int cargar_palabra(){
	printf("Veo que aun no estas listo para cargar ninguna palabra 'T'...\n");
	return 0;
}

void resultados(){
	printf("Muy bien...\n");
}


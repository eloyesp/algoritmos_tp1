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
char guion_asterisco(const int i, const int j);
int cargar_palabra(void);
void resultados(void);
void elegir_palabras(void);
char * read_line (char * buf, size_t length);
int ya_esta(const int valor, const int index);

// Funcion main
int main(void) {
	cargar_diccionario();
	bienvenida();

	while (menu())
		jugar();

	despedida();

	return 0;
}

void bienvenida() {
	int i;
	system("cls");

	for (i=0;i<80*2;i++){
		printf("#");
	}

	printf("\n\nBievenido a el crucigrama horizontal y vertical,"
		"\n          un crucigrama con 2 grandes opciones..."
		"\n          horizontal y vertical ! XD\n\n");

	for (i=0;i<80*2;i++){
		printf("#");
	}
	system("pause");
}

int menu() {
	/** elije entre jugar o salir.
	*/
	int opcion;
	char entrada[3];
	// Limpiar la pantalla
	system("cls");

	printf("---****----****----**** Crucigrama Horizontal o Vertical ****----****----****---");
	printf("\n\n\n\n");
	printf("                          Menu principal\n");
	printf("                          1) Jugar.\n\n");
	printf("                          2) Salir.\n\n");
	printf("                      Ingrese una opcion valida:\n\n");
	read_line(entrada, 3);
	opcion = atoi(entrada);

	while(opcion!=1 && opcion!=2){
		printf("Ingreso una opcion incorrecta.\nIngrese nuevamente la opcion que desea:\n");
		read_line(entrada, 3);
		opcion = atoi(entrada);
	}

	if (opcion==1)
		return 1;
	else
		return 0;
}

void jugar() {
	/** Inicializa las variables del juego y permite cargar las palabras
	*/
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

void despedida() {
	int i;
	system("cls");

	for (i=0;i<80*2;i++){
		printf("#");
	}

	printf("\n\nMUCHAS GRACIAS POR JUGAR..."
		"\n          RECUERDE QUE EN ESTE JUEGO GANA EL MAS PERSISTENTE"
		"\n          PERSISTE Y VENCERAS...! XD\n\n");

	for (i=0;i<80*2;i++){
		printf("#");
	}
}

void vaciar_grilla() {
	/** Llena la grilla de - o * segun corresponda.
	*/
	int i, j;
	for (i=0; i<TG; i++) {
		for (j=0; j<TG; j++) {
			grilla[i][j] = guion_asterisco(i, j);
		}
	}
}

char guion_asterisco(const int i, const int j) {
	/** retorna - o * segun corresponda a la fila y columna.
	*/
	char value;
	if (j < 3 || j > 5)
		value = '-';
	else if (j > 3 && j < 6)
		value = '*';
	else {
		if ((i % 2) == 0)
			value = '-';
		else
			value = '*';
	}
	return value;
}

void mostrar_grilla() {
	/** Muestra al usuario la grilla (en su estado actual) y las definiciones.
	*/
	int i,j;
	system("cls");
	printf("----****----****----**** Crucigrama Horizontal ****----****----****----\n");
	printf("\n\n");

	for (i=0;i<TG;i++) {
		printf("                    %2d)", i+1);
		for (j=0; j<TG; j++) {
			printf(" %c ", grilla[i][j]);
		}
		printf("\n");
	}
	printf("\nDefiniciones:\n");
	//Mostramos las definiciones de la grilla.
	for (i=0;i<TG;i++) {
		for(j=0; j<2; j++) {
			printf("Fila %d - Pal %d: %s | ", i, j, def[respuestas[i][j]]);
		}
	}
	printf("\n");
}

int cargar_palabra() {
	/** Permite al usuario cargar una palabra en el crucigrama.
	*/
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

void resultados() {
	/** Indica al usuario el puntaje obtenido, asi como sus aciertos y errores.
	*/
	printf("Muy bien...\n");
}

void elegir_palabras() {
	/** Elige aleatoriamiente las palabras para llenar el crucigrama.
	*/
	int i,aux;
	for (i=0; i<TG*2; i++) {
		do {
			aux = rand()%50;
		} while ( ya_esta(aux, i) );

		respuestas[0][i] = aux;
	}
}

int ya_esta(const int valor, const int index) {
	/** retorna verdadero si el valor ya esta en la matriz y falso si no esta.
	    O sea, avisa si la palabra ya fue elegida.
	*/
	int i=0;
	while (valor!=respuestas[0][i] && i<index) {
		i++;
	}
	return (valor == respuestas[0][i]);
}

char * read_line (char * buf, size_t length) {
	/**** Robado de home.datacomm.ch/t_wolf/tw/c/getting_input.html#skip
	Read at most 'length'-1 characters from the file 'f' into
	'buf' and zero-terminate this character sequence. If the
	line contains more characters, discard the rest.
	*/

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


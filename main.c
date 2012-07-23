/*							Trabajo Practico Nº1

							Grupo nº1

-------------------------------------------------------------------------------
Integrantes 				Direccion de correo 	
-------------------------------------------------------------------------------
Eloy Espinaco				eloyesp@gmail.com
Daiana Giorgi				daia_gior@hotmail.com
Roberto Cavalcabué			eltotti_38@hotmail.com
*/

// Tamanio de la grilla
#define TG 10 // tamanio de la grilla
#define SP 6  // inicio de la segunda palabra
#define TI 6  // Tamanio del ingreso de palabra.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "palydef.h"
#include "usuario.h"
#include "utils.h"

/**   Variables globales:
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
void mostrar_grilla_vertical(void);
void mostrar_grilla_horizontal(void);
char guion_asterisco(const int i, const int j);
int cargar_palabra(void);
int palabra_valida(const char input[]);
int de_tres_letras(const int fila, const int columna);
void resultados(void);
int asignar_puntaje(const int fila, const int palabra);
void elegir_palabras(void);
char * read_line (char * buf, size_t length);
int ya_esta(const int valor, const int index);

// Funcion main
int main(void) {
	palydef_inicializar();
	bienvenida();

	while (menu());

	despedida();

	return(0);
}

void bienvenida() {
	int i;
	system("cls");

	for (i=0;i<80*2;i++){
		printf(".*.");
	}
	printf("\n\n  		Bienvenidos a la Aplicacion Crucigrama!!\n\n");
	for (i=0;i<80*2;i++){
		printf(".*.");
	}

	PAUSE();
}

int menu() {
	/** elije entre jugar o salir.
	*/
	int opcion;
	char entrada[3];
	// Limpiar la pantalla
	system("cls");

	printf(
		"---****----****----**** Crucigrama Horizontal o Vertical ****----****----****---"
		"\n\n\n\n"
		"                          Menu principal\n\n"
		"                          1) Alta de usuario.\n\n"
		"                          2) Jugar.\n\n"
		"                          3) Estadisticas.\n\n"
		"                          4) Salir.\n\n"
		"                      Ingrese una opcion valida: ");
	read_line(entrada, 3);
	opcion = atoi(entrada);

	while(opcion < 1 || opcion > 4 ){
		printf("\nIngreso una opcion incorrecta.\nIngrese nuevamente la opcion que desea: ");
		read_line(entrada, 3);
		opcion = atoi(entrada);
	}

	if (opcion == 1)
		usuario_alta();
	else if(opcion == 2)
		jugar();
	else if (opcion == 3) {
		printf("no implementado");
		PAUSE();
	}
	else
		return 0;

	return(1);
}

void jugar()
{
	/** Inicializa las variables del juego y permite cargar las palabras
	*/
	char entrada[3];
	int opcion;
	int usuario;
	
	// pedir cuil
	usuario = usuario_login();
	
	if (usuario == -2) {
		printf("Su cuil no es correcto");
		return;
	}
	
	printf("\n\n"
		"                          1) Horizontal.\n\n"
		"                          2) Vertical.\n\n"
		"                      Ingrese una opcion valida: ");
	read_line(entrada, 3);
	opcion = atoi(entrada);
	while(opcion!=1 && opcion!=2){
		printf("Ingreso una opcion incorrecta.\nIngrese nuevamente la opcion que desea: ");
		read_line(entrada, 3);
		opcion = atoi(entrada);
	}
	if (opcion == 1)
		sentido = 'H';
	else
		sentido = 'V';
	
	vaciar_grilla();
	elegir_palabras();
	
	mostrar_grilla();
	while(cargar_palabra()) {
		mostrar_grilla();
	}
	resultados();
}

void despedida() {
	int i;
	system("cls");

	for (i=0;i<80*2;i++){
		printf(".*.");
	}

	printf("\n\n 				GAME OVER\n\n");

	for (i=0;i<80*2;i++){
		printf(".*.");
	}
}

void vaciar_grilla(void) {
	/** Llena la grilla de - o * segun corresponda.*/
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
		value = (de_tres_letras(i, 0)) ? '*' : '-';
	}
	return value;
}

void mostrar_grilla(void) {
	/** Muestra al usuario la grilla (en su estado actual) y las definiciones.
	*/
	int i,j;
	char fila_columna[8];
	system("cls");
	if (sentido == 'H') {
		strcpy(fila_columna, "Fila");
		printf("----****----****----**** Crucigrama Horizontal ****----****----****----\n\n\n");
		mostrar_grilla_horizontal();
	} else {
		strcpy(fila_columna, "Columna");
		printf("----****----****----****  Crucigrama Vertical  ****----****----****----\n\n\n");
		mostrar_grilla_vertical();
	}
	
	printf("\n\nDefiniciones:\n");
	//Mostramos las definiciones de la grilla.
	for (i=0;i<TG;i++) {
		for(j=0; j<2; j++) {
			printf("%s %d - %d: %s \n", fila_columna, i+1, j+1, def[respuestas[i][j]]);
		}
	}
	printf("\n");
}

void mostrar_grilla_vertical(void) {
	int i, j;
	printf("                         1  2  3  4  5  6  7  8  9  10\n");
	for (i=0;i<TG;i++) {
		printf("                        ", i+1);
		for (j=0; j<TG; j++) {
			printf(" %c ", grilla[j][i]);
		}
		printf("\n");
	}
}

void mostrar_grilla_horizontal(void) {
	int i, j;
	
	for (i=0;i<TG;i++) {
		printf("                    %2d)", i+1);
		for (j=0; j<TG; j++) {
			printf(" %c ", grilla[i][j]);
		}
		printf("\n");
	}
}

int cargar_palabra() {
	/** Permite al usuario cargar una palabra en el crucigrama.
	*/
	int fila, columna, cantidad_de_letras, i=0, d;
	char ingreso[TI];

	printf("Ingrese la fila: ");
	read_line(ingreso, TI);
	while (!((atoi(ingreso) <= 10 && atoi(ingreso) >= 1) || ((ingreso[0] == 't'
		|| ingreso[0] == 'T') && ingreso[1] == '\0'))) {
		printf("Ingrese la fila (entre 1 y 10) ('T' para terminar): ");
		read_line(ingreso, TI);
	}
	if ((ingreso[0] != 't') && (ingreso[0] != 'T')) {
		fila = atoi(ingreso) - 1;
		printf("Ingrese el numero de palabra: ");
		read_line(ingreso, TI);
		while (!((atoi(ingreso) <= 2 && atoi(ingreso) >= 1) || ((
			ingreso[0] == 't' || ingreso[0] == 'T') && ingreso[1] == '\0'))) {
				printf("Ingrese el numero de palabra. (1 o 2) ('T' para terminar): ");
				read_line(ingreso, TI);
			}
		
		
		if ((ingreso[0] != 't') && (ingreso[0] != 'T')) {
			columna = atoi(ingreso) - 1;
			d = (columna == 0) ? 0 : SP;
			cantidad_de_letras = (de_tres_letras(fila, columna)) ? 3 : 4;

			printf("Ingrese la Palabra: ");
			read_line(ingreso, TI);
			while (strlen(ingreso) != cantidad_de_letras || !palabra_valida(ingreso)) {
					printf("Ingrese la palabra (%d:%d : %s )(%d letras): ", 
						fila+1, columna+1, def[respuestas[fila][columna]], cantidad_de_letras);
					read_line(ingreso, TI);
				}
			// Ingreso la palabra en el crucigrama.
			for (i=0; i < cantidad_de_letras; i++) {
				grilla[fila][i+d] = ingreso[i];
			}
		}
	}

	return i; // i es 0 exepto que se halla cargado una palabra.
}

int palabra_valida(const char input[]) {
	int i=0, valida = 1;
	char c;
	c = input[i];
	while (valida == 1 && c != '\0') {
		if (c >= 48 && c <= 57) {
			valida = 0;
			printf("La palabra no puede contener numeros\n");
		}
		if (c == '-' || c == '*') {
			valida = 0;
			printf("La palabra no puede contener ni guion(-) ni asteriscos(*)\n");
		}
		i++;
		c = input[i];
	}
	return valida;
}

int de_tres_letras(const int i, const int j) {
	/** Verdadero si la cantidad de letras que tiene la palabra correspondiente
	    Es 3.
	*/
	int es_tres;
	if (j != 0) {
		es_tres = 0;
	} else {
		if ((sentido == 'H' && (i % 2) == 0) || (sentido == 'V' && (i % 2) == 1))
			es_tres = 0;
		else
			es_tres = 1;
	}
	return es_tres;
	
}
void resultados() {
	/** Indica al usuario el puntaje obtenido, asi como sus aciertos y errores.
	*/
	int i, j, totalpuntos = 0;
	// recorrer filas e indicar errores.
	for (i=0;i<TG;i++) {
		for (j=0; j<2; j++) {
			totalpuntos += asignar_puntaje(i, j);
		}
	}	

	// Dar mensaje de felicitaciones si no hay errores.
	if(totalpuntos == 75){
		printf("\n\n\n\n");
		printf(".+.+.+..+.+.+.+.+.+.+.+.+++.+.+.+.+.+.+.+.+.+.+.+.+.+.+.+.+++");
		printf("                 FELICITACION: CRUCIGRAMA CORRECTO");
		printf(".+.+.+..+.+.+.+.+.+.+.+.+++.+.+.+.+.+.+.+.+.+.+.+.+.+.+.+.+++");
	}
	
	// Puntaje
	printf("puntaje: %d de 75 (%.2f %%)\n",  totalpuntos, (float) totalpuntos / 75 * 100 );
	system("pause");
}

int asignar_puntaje(const int fila, const int palabra){
	int d, j=0, correcta = 0, cantidad_de_letras, puntos;
	d = palabra * 6;
	cantidad_de_letras = de_tres_letras(fila, palabra) ? 3 : 4;
	
	while ( j<cantidad_de_letras && correcta == 0) {
		if (grilla[fila][j+d] == '-')
			correcta = 1;
		else if (grilla[fila][j+d] != pal[respuestas[fila][palabra]][j])
			correcta = 2;
		j++;
	}
	
	if (correcta == 0)
		puntos = cantidad_de_letras;
	else if (correcta==1) {
		puntos = 0;
		printf("La palabra %d de la fila %d esta vacia.\n", palabra+1, fila+1);
	} else {
		puntos=0;
		printf("La palabra %d de la fila %d esta incorrecta.\n", palabra+1, fila+1);
	}

	return puntos;
}

void elegir_palabras() {
	/** Elige aleatoriamiente las palabras para llenar el crucigrama.
	*/
	int i, j, aux,hora;
	hora=time(NULL);
	srand(hora);
	for (i=0; i<TG; i++) {
		for (j=0; j<2; j++) {
			do {
				aux = (de_tres_letras(i, j)) ? rand()%20 : rand()%30+20;
			} while ( ya_esta(aux, 2*i + j) );

			respuestas[i][j] = aux;
		}
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

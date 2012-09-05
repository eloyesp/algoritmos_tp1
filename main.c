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
#define SP 6  // inicio de la segunda palabra
#define TI 6  // Tamanio del ingreso de palabra.
#include <stdio.h>
#include <stdlib.h>
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
void resultados(const int num_usuario);
int asignar_puntaje(const int fila, const int palabra);

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
		printf(".*.*.*.*.*.*.*.*.*.*.*.*. ESTADISTICAS DEL CRUCIGRAMA .*.*.*.*.*.*.*.*.*.*.*.");
		printf("\n\n\n\n");
		usuario_estadisticas();
		palydef_estadisticas();
		printf(".*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
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
	int num_usuario;
	
	// pedir cuil
	num_usuario = usuario_login();
	
	if (num_usuario == -2) {
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
	palydef_elegir_palabras(respuestas, sentido);
	
	mostrar_grilla();
	while(cargar_palabra()) {
		mostrar_grilla();
	}
	resultados(num_usuario);
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
		value = (de_tres_letras(i, 0, sentido)) ? '*' : '-';
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
			printf("%s %d - %d: %s \n", fila_columna, i+1, j+1, palydef_definicion(respuestas[i][j]));
		}
	}
	printf("\n");
}

void mostrar_grilla_vertical(void) {
	int i, j;
	printf("                         1  2  3  4  5  6  7  8  9  10\n");
	for (i=0;i<TG;i++) {
		printf("                        ");
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
	char ingreso[TI], fila_columna[8];
	
	if (sentido == 'H') {
		strcpy(fila_columna, "Fila");		
	} else {
		strcpy(fila_columna, "Columna");
	}

	printf("Ingrese la %s: ", fila_columna);
	read_line(ingreso, TI);
	while (!((atoi(ingreso) <= 10 && atoi(ingreso) >= 1) || ((ingreso[0] == 't'
		|| ingreso[0] == 'T') && ingreso[1] == '\0'))) {
		printf("Ingrese la %s (entre 1 y 10) ('T' para terminar): ", fila_columna);
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
			cantidad_de_letras = (de_tres_letras(fila, columna, sentido)) ? 3 : 4;

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
	/** Valida una palabra ingresada por el usuario.
		Si no es valida, da el mensaje de error y retorna 0.
		Retorna 1 si la palabra es valida. 
	*/
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

void resultados(const int num_usuario) {
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
	usuario_cargar_puntaje(num_usuario, totalpuntos);
	PAUSE();
}

int asignar_puntaje(const int fila, const int palabra){
	int puntos;
	
	puntos = palydef_coincide(&grilla[fila][palabra * 6], respuestas[fila][palabra]);
	
	if ( puntos == -1 ) {
		puntos = 0;
		printf("La palabra %d de la fila %d esta vacia.\n", palabra+1, fila+1);
	} else if ( puntos == -2 ){
		puntos = 0;
		printf("La palabra %d de la fila %d esta incorrecta.\n", palabra+1, fila+1);
	}

	return puntos;
}

#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "palydef.h"
#include "utils.h"

#define  ESTADISTICAS "estadisticas.dat"

int ya_esta(const int valor, const int index, int respuestas[][2]);
void cargar_estadistica(const int respuesta);
int terminada_en_o(const char * const palabra);
int con_r(const char * const palabra);

void palydef_inicializar(void)
	/** Inicializa los vectores pal[] y def[]
	// pal son las palabras
	// pal[0-19] tienen 3 letras y pal[20-49] tienen 4 letras.
	// def son las definiciones correspondientes.
	*/
{
	strcpy(pal[0], "une");
	strcpy(def[0], "Junta, enlaza una cosa con otra.");

	strcpy(pal[1], "oso");
	strcpy(def[1], "Animal muy grande que te abraza.");

	strcpy(pal[2], "ron");
	strcpy(def[2], "Licor alcoholico de la melaza.");

	strcpy(pal[3], "log");
	strcpy(def[3], "Logaritmo.");

	strcpy(pal[4], "tnt");
	strcpy(def[4], "Explosivo poderoso.");
	
	strcpy(pal[5], "aji");
	strcpy(def[5], "Pimiento.");
	
	strcpy(pal[6], "ley");
	strcpy(def[6], "Precepto dictado por la sup. autoridad.");
	
	strcpy(pal[7], "feo");
	strcpy(def[7], "Que carece de belleza.");
	
	strcpy(pal[8], "uno");
	strcpy(def[8], "Numero que le sigue al cero.");
	
	strcpy(pal[9], "sol");
	strcpy(def[9], "Estrella luminosa cercana a la tierra.");
	
	strcpy(pal[10], "ojo");
	strcpy(def[10], "Organo de la vista");
	
	strcpy(pal[11], "ola");
	strcpy(def[11], "Movimiento que hace el agua en el mar.");
	
	strcpy(pal[12], "sal");
	strcpy(def[12], "Cloruro de sodio.");
	
	strcpy(pal[13], "rap");
	strcpy(def[13], "Ritmo negro urbano.");
	
	strcpy(pal[14], "uva");
	strcpy(def[14], "Fruta pequenia y redonda.");
	
	strcpy(pal[15], "oro");
	strcpy(def[15], "Metal amarillo.");
	
	strcpy(pal[16], "oca");
	strcpy(def[16], "El juego de la...");
	
	strcpy(pal[17], "via");
	strcpy(def[17], "Por donde pasa el tren.");
	
	strcpy(pal[18], "cal");
	strcpy(def[18], "CaO");
	
	strcpy(pal[19], "pan");
	strcpy(def[19], "Alimento (en general)");
	
	strcpy(pal[20], "casa");
	strcpy(def[20], "Habitat de un ser humano.");
	
	strcpy(pal[21], "chau");
	strcpy(def[21],"Adios.");
	
	strcpy(pal[22],"soda");
	strcpy(def[22],"Agua con gas.");
	
	strcpy(pal[23],"sopa");
	strcpy(def[23],"Alimento liquido.");
	
	strcpy(pal[24],"joya");
	strcpy(def[24],"Alahja.");
	
	strcpy(pal[25],"gota");
	strcpy(def[25],"Cantidad muy pequenia de liquido.");
	
	strcpy(pal[26],"pena");
	strcpy(def[26],"Castigo.");
	
	strcpy(pal[27],"chip");
	strcpy(def[27],"Circuito integrado electronico.");
	
	strcpy(pal[28],"lila");
	strcpy(def[28],"Violeta claro.");
	
	strcpy(pal[29],"tour");
	strcpy(def[29],"Excursion turistica.");
	
	strcpy(pal[30], "alfa");
	strcpy(def[30],"letra griega a.");
	
	strcpy(pal[31],"zeus");
	strcpy(def[31],"Dios del olimpo.");
	
	strcpy(pal[32],"auto");
	strcpy(def[32],"Medio de transporte familiar.");
	
	strcpy(pal[33],"Arpa");
	strcpy(def[33],"Instrumento musical de cuerdas.");
	
	strcpy(pal[34],"tuba");
	strcpy(def[34],"Instrumento mucical de viento.");
	
	strcpy(pal[35],"papa");
	strcpy(def[35],"Tuberculo.");
	
	strcpy(pal[36],"coco");
	strcpy(def[36],"Fruta de palmera.");
	
	strcpy(pal[37],"rata");
	strcpy(def[37],"Mamifero roedor pequenio.");
	
	strcpy(pal[38],"cana");
	strcpy(def[38],"Pelo blanco.");
	
	strcpy(pal[39],"nono");
	strcpy(def[39],"Dos veces no.");
	
	strcpy(pal[40],"ogro");
	strcpy(def[40],"criatura verde animada que es mala");
	
	strcpy(pal[41],"jefe");
	strcpy(def[41],"Conductor de un grupo.");
	
	strcpy(pal[42],"gato");
	strcpy(def[42],"Animal felino.");
	
	strcpy(pal[43],"cama");
	strcpy(def[43],"Lugar de descanso.");
	
	strcpy(pal[44],"boca");
	strcpy(def[44],"Orificio donde entra la comida.");
	
	strcpy(pal[45],"loco");
	strcpy(def[45],"Persona fuera de si.");
	
	strcpy(pal[46],"ropa");
	strcpy(def[46],"Cualquier prenda de tela.");
	
	strcpy(pal[47],"foco");
	strcpy(def[47],"Lampara que emite luz.");
	
	strcpy(pal[48],"mayo");
	strcpy(def[48],"Quinto mes del anio.");
	
	strcpy(pal[49],"taza");
	strcpy(def[49],"Vasija pequenia para tomar liquidos.");
}

void palydef_elegir_palabras(int respuestas[][2], const char sentido) {
	/** Elige aleatoriamiente las palabras para llenar el crucigrama.
	*/
	int i, j, aux;
	
	srand(time(NULL));
	
	for (i=0; i<TG; i++) {
		for (j=0; j<2; j++) {
			do {
				aux = (de_tres_letras(i, j, sentido)) ? rand()%20 : rand()%30+20;
			} while ( ya_esta(aux, 2*i + j, respuestas) );
			
			respuestas[i][j] = aux;
		}
	}
}

char * palydef_definicion(const int palabra) {
	return def[palabra];
}

int palydef_coincide(const char * palabra, const int respuesta) {
	/** Chequea si la palabra coincide con la respuesta, agrega las estadisticas
		y retorna el puntaje correspondiente, o -1 si la palabra esta vacia o -2
		si la palabra esta errada.
	*/
	int correcta = 0, i = 0;

	// Chequea si coincide.
	while ( pal[respuesta][i] != '\0' && correcta == 0) {
		if ( palabra[i] == '-')
			correcta = -1;
		else if ( palabra[i] != pal[respuesta][i] )
			correcta = -2;
		i++;
	}

	// Carga las estadisticas y da el mensaje correspondiente.
	if ( correcta == 0 ) {
		correcta = i;
		cargar_estadistica(respuesta);
	}

	return correcta;
}

void cargar_estadistica(const int respuesta) {
	Estadistica estadistica;
	FILE * estadisticas;
	estadisticas = fopen(ESTADISTICAS, "rb+");
	int i;
	
	if (estadisticas == NULL) {
		// Si no hay archivo de estadisticas creo uno vacio
		estadisticas = fopen(ESTADISTICAS, "wb");
		if (estadisticas == NULL) {
			printf("algo malo ha ocurrido!");
		} else {
			estadistica.aciertos = 0;
			for (i=0; i<50; i++) {
				estadistica.id = i;
				fwrite(&estadistica, sizeof(Estadistica), 1, estadisticas);
			}
			// y hacemos lo que vinimos a hacer
			fseek(estadisticas, sizeof(Estadistica) * (respuesta), SEEK_SET);
			estadistica.aciertos += 1;
			estadistica.id = respuesta;
			fwrite(&estadistica, sizeof(Estadistica), 1, estadisticas);
			fclose(estadisticas);
		}
	} else {
		fseek(estadisticas, sizeof(Estadistica) * (respuesta - 1), SEEK_SET);
		fread(&estadistica, sizeof(Estadistica), 1, estadisticas);
		estadistica.aciertos += 1;
		fseek(estadisticas, - sizeof(Estadistica), SEEK_CUR);
		fwrite(&estadistica, sizeof(Estadistica), 1, estadisticas);
		fclose(estadisticas);
	}
	return;
}


void palydef_estadisticas(void) {
	char * palabra_mas_adivinada;
	int palabra_mas_adivinada_cantidad = 0;
	char * palabra_menos_adivinada;
	int palabra_menos_adivinada_cantidad = 0;
	int palabras_adivinadas = 0;
	int palabras_acertadas_terminadas_en_o = 0;
	int palabras_acertadas_con_r = 0;
	
	Estadistica estadistica;
	FILE * estadisticas;
	estadisticas = fopen(ESTADISTICAS, "rb");
	
	if (estadisticas == NULL)
		printf("El archivo de estadisticas no se pudo abrir.");
	else {
		// cargo el primer elemento fuera del bucle.
		fread(&estadistica, sizeof(Estadistica), 1, estadisticas);
		palabras_adivinadas += estadistica.aciertos;
		palabra_mas_adivinada = palabra_menos_adivinada = pal[0];
		palabra_mas_adivinada_cantidad = palabra_menos_adivinada_cantidad = estadistica.aciertos;
		puts("");
		while (fread(&estadistica, sizeof(Estadistica), 1, estadisticas)) {
			palabras_adivinadas += estadistica.aciertos;
			if (terminada_en_o(pal[estadistica.id]))
				palabras_acertadas_terminadas_en_o += estadistica.aciertos;
			printf("%s : %i \n", pal[estadistica.id], con_r(pal[estadistica.id]));
			if (con_r(pal[estadistica.id]))
				palabras_acertadas_con_r += estadistica.aciertos;
			// TODO: que pasa cuando hay 5 palabras con el maximo de aciertos
			if (palabra_mas_adivinada_cantidad <= estadistica.aciertos) {
				palabra_mas_adivinada_cantidad = estadistica.aciertos;
				palabra_mas_adivinada = pal[estadistica.id];
			}
			if (palabra_menos_adivinada_cantidad >= estadistica.aciertos) {
				palabra_menos_adivinada_cantidad = estadistica.aciertos;
				palabra_menos_adivinada = pal[estadistica.id];
			}
		}
		fclose(estadisticas);
	}

	/*buscamos la palabra mas adivinada.. si es una solo imprimimos una y si son varias se imrimen esas varias*/
	if (palabras_adivinadas != 0) {
		printf("\nPalabras adivinadas: %i\n", palabras_adivinadas);
		printf("\n(*) La palabra mas adivinada es \"%s\" que ha sido adivinada %i veces\n", palabra_mas_adivinada, palabra_mas_adivinada_cantidad);
		printf("\n(*) La palabra menos adivinada es \"%s\" que ha sido adivinada %i veces\n", palabra_menos_adivinada, palabra_menos_adivinada_cantidad);
		printf("\n(*) El porcentaje de palabras acertadas terminadas con la letra O es: %.2f%%\n", (float) palabras_acertadas_terminadas_en_o / palabras_adivinadas);
		printf("\n(*) El porcentaje de palabras acertadas que contienen la letra R en algun lugar de la palabra es : %.2f%%\n", (float) palabras_acertadas_con_r / palabras_adivinadas);
	} else {
		printf("\n No hay registros sobre palabras acertadas\n");
	}
}

int ya_esta(const int valor, const int index, int respuestas[][2]) {
	/** retorna verdadero si el valor ya esta en la matriz y falso si no esta.
	O sea, avisa si la palabra ya fue elegida.
	*/
	int i=0;
	while (valor!=respuestas[0][i] && i<index) {
		i++;
	}
	return (valor == respuestas[0][i]);
}

int terminada_en_o(const char * const palabra) {
	// TODO: implementar
	return 0;
}
int con_r(const char * const palabra) {
	int i = 0, encontrado = 0;
	while( !encontrado && palabra[i] != '\0') {
		if ('r' == palabra[i])
			encontrado = 1;
		i++;
	}
	return encontrado;
}


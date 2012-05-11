// pal son las palabras
// pal[0-19] tienen 3 letras y pal[20-49] tienen 4 letras.
// def son las definiciones correspondientes.
#include <string.h>
char pal[50][5], def[50][40];

void cargar_diccionario(void) {
	strcpy(pal[0], "oso");
	strcpy(def[0], "Animal muy grande que te abraza.");

	strcpy(pal[20], "casa");
	strcpy(def[20], "Habitat de un ser humano.");
}


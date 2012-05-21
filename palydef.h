// pal son las palabras
// pal[0-19] tienen 3 letras y pal[20-49] tienen 4 letras.
// def son las definiciones correspondientes.
#include <string.h>
char pal[50][5], def[50][40];

void cargar_diccionario(void)
{
	strcpy(pal[0], "oso");
	strcpy(def[0], "Animal muy grande que te abraza.");

	strcpy(pal[1], "une");
	strcpy(def[1], "Junta, enlaza una cosa con otra.");

	strcpy(pal[2], "ron");
	strcpy(def[2], "Licor alcohólico de la melaza.");

	strcpy(pal[3], "log");
	strcpy(def[3], "Logaritmo.");

	strcpy(pal[4], "tnt");
	strcpy(def[4], "Explosivo poderoso.");

	strcpy(pal[5], "aji");
	strcpy(def[5], "Pimiento.");

	strcpy(pal[6], "ley");
	strcpy(def[6], "Precepto dictado por la suprema autoridad.");

	strcpy(pal[7], "feo");
	strcpy(def[7], "Que carece de belleza.");

	strcpy(pal[8], "uno");
	strcpy(def[8], "Numero que le sigue al cero.");

	strcpy(pal[9], "sol");
	strcpy(def[9], "Estrella luminosa cercana a la tierra.");

	strcpy(pal[10], "ojo");
	strcpy(def[10], "Organo de la vista OJO");

	strcpy(pal[11], "ola");
	strcpy(def[11], "Movimiento que hace el agua en el mar.");

	strcpy(pal[12], "sal");
	strcpy(def[12], "Cloruro de sodio.");

	strcpy(pal[13], "rap");
	strcpy(def[13], "Ritmo negro urbano.");

	strcpy(pal[14], "uva");
	strcpy(def[14], "Fruta pequeña y redonda.");

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
	strcpy(def[25],"Cantidad muy pequeña de liquido.");

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
	strcpy(def[37],"Mamifero roedor pequeño.");

	strcpy(pal[38],"cana");
	strcpy(def[38],"Pelo blanco.");

	strcpy(pal[39],"nono");
	strcpy(def[39],"Dos veces no.");

	strcpy(pal[40],"ogro");
	strcpy(def[40],"criatura verde animada que es mala");

	strcpy(pal[41],"jefe");
	strcpy(def[41],"Persona que tiene poder o autoridad sobre un grupo para dirigir su trabajo.");

	strcpy(pal[42],"gato");
	strcpy(def[42],"Animal felino.");

	strcpy(pal[43],"cama");
	strcpy(def[43],"Lugar de descanso.");

	strcpy(pal[44],"boca");
	strcpy(def[44],"Orificio donde entra la comida.");

	strcpy(pal[45],"loco");
	strcpy(def[45],"Persona fuera de si.");

	strcpy(pal[46],"ropa");
	strcpy(def[46],"Cualquier prenda de tela que sirve para vestir.");

	strcpy(pal[47],"foco");
	strcpy(def[47],"Lampara que emite luz.");

	strcpy(pal[48],"mayo");
	strcpy(def[48],"Quinto mes del anio.");

	strcpy(pal[49],"taza");
	strcpy(def[49],"Vasija pequenia para tomar liquidos.");
}


#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define  TAM 13
#define  CUIL 15
#define  USUARIOS "usuarios.dat"

int profesion_valida(const char profesion[]);
void cargar_fecha(Fecha * fecha);
int validar_cuil(char * ingreso);
int cantidad_de_registros(FILE * usuarios);
int DNI = 0;

void usuario_alta() {
	FILE * usuarios;
	Usuario nuevo_usuario;
	char ingreso[MAX_NOMBRE];
	char profesion[8] = "abogado\0";
	char profesion1[10] = "ingeniero\0";
	char profesion2[9] = "contador\0";
	usuarios = fopen(USUARIOS, "ab+");

	if (usuarios != NULL) {
		// Ingreso de datos
		printf("Ingrese la Profesion: ");
		read_line(nuevo_usuario.profesion, MAX_NOMBRE);
		while(strcmp(profesion,nuevo_usuario.profesion) != 0 && strcmp(profesion1,nuevo_usuario.profesion) != 0 && strcmp(profesion2,nuevo_usuario.profesion) != 0){
			printf("Ingrese la Profesion: ");
			read_line(nuevo_usuario.profesion, MAX_NOMBRE);
		}
		printf("Ingrese Nombre: ");
		read_line(nuevo_usuario.nombre, MAX_NOMBRE);
		printf("Ingrese Apellido: ");
		read_line(nuevo_usuario.apellido, MAX_NOMBRE);
		printf("DNI: ");
		read_line(ingreso, MAX_NOMBRE);
		nuevo_usuario.dni = atoi(ingreso);
		printf("Fecha de nacimiento:\n");
		cargar_fecha(&nuevo_usuario.nacimiento);
		printf("Fecha de ingreso al colegio:\n");
		cargar_fecha(&nuevo_usuario.inscripcion);
		nuevo_usuario.num_usuario = cantidad_de_registros(usuarios) + 1;
		//pongo en cero las estadisticas 
		nuevo_usuario.partidas_jugadas = 0;
		nuevo_usuario.crucigramas_completos = 0;
		nuevo_usuario.mayor_puntaje = -1;
		// Registro en el archivo
		fseek(usuarios, (nuevo_usuario.num_usuario - 1) * sizeof(Usuario), SEEK_SET);
		fwrite(&nuevo_usuario, sizeof(Usuario), 1, usuarios);
		printf("Enhorabuena %s, ha sido registrado con el numero de usuario: %i", nuevo_usuario.nombre, nuevo_usuario.num_usuario);
		fclose(usuarios);
	} else {
		puts("No se pudo abrir el archivo");
	}
	
	PAUSE();
	return;
}

int usuario_login(Usuario * usuario) {
	FILE * usuarios; 
	char ingreso[CUIL];
	int dni, encontrado = 0;
	
	system("cls");
	printf("Ingrese el numero de CUIL (Ej. 99-99999999-9): ");
	read_line(ingreso, CUIL);
	dni = validar_cuil(ingreso);

	if (dni == -2) {
		usuario->num_usuario = -2;
		printf("Su cuil no es correcto\n\n");
		PAUSE();
	} else {
		usuarios = fopen(USUARIOS, "rb");
		if (usuarios == NULL)
			printf("El archivo no se pudo abrir.");
		else {
			while (encontrado == 0 && !feof(usuarios)) {
				fread(usuario, sizeof(Usuario), 1, usuarios);
				if (dni == usuario->dni) {
					encontrado = 1;
				}
			}
		}
		if (encontrado == 0) {
			usuario->num_usuario = -1;
			strcpy(usuario->nombre, ingreso);
		}
	}
	
	return usuario->num_usuario;
}

int profesion_valida(const char profesion[]) {
	int tiene_profesion = 0, i = 0;
	const char * profesiones[] = { "contador", "abogado", "ingeniero"};
	
	while (!tiene_profesion && i < 3) {
		if (!strcmp(profesion, profesiones[i])) {
			tiene_profesion = 1;
		}
		i++;
	}
	return tiene_profesion;
}

void cargar_fecha(Fecha * fecha){

	printf("Dia: ");
	scanf("%d",&(fecha->dia));
	while((fecha->dia) < 0 || (fecha->dia) > 32){
		printf("Dia incorrecto vuelva a ingresar: ");
		printf("Dia: ");
		scanf("%d",&(fecha->dia));
	}
	printf("Mes: ");
	scanf("%d",&(fecha->mes));
	while((fecha->mes) < 0 || (fecha->mes) > 13){
		printf("Mes incorrecto vuelva a ingresar: ");
		printf("Mes: ");
		scanf("%d",&(fecha->mes));
	}
	printf("Anio: ");
	scanf("%d",&(fecha->anio));
	while((fecha->anio) < 1900 || (fecha->anio > 2012)){
		printf("Anio incorrecto vuelva a ingresar: ");
		printf("Anio: ");
		scanf("%d",&(fecha->anio));
	}
	
}

int validar_cuil(char * ingreso) {
	char cuil[CUIL];
	int i, tipo, dni, verificador, suma = 0;
	const int base[10] = {5, 4, 3, 2, 7, 6, 5, 4, 3, 2 };
	
	for (i=0; i < 14; i++) {
		if (i == 2 || i == 11) {
			if (ingreso[i] != '-')
				return -2;
		} else if (i == 13) {
			if (ingreso[i] != '\0')
				return -2;
		} else if (!isdigit(ingreso[i])) {
			return -2;
		}
	}
	
	for (i=0; i<2; i++) {
		cuil[i] = ingreso[i];
	}
	cuil[i] = '\0';
	
	tipo = atoi(cuil);
	if ( tipo != 20 && tipo != 23 && tipo != 27)
		return -2;
	
	strncat(cuil, ingreso + 3, 8);
	dni = atoi(cuil + 2);
	
	for (i=0; i < 10; i++){
		suma += (cuil[i] - '0') * base[i];
	}
	
	verificador = 11 - (suma % 11);
	if (verificador == 11) 
		verificador = 0;
	else {
		if (verificador == 10)
			verificador = 9;
	}
	
	if ((int) (ingreso[12] - '0') == verificador)
		return dni;
	else
		return -2;
}

int cantidad_de_registros(FILE * usuarios) {
	/** Retorna la cantidad de registros existentes y ubica el puntero al final
	    del archivo para realizar una escritura.
	*/
	fseek(usuarios, 0, SEEK_END);
	return ftell(usuarios)/sizeof(Usuario);
}

void usuario_estadisticas(void) {
	Usuario usuario;
	FILE * usuarios; 
		
	int mayor_cantidad_de_partidas = -1;
	char jugador_cantidad_de_partidas[] = "jugador_cantidad_de_partidas";
	
	char jugador_cantidad_de_ganados[] = "jugador_cantidad_de_ganados";
	int cantidad_de_ganados = 0;
	
	int mayor_puntaje = -1;
	char jugador_mayor_puntaje[] = "jugador_mayor_puntaje";
	
	// int mayor_puntaje_solicito = 3;
	
	int total_completos = 0;
	int completos_ingenieros = 0;
	int completos_abogados = 0;
	int completos_contadores = 0;

	usuarios = fopen(USUARIOS, "rb");
	
	if (usuarios == NULL)
		printf("El archivo no se pudo abrir.");
	else {
		while (fread(&usuario, sizeof(Usuario), 1, usuarios)) {
//			printf("%2i - %2i - %2i - %2i\n", usuario.num_usuario,
//				usuario.partidas_jugadas, usuario.mayor_puntaje, usuario.crucigramas_completos);
			if (usuario.partidas_jugadas > mayor_cantidad_de_partidas) {
				mayor_cantidad_de_partidas = usuario.partidas_jugadas;
				strcpy(jugador_cantidad_de_partidas, usuario.nombre);
			}
			// TODO: if mayor puntaje tiene empate.
			if (usuario.mayor_puntaje > mayor_puntaje) {
				mayor_puntaje = usuario.mayor_puntaje;
				strcpy(jugador_mayor_puntaje, usuario.nombre);
			}
			if (usuario.crucigramas_completos > cantidad_de_ganados) {
				cantidad_de_ganados = usuario.crucigramas_completos;
				strcpy(jugador_cantidad_de_ganados, usuario.nombre);
			}
			total_completos += usuario.crucigramas_completos;
			if (!strcmp(usuario.profesion, "abogado")) {
				completos_abogados += usuario.crucigramas_completos;
			} else if (!strcmp(usuario.profesion, "contador")) {
				completos_contadores += usuario.crucigramas_completos;
			} else if (!strcmp(usuario.profesion, "ingeniero")) {
				completos_ingenieros += usuario.crucigramas_completos;
			}
				
		}
		fclose(usuarios);
	}
	
	printf("(*) El jugador que mas veces jugo crucigramas es: %s.\n", jugador_cantidad_de_partidas);
	if (cantidad_de_ganados > 0) {
		printf("\n(*) El jugador que mas veces obtuvo un puntaje perfecto, es decir, 75 puntos es %s.\n", jugador_cantidad_de_ganados);
		printf("\n(*) La cantidad de curcigramas completos son: %i\n", total_completos);
		printf("\n(*)Dentro de los crucigrgamas completos podemos detallar:\n");
		printf("\n(*) Del total de crucigramas completos %.2f%% son de abogados\n", (float) completos_abogados / total_completos * 100);
		printf("\n(*) Del total de crucigramas completos %.2f%% son de contadores\n", (float) completos_contadores / total_completos * 100);
		printf("\n(*) Del total de crucigramas completos %.2f%% son de ingenieros\n", (float) completos_ingenieros / total_completos * 100);
		
	} else {
		printf("\n(*) El jugador que obtuvo el puntaje mas alto en el juego es: %s\n", jugador_mayor_puntaje);
		printf("\n(*) Su mayor puntaje es %d\n", mayor_puntaje); /*El mayor punaje del usuario que pide las estadisticas*/
	}
}

void usuario_cargar_puntaje(Usuario usuario, const int puntaje) {
	FILE * usuarios; 
	usuarios = fopen(USUARIOS, "rb+");
	if (usuarios != NULL) {
		fseek(usuarios, (usuario.num_usuario - 1) * sizeof(Usuario), SEEK_SET);
		usuario.partidas_jugadas++;
		if (puntaje==75)
			usuario.crucigramas_completos++;
		if (usuario.mayor_puntaje < puntaje)
			usuario.mayor_puntaje = puntaje;
		fwrite(&usuario, sizeof(Usuario), 1, usuarios);
		fclose(usuarios);
	} else {
		printf("No se pudo abrir el archivo...");
	}
}

void usuario_cabecera(const Usuario usuario) {
	if (usuario.num_usuario == -1)
		printf("Usuario no registrado - [%s]\n", usuario.nombre);
	else
		printf("Usuario registrado: %s %s, %d, %s\n\n", 
		usuario.nombre, usuario.apellido, usuario.dni, 
		usuario.profesion);
}


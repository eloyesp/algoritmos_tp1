#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define  TAM 13
#define  CUIL 15

int profesion_valida(const char profesion[]);
void cargar_fecha(Fecha * fecha);
int validar_cuil(char * ingreso);
int cantidad_de_registros(FILE * usuarios);

void usuario_alta() {
	FILE * usuarios;
	Usuario nuevo_usuario;
	char ingreso[MAX_NOMBRE];

	usuarios = fopen("usuarios.dat", "ab+");
	
	if (usuarios != NULL) {
		// Ingreso de datos
		printf("Ingrese la profesion: ");
		read_line(nuevo_usuario.profesion, MAX_NOMBRE);
		printf("Ingrese Nombre: ");
		read_line(nuevo_usuario.nombre, MAX_NOMBRE);
		printf("Apellido: ");
		read_line(nuevo_usuario.apellido, MAX_NOMBRE);
		printf("DNI: ");
		read_line(ingreso, MAX_NOMBRE);
		nuevo_usuario.dni = atoi(ingreso);
		printf("Fecha de nacimiento:\n");
		cargar_fecha(&nuevo_usuario.nacimiento);
		printf("Fecha de ingreso al colegio:\n");
		cargar_fecha(&nuevo_usuario.inscripcion);
		nuevo_usuario.num_usuario = cantidad_de_registros(usuarios) + 1;
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

int usuario_login(void){
	char ingreso[CUIL];
	int usuario;
	printf("Ingrese el numero de CUIL (Ej. 99-99999999-99): ");
	read_line(ingreso, CUIL);
	usuario = validar_cuil(ingreso);
	return usuario;
}

int profesion_valida(const char profesion[]) {
	int bien = 0, i = 0;
	const char * profesiones[] = { "contador", "abogado", "ingeniero"};
	
	while (!bien && i < 3) {
		if (!strcmp(profesion, profesiones[i])) {
			bien = 1;
		}
		i++;
	}
	return bien;
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

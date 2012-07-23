#include "usuario.h"
#include <stdio.h>
#include <string.h>

int usuario_alta(void){
	FILE * usuarios;
	Usuario nuevo_usuario;
	char input, * profesiones[] = { "contador", "abogado", "ingeniero"};
	
	usuarios = fopen("usuarios.dat", "w+");
	
	printf("Ingrese la profesion: ");
	gets(input);
	
	if (profesion_valida()) {
		if ( usuarios == NULL)
			printf("No se pudo abrir el archivo.");
		else {
			printf("Ingrese Nombre, Apellido, DNI, Fecha de nacimiento, Fecha de ingreso al Colegio");
			fscanf(stdin, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%s",
				nuevo_usuario.nombre,
				nuevo_usuario.apellido,
				&nuevo_usuario.dni,
				&nuevo_usuario.nacimiento.dia,
				&nuevo_usuario.nacimiento.mes,
				&nuevo_usuario.nacimiento.anio,
				&nuevo_usuario.inscripcion.dia,
				&nuevo_usuario.inscripcion.mes,
				&nuevo_usuario.inscripcion.anio);
			strcpy(input, nuevo_usuario.profesion);
			fseek(usuarios, (nuevo_usuario.dni - 1) * sizeof(Usuario), SEEK_SET);
			fwrite(&nuevo_usuario, sizeof(Usuario), 1, usuarios);
		}	
		fclose(usuarios);
		return 1;
	}
	else
		printf("No puede cargar sus datos. Recuerde que para registrarse tiene que ser Contador, Abogado o Ingeniero.");
	return 0;
}

int  usuario_login(void){
	// retorna un numero de usuario
	// (-1): no registrado
	// (-2): cuil invalido
	printf("Ingrese el numero de CUIL:en este formato 99-99999999-99");
	scanf("%s", NULL);
	return(0);
}

int profesion_valida() {
	return 1;
	// !strcmp(alta.profesion,profesion1)
}

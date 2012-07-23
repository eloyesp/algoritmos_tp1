#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int usuario_alta(void){
	FILE * usuarios;
	Usuario nuevo_usuario;
	char input[MAX_NOMBRE], * profesiones[] = { "contador", "abogado", "ingeniero"};
	
	usuarios = fopen("usuarios.dat", "wb+");
	
	printf("Ingrese la profesion: ");
	read_line(input, MAX_NOMBRE);
	strcpy(input, nuevo_usuario.profesion);
	
	if (profesion_valida()) {
		if ( usuarios == NULL)
			printf("No se pudo abrir el archivo.");
		else {
			printf("Ingrese Nombre: ");
			read_line(nuevo_usuario.nombre, MAX_NOMBRE);
			printf("Apellido: ");
			read_line(nuevo_usuario.apellido, MAX_NOMBRE);
			printf("DNI: ");
			scanf("%d",&nuevo_usuario.dni);
			printf("Fecha de nacimiento:\n");
			printf("Dia: ");
			scanf("%d",&nuevo_usuario.nacimiento.dia);
			printf("Mes: ");
			scanf("%d",&nuevo_usuario.nacimiento.mes);
			printf("Anio: ");
			scanf("%d",&nuevo_usuario.nacimiento.anio);
			printf("Fecha de ingreso al colegio:\n");
			printf("Dia: ");
			scanf("%d",&nuevo_usuario.inscripcion.dia);
			printf("Mes: ");
			scanf("%d",&nuevo_usuario.inscripcion.mes);
			printf("Anio: ");
			scanf("%d",&nuevo_usuario.inscripcion.anio);
			nuevo_usuario.num_usuario = 0;	
			
			fseek(usuarios, (nuevo_usuario.num_usuario) * sizeof(Usuario), SEEK_SET);
			fwrite(&nuevo_usuario, sizeof(Usuario), 1, usuarios);
			printf("Enhorabuena, ha sido registrado: %s, %i",
				nuevo_usuario.nombre,
				nuevo_usuario.num_usuario);
			//system("pause");
		}	
		fclose(usuarios);
		return 1;
	}
	else
		printf("No puede cargar sus datos. Recuerde que para registrarse tiene que ser Contador, Abogado o Ingeniero.");
	return(0);
}

int  usuario_login(void){
	// retorna un numero de usuario
	// (-1): no registrado
	// (-2): cuil invalido
	char ingreso[15];
	printf("Ingrese el numero de CUIL:en este formato 99-99999999-99: ");
	read_line(ingreso, 15);
	return(-1);
}

int profesion_valida() {
	
	return 1;
	// !strcmp(alta.profesion,profesion1)
}

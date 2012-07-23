#include "usuario.h"
#include <stdio.h>
#include <string.h>
#define MAX 40
#define VEC 100
int usuario_alta(void){
FILE *F;
	F=fopen("usuarios.dat","w+");
	
	Usuario alta;
	char cadena,profesion1={'c','o','n','t','a','d','o','r'},profesion2={'a','b','o','g','a','d','o'},profesion3={'i','n','g','e','n','i','e','r','o'};
	printf("Ingrese la profesion:");
	gets(cadena);
	
	if(!strcmp(alta.profesion,profesion1) || !strcmp(alta.profesion,profesion2) || !strcmp(alta.profesion,profesion3)){
		if(F == NULL)
			printf("No se pudo abrir el archivo.");
		else
			{
				printf("Ingrese Nombre, Apellido, DNI, Fecha de nacimiento, Fecha de ingreso al Colegio");
				fscanf(stdin,"%s,%s,%d,%d,%d,%d,%d,%d,%d,%s",alta.nombre,alta.apellido,&alta.dni,&alta.nacimiento.dia,&alta.nacimiento.mes,&alta.nacimiento.anio,&alta.inscripcion.dia,alta.inscripcion.mes,&alta.inscripcion.anio);
				alta.profesion=cadena;
				fseek(F,(alta.dni - 1)*sizeof(alta),SEEK_SET);
				
				fwrite(& alta,sizeof(alta),1,F);
				
			}
	fclose(F);
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
scanf()

}

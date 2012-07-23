#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#define  TAM 13
#define  MAX 11

int profesion_valida(const char profesion[], const char * profesiones[] );

int usuario_alta(void){
	FILE * usuarios;
	Usuario nuevo_usuario;
	char input[MAX_NOMBRE], * profesiones[] = { "contador", "abogado", "ingeniero"};
	
	usuarios = fopen("usuarios.dat", "wb+");
	
	printf("Ingrese la profesion: ");
	read_line(input, MAX_NOMBRE);
	strcpy(nuevo_usuario.profesion, input);
	if ( usuarios == NULL)
		printf("No se pudo abrir el archivo.");
	else {
		if (profesion_valida(input, profesiones)) {
			printf("Ingrese Nombre: ");
			read_line(nuevo_usuario.nombre, MAX_NOMBRE);
			printf("Apellido: ");
			read_line(nuevo_usuario.apellido, MAX_NOMBRE);
			printf("DNI: ");
			scanf("%d",&nuevo_usuario.dni);
			printf("Fecha de nacimiento:\n");
			printf("Dia: ");
			scanf("%d",&nuevo_usuario.nacimiento.dia);
			while(nuevo_usuario.nacimiento.dia < 0 || nuevo_usuario.nacimiento.dia > 32){
				printf("Dia incorrecto vuelva a ingresar: ");
				printf("Dia: ");
				scanf("%d",&nuevo_usuario.nacimiento.dia);
			}
			printf("Mes: ");
			scanf("%d",&nuevo_usuario.nacimiento.mes);
			while(nuevo_usuario.nacimiento.mes < 0 || nuevo_usuario.nacimiento.mes > 13){
				printf("Mes incorrecto vuelva a ingresar: ");
				printf("Mes: ");
				scanf("%d",&nuevo_usuario.nacimiento.mes);
			}
			printf("Anio: ");
			scanf("%d",&nuevo_usuario.nacimiento.anio);
			while(nuevo_usuario.nacimiento.anio < 1900 || nuevo_usuario.nacimiento.anio > 2012){
				printf("Anio incorrecto vuelva a ingresar: ");
				printf("Anio: ");
				scanf("%d",&nuevo_usuario.nacimiento.anio);
			}
			printf("Fecha de ingreso al colegio:\n");
			printf("Dia: ");
			scanf("%d",&nuevo_usuario.inscripcion.dia);
			while(nuevo_usuario.inscripcion.dia < 0 && nuevo_usuario.inscripcion.dia > 32){
				printf("Dia incorrecto vuelva a ingresar: ");
				printf("Dia: ");
				scanf("%d",&nuevo_usuario.inscripcion.dia);
			}
			printf("Mes: ");
			scanf("%d",&nuevo_usuario.inscripcion.mes);
			while(nuevo_usuario.inscripcion.mes < 0 && nuevo_usuario.inscripcion.mes > 13){
				printf("Mes incorrecto vuelva a ingresar: ");
				printf("Mes: ");
				scanf("%d",&nuevo_usuario.inscripcion.mes);
			}
			
			printf("Anio: ");
			scanf("%d",&nuevo_usuario.inscripcion.anio);
			while(nuevo_usuario.inscripcion.anio < 1900 && nuevo_usuario.inscripcion.anio > 2012){
				printf("Anio incorrecto vuelva a ingresar: ");
				printf("Anio: ");
				scanf("%d",&nuevo_usuario.inscripcion.anio);
			}
			nuevo_usuario.num_usuario = 0;	
			
			fseek(usuarios, (nuevo_usuario.num_usuario) * sizeof(Usuario), SEEK_END);
			fwrite(&nuevo_usuario, sizeof(Usuario), 1, usuarios);
			printf("Enhorabuena, ha sido registrado: %s, %i",
				nuevo_usuario.nombre,
				nuevo_usuario.num_usuario);
			PAUSE();
			return 1;
		} else {
			return -1;
		}
		fclose(usuarios);
	}
}		
			

int usuario_login(void){
	char v[TAM], vector[MAX];
	int i,j,numero=0,comparar,aux,vector_control[10]={5,4,3,2,7,6,5,4,3,2},vector_aux[11];
	
	// retorna un numero de usuario
	// (-1): no registrado
	// (-2): cuil invalido
	char ingreso[15];
	printf("Ingrese el numero de CUIL:en este formato 99-99999999-99: ");
	read_line(ingreso, 15);
	return(-1);
//	printf("Ingrese el numero de CUIL (en este formato 99-99999999-99): ");
//	gets(v);
//	
//	if( v[0]!= 2 && (v[1]!= 7 || v[1]!= 0))
//		return -2;
//	
//	j=0;
//	for (i=0; i<TAM; i++){/*aca borro los guiones*/
//		if(i==2 || i==11){
//			i++;
//			vector[j]=v[i];
//		}
//		vector[j]=v[i];
//		j++;
//	}
//	
//	for(i=0;i<MAX;i++){
//		vector_aux[i] = atoi(&vector[i]);
//	}
//	
//	
//	
//	for(i=0;i<10;i++){
//		vector_aux[i]=vector_aux[i]*vector_control[i];
//		numero=numero+vector_aux[i];
//	}
//	
//	aux=numero%11;
//	
//	comparar=11-aux;
//	
//	if(comparar==vector[10]){
//		printf("codigo correcto :)");/*codigo correcto*/
//		return -1; 
//	}
//	else {
//		printf("no es correcto :(");
//		return -2;
//	}
}



int profesion_valida(const char profesion[], const char * profesiones[] ) {
	int bien = 0, i = 0;
	
	while (!bien && i < 3) {
		if (!strcmp(profesion, profesiones[i])) {
			bien = 1;
		}
		i++;
	}
	return bien;
}

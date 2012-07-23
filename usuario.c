#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#define  TAM 13
#define  MAX 11

int profesion_valida(const char profesion[]);
void cargar_fecha(Fecha * fecha);

void usuario_alta(){
	FILE * usuarios;
	Usuario nuevo_usuario;
	char ingreso[MAX_NOMBRE];
	
	usuarios = fopen("usuarios.dat", "wb+");
	
	printf("Ingrese la profesion: ");
	read_line(ingreso, MAX_NOMBRE);
	strcpy(nuevo_usuario.profesion, ingreso);
	if ( usuarios == NULL)
		printf("No se pudo abrir el archivo.");
	else if (profesion_valida(ingreso)) { 
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
		
		nuevo_usuario.num_usuario = 0;	
		
		fseek(usuarios, (nuevo_usuario.num_usuario) * sizeof(Usuario), SEEK_END);
		fwrite(&nuevo_usuario, sizeof(Usuario), 1, usuarios);
		printf("Enhorabuena, ha sido registrado: %s, %i",
			nuevo_usuario.nombre,
			nuevo_usuario.num_usuario);
		PAUSE();
	}
	fclose(usuarios);
}		


int usuario_login(void){
	char v[TAM], vector[MAX];
	int i,j,numero=0,comparar,aux,vector_control[10]={5,4,3,2,7,6,5,4,3,2},vector_aux[11];
	
	// retorna un numero de usuario
	// (-1): no registrado
	// (-2): cuil invalido
	char ingreso[15];
	printf("Ingrese el numero de CUIL(Ej. 99-99999999-99): ");
	read_line(ingreso, 15);
	
	return(-1);
	
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

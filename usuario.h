#ifndef USUARIO_H
#define USUARIO_H
#define MAX 40
#define VEC 100

typedef struct{
	int dia,mes,anio;
}Fecha;

typedef struct {
	char nombre[MAX],apellido[MAX];
	int dni;
	Fecha nacimiento,inscripcion;
	char profesion[MAX];
}Usuario;

int usuario_alta(void);
// retorna 0 en caso de error.

int  usuario_login(void);
// retorna un numero de usuario
// (-1): no registrado
// (-2): cuil invalido
int usuario_cargar_puntaje(const int nro_usuario, const int puntaje);
// retorna 0 en caso de error.
void usuario_estadisticas(void);
#endif

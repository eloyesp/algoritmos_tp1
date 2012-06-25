# Crucigrama #

En la aplicacion se presenta al usuario un crucigrama simplificado con palabras
de solo 3 y 4 letras. El sistema cuenta con cuentas de usuario y requiere el
ingreso de un numero de cuil válido para jugar.

## Menu principal ##

Está codificado en la función menu (en main.c) y permite ir a las diferentes
funciones del programa.

## TDA Usuario ##

Se implementan la siguiente interface pública:

``` c
int usuario_alta(void);
// retorna 0 en caso de error.
int  usuario_login(void);
// retorna un numero de usuario
// (-1): no registrado
// (-2): cuil invalido
int usuario_cargar_puntaje(const int nro_usuario, const int puntaje);
// retorna 0 en caso de error.
void usuario_estadisticas(void)
// Imprime en pantalla las estadisticas correspondientes.
```

Esto está implementado en los archivos usuario.c y usuario.h

## TDA PalyDef ##

Se implementan la siguiente interface pública:

``` c
void palydef_inicializar(void);
void palydef_elegir_palabras(int * respuestas[][2]);
char * palydef_definicion(const int palabra);
int palydef_coincide(char * palabra, int respuesta);
//(n): esta bien (n = cantidad de puntos)
//(0): esta mal (carga las estadísticas!)
void palydef_estadisticas(void);
```


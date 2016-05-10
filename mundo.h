#ifndef HDR_H
#define HDR_H
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 

/* Tamaño del array regular bidimensaional */
#define TAM_ARRAY 50
/* Número de iteraciones */
#define ITERACION 9
//Definición de colores:
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* Definición de funciones */
//Imprime menú inicio.
int menuInicio(int width, int high);

//Inicializa el tablero con el número de celulas dadas por user
void inicializarTablero(bool *array, int numCelulas, int width, int high);

//Inicializa el tablero a 0s (celulas muertas)
void establecerA0Tablero(bool *array, int width, int high);

//Para imprimir el tablero;
void imprimeTablero(bool *array, int width, int high);

//Para analizar el tablero en cada iteración:
void analizarTablero(bool *array, bool *provisional, int width, int high);

//Realiza la comprobación de las condiciones para vivir o morir de una célula:
void comprobarCondiciones(int x, int j, bool *array, bool *provisional, int width, int high);

//Cuenta las células vecinas vivas de otra dada:
int cuentaVecinasVivas(int i, int j, bool *array, int width, int high);

//Para copiar un array en otro:
void copiaArray(bool *array, bool *arrayAcopiar, int width, int high);

//Comprobar si una célula está dentro de los límites:
bool estaDentroLimites(int i, int j, int width, int high);

//Para contar las celulas vivas del mundo:
int contadorCelulasVivas(bool *array, int width, int high);
#endif
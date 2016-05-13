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
//Definición de Estructuras:
struct celula
	{
		int i;
		int j;
		struct celula *siguiente;
	}Celula;
struct listaCelulas
	{
		struct celula *inicio;
		struct celula *fin;
		int tamanio;
	}ListaCelulas;
struct mundo
	{
		struct listaCelulas *celulasVivas;
		struct listaCelulas *celulasNacen;
		struct listaCelulas *celulasMueren;
		int width;
		int high;
	}Mundo;

/* Definición de funciones */
//Imprime menú inicio.
int menuInicio(int width, int high);

//Para comprobar errores de reserva de memoria (1 si da error y 0 e.o.c):
int compruebaError(void *p);

//Libera Mundo:
void mundo_free(struct mundo * mundo);

/*
//Para analizar el tablero en cada iteración:
void analizarTablero(bool *array, bool *provisional, int width, int high);

//Realiza la comprobación de las condiciones para vivir o morir de una célula:
void comprobarCondiciones(int x, int j, bool *array, bool *provisional, int width, int high);

//Cuenta las células vecinas vivas de otra dada:
int cuentaVecinasVivas(int i, int j, bool *array, int width, int high);

//Comprobar si una célula está dentro de los límites:
bool estaDentroLimites(int i, int j, int width, int high);

*/
//Contador de células Vecinas Vivas:
int cuentaVecinasVivas(struct mundo *mundo, int i, int j);

//Comprueba si una celula esta en la lista:
bool estaCelulaEnLista(struct listaCelulas *celulas, int i, int j);

//Imprime mundo:
void imprimeMundo(struct mundo *mundo);

//Reserva memoria para la lista:
struct listaCelulas * inicializaListaCelulas();

//Añade el número de células vivas indicado por el usuario:
void inicializaListaCelulasVivas(struct mundo *mundo, int numCelulas);

//Añade célula a la lista:
int addCelula(struct listaCelulas *celulasVivas, int i, int j);

//Libera memoria y elimina la lista:
void free_lista(struct listaCelulas *celulas);

#endif
#include "mundo.h"

//Comienza el juego preguntando el número de células de las que partir:
int menuInicio(int width, int high)
{
	int num = 0;
	printf("Escoge un número entre 3 y %d: \n", width*high);
	scanf("%4d",&num);
	return num;
}

//Libera memoria y elimina la lista:
void free_lista(struct listaCelulas *celulas)
{	
		struct celula *plista = celulas->inicio;
		if(plista){
			struct celula *celulaSiguiente = celulas->inicio->siguiente;
			free(plista);
			plista = celulaSiguiente;
			while(plista != celulas->inicio){
					celulaSiguiente = plista->siguiente;
					free(plista);
					plista = celulaSiguiente;
			}
		}
		free(celulas);
		printf("%p Libero Célula\n", celulas);
}

//Reserva memoria para la lista:
struct listaCelulas * inicializaListaCelulas()
{
	struct listaCelulas *celulas = (struct listaCelulas *) malloc (sizeof(struct listaCelulas));
	compruebaError(celulas);
	celulas->inicio = NULL;
	celulas->fin = NULL;
	celulas->tamanio = 0;
	return celulas;
}

//Añade el número de células vivas indicado por el usuario:
void inicializaListaCelulasVivas(struct listaCelulas *celulasVivas, int numCelulas, int width, int high)
{	
	//Añadimos la semilla:
	srand (time(NULL));
	//Bucle con valor de iteración igual al número de células: 
	for(int n=0;n< numCelulas;n++){ 
		/* Para obtener un número aleatorio:
		numero = rand () % (N-M+1) + M;   // Este está entre M y N 
		En nuestro caso: Entre 0 y width/high Para obtener dos coordenadas del tablero
		donde introducir las células vivas: */
		
		int i= rand() %  high;
		int j= rand() %  width;
		//Establecemos celula como viva (la añadimos a la lista)
		addCelulaViva(celulasVivas,i,j);
	}
}

//Añade célula a la lista:
void addCelulaViva(struct listaCelulas *celulasVivas, int i, int j)
{
	/* Con esta función añadimos un elemento al final de la lista */
	struct celula *nuevo;
    /* reservamos memoria para el nuevo elemento */
    nuevo = (struct celula *) malloc (sizeof(struct celula));
    compruebaError(nuevo);
    /* ahora metemos el nuevo elemento en la lista. lo situamos
    al final de la lista.comprobamos si la lista está vacía. 
    si primero==NULL es que no hay ningún elemento en la lista. También vale ultimo==NULL */
    if (celulasVivas->inicio == NULL) 
    {
    	 /* el campo siguiente va a ser él mismo por ser el único elemento
         de la lista */
        nuevo->siguiente = celulasVivas->inicio;
        celulasVivas->inicio = nuevo;
        celulasVivas->fin = nuevo;
        celulasVivas->tamanio = 0;        
    }else{
           /* el que hasta ahora era el último tiene que apuntar al nuevo */
           celulasVivas->fin->siguiente = nuevo;
           /* hacemos que el nuevo sea ahora el último */
           celulasVivas->fin = nuevo;
           /* hacemos que el nuevo último apunte su siguiente al primer elemento: */
           celulasVivas->fin->siguiente = celulasVivas->inicio;
           celulasVivas->tamanio++;
    }
}

//Para comprobar errores de reserva de memoria (1 si da error y 0 e.o.c):
int compruebaError(void *p)
{
	if(!p)
		perror("Error al reservar memoria!");
	return p == NULL;

}
/*
//Imprime tablero por consola:
void imprimeTablero(struct listaCelulas *listaCelulas, int width, int high)
{
	for(int i=0; i<high; i++){
		for(int j=0; j<width; j++){
			//printf("Elemento (%d,%d)-> %p\n", j, i, array+i*width+j);
			//Si célula está viva escribimos V:
			if(*(array+i*width+j) == true)
				printf(ANSI_COLOR_YELLOW " V " ANSI_COLOR_RESET);
			//Si está muerta escribimos - :
			else
				printf(ANSI_COLOR_CYAN " - " ANSI_COLOR_RESET);
		}
		//Si llegamos a la última columna nos vamos a la siguiente línea:
		printf(" \n");
	}
	printf("\tLeyenda:\n\t");
	printf(ANSI_COLOR_YELLOW "V: Célula Viva -> Vivas: %d\n" ANSI_COLOR_RESET, listaCelulas->tamanio);
	printf(ANSI_COLOR_CYAN "\t- : Célula Muerta -> Muertas %d\n" ANSI_COLOR_RESET,width*high - listaCelulas->tamanio);
}

//Realiza la iteración:
void analizarTablero(bool *array, bool *provisional, int width, int high)
{
	//Recorremos el array analizando cada célula y sus vecinas:
	for (int i = 0; i < high; i++)
		for(int j = 0; j < width ; j++)
			//Comprobamos las condiciones en cada caso:
			comprobarCondiciones(i,j,array, provisional, width, high);
	//Copiamos provisional en array:
	copiaArray(array, provisional, width, high);
}

//Realiza la comprobación de las vecionas de una célula:
void comprobarCondiciones(int i, int j, bool *array, bool *provisional, int width, int high)
{
	int vecinas = 0;
	/* Sabiendo que cada célula (i,j) tiene máximo 8 lindantes,
	comprobando (i-1,j-1);(i-1,j);(i-1,j+1);(i,j-1); y
	(i,j+1);(i+1,j-1);(i+1,j);(i+1,j+1); 
	bool caso =*(array+i*width+j);
	vecinas = cuentaVecinasVivas(i,j,array, width, high);
	switch(caso){
		//Si está muerta:
		case false:
			//Si tiene 3 vecinas vivas nace:
			if(vecinas == 3){
				*(provisional+i*width+j) = true;
			}
			else
				//Si no tiene 3 vecinas vivas sigue muerta:
				*(provisional+i*width+j) = *(array+i*width+j);
			break;
		//Si está viva:
		case true:
			//Si no tiene 2 o 3 vecinas vivas muere:
			if(!(vecinas >=2 && vecinas <= 3)){
				*(provisional+i*width+j) = false;
			}
			else
				//Si tiene 2 o 3 vecinas vivas sigue viva:
				*(provisional+i*width+j) = *(array+i*width+j);
			break;
	}
	//printf("%p->(%d,%d)->%d Vecinas; ", array+i*width+j, j, i, vecinas);
}

//Contador de células Vecinas Vivas:
int cuentaVecinasVivas(int i, int j, bool *array, int width, int high)
{
	int contador = 0;
	if(estaDentroLimites(i-1, j-1, width, high) && *(array+(i-1)*width+(j-1)))
		contador++;
	if(estaDentroLimites(i-1,j, width, high) && *(array+(i-1)*width+j))
		contador++;
	if(estaDentroLimites(i-1,j+1, width, high) && *(array+(i-1)*width+(j+1)))
		contador++;
	if(estaDentroLimites(i,j-1, width, high) && *(array+i*width+(j-1)))
		contador++;
	if(estaDentroLimites(i,j+1, width, high) && *(array+i*width+(j+1)))
		contador++;
	if(estaDentroLimites(i+1,j-1, width, high) && *(array+(i+1)*width+(j-1)))
		contador++;
	if(estaDentroLimites(i+1,j, width, high) && *(array+(i+1)*width+j))
		contador++;
	if(estaDentroLimites(i+1,j+1, width, high) && *(array+(i+1)*width+(j+1)))
		contador++;
	return contador;
}

//Comprueba que los índices pertenecen al tablero:
bool estaDentroLimites(int i, int j, int width, int high)
{
	return  !(i>=high || i<0 || j>width || j<0);
}
*/
#include "mundo.h"

//Comienza el juego preguntando el número de células de las que partir:
int menuInicio(int width, int high)
{
	int num = 0;
	printf("Escoge un número entre 3 y %d: \n", width*high);
	scanf("%4d",&num);
	return num;
}
//Inicializamos la estructura de la lista con los valores por defecto:
struct listaCelulas inicializaListaCelulas(struct listaCelulas *listaCelulas)
{
	listaCelulas->inicio = NULL;
	listaCelulas->fin = NULL;
	listaCelulas->tamanio = 0;
}

//Añade el número de células vivas indicado por el usuario:
void inicializaListaCelulasVivas(struct celula *celulasVivas, int numCelulas)
{	
	//Añadimos la semilla:
	srand (time(NULL));
	//Bucle con valor de iteración igual al número de células: 
	for(int n=0;n< numCelulas;n++){ 
		/* Para obtener un número aleatorio:
		numero = rand () % (N-M+1) + M;   // Este está entre M y N 
		En nuestro caso: Entre 0 y width/high Para obtener dos coordenadas del tablero
		donde introducir las células vivas: 
		*/
		int i= rand() %  high;
		int j= rand() %  width;
		//Establecemos celula como viva (la añadimos a la lista)
		addCelulaViva(celulasVivas,i,j);
	}
}

void addCelulaViva(struct celula *celulasVivas, int numCelulas)
{
	if(!celulasVivas){

	}else{

	}
}

//Imprime tablero por consola:
void imprimeTablero(bool *array, int width, int high)
{
	int numCelulas = contadorCelulasVivas(array,width,high);
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
	printf(ANSI_COLOR_YELLOW "V: Célula Viva -> Vivas: %d\n" ANSI_COLOR_RESET, numCelulas);
	printf(ANSI_COLOR_CYAN "\t- : Célula Muerta -> Muertas %d\n" ANSI_COLOR_RESET,width*high - numCelulas);
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
	(i,j+1);(i+1,j-1);(i+1,j);(i+1,j+1); */
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
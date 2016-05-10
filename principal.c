#include "mundo.h"

int main(int argc, char **argv)
{
	/* Recogemos los parametros de ancho, alto y lugar opcion */
	int width, high, c; //Ancho y Alto del mundo.
	/* Cadena de caracter que guarda el path del archivo que contiene
	la sesion anteriormente jugada y guardada del mundo */
	char *directorio = "";//la cadena debe ir pegada a d(por consola)
	while((c = getopt( argc, argv, "w:h:d::"))!=-1){
		switch(c){
			case 'w':
				width = strtol(optarg, NULL, 0);
				break;
			case 'h':
				high = strtol(optarg, NULL, 0);
				break;
			case 'd':
				directorio = optarg;
				break;
			default:
				return EXIT_FAILURE;
		}
	}
	if(width < 0 || width > 100)
		width = TAM_ARRAY;
	if(high < 0 || high > 100)
		high = TAM_ARRAY;
	//Preguntamos al usuario para insertar el nº de células inicial
	int numeroCelulasVivas = menuInicio(width, high);
	//Declaramos el Tablero de Células:
	bool *mundo;
	//Declaramos el mundo:
	mundo = (bool *) malloc(width * high * sizeof(bool));
	if(!mundo)
		perror("Error al reservar memoria para mundo.");
	
	//Declaramos las 3 listas: Celulas Vivas, las que van a nacer y morir:
	struct listaCelulas *celulasVivas = NULL;
	struct listaCelulas *celulasNacen = NULL;
	struct listaCelulas *celulassMueren = NULL;
	inicializaListaCelulas(celulasVivas);
	inicializaListaCelulas(celulasNacen);
	inicializaListaCelulas(celulassMueren);
/*
	//Inicializamos tablero:
	inicializarTablero(celulasVivas,numeroCelulasVivas, width, high);
	imprimeTablero(celulasVivas, width, high);
	//Iteramos:
	for(int iteracion = 0; iteracion < ITERACION; iteracion++){
		//Analizamos el tablero y en provisional guardamos los cambios.
		analizarTablero(mundo, provisional, width, high);
		//Imprimimos iteración con su leyenda:
		printf("\tIteración %d: \n\n", iteracion+1);
		imprimeTablero(mundo, width, high);
		printf("\n");
	}
	free(mundo);
	free(provisional);
	*/
	return 0;
}

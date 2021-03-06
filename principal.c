#include "mundo.h"

int main(int argc, char **argv)
{
	/* Recogemos los parametros de ancho, alto y lugar opcion */
	int width, high, c; //Ancho y Alto del mundo.
	/* Cadena de caracter que guarda el path del archivo que contiene
	la sesion anteriormente jugada y guardada del mundo */
	char *directorio = "";//la cadena debe ir pegada a d(por consola)
	struct mundo *mundo = (struct mundo *) malloc(sizeof(struct mundo));
	compruebaError(mundo);
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
	mundo->width = width;
	mundo->high = high;
	//Declaramos las 3 listas: Celulas Vivas, las que van a nacer y morir:
	struct listaCelulas *celulasVivas = inicializaListaCelulas();
	struct listaCelulas *celulasNacen = inicializaListaCelulas();
	struct listaCelulas *celulasMueren = inicializaListaCelulas();
	mundo->celulasVivas = celulasVivas;
	mundo->celulasNacen = celulasNacen;
	mundo->celulasMueren = celulasMueren;
	inicializaListaCelulasVivas(mundo,numeroCelulasVivas);
	imprimeMundo(mundo);
	printf("%d\n", cuentaVecinas(mundo, 0, 0));
	/*
	printf("%p->%d\n",celulasVivas, celulasVivas->tamanio);
	printf("%p->%d\n",celulasNacen, celulasNacen->tamanio);
	printf("%p->%d\n",celulasMueren, celulasNacen->tamanio);
	*/
	mundo_free(mundo);
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
*/
	return 0;
}

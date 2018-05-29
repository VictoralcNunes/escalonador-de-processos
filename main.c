#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){
	TF *fila = cria_fila();

	char str[10]; // Variavel para armazenar o nome do arquivo a ser usado
	printf("Digite o nome do arquivo: ");printf("\n");
	scanf("%s", str);
	fila = armazena(fila, str);

	int timer = 0;

	int in = 1;
	do{



		imprime_fila(&fila);
		printf("\n Press Enter to continue or 0 to quit. ");printf("\n");
		scanf("%d", &in);
	}while(in == 1);

	libera_fila(fila);
	return(0);
}

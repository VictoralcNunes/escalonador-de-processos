#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){
	TF *fila = cria_fila();
	char str[10]; // Variavel para armazenar o nome do arquivo a ser usado

	printf("Digite o nome do arquivo: ");
	scanf("%s", str);
	fila = armazena(fila, "text.txt");
	
	int in = 1;
	while(in){



		imprime_fila(fila);
		printf("Qualquer parada para pular, exceto 0.");
		scanf("%d", &in);
	}

	libera_fila(fila);
	return(0);
}

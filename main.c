#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){
	TF *fila = cria_fila();
	FILE *file;
	file = fopen("text.txt","r");
	fila = armazena(fila, file);
	
	int in = 1;
	while(in){
		
		

		imprime_fila(fila);
		printf("Qualquer parada para pular, exceto 0.");
		scanf("%d", &in);
	}
	

	libera_fila(fila);
	system("pause");
	return(0);
}
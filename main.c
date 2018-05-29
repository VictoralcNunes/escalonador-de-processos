#include <stdio.h>
#include <stdlib.h>
#include "so.c"

int main(){
	
	TF *fila_entrada = cria_fila();
	TF *fila_pronto_real = cria_fila();
	TF *fila_pronto_usuario = cria_fila();
	TF *fila_bloqueado = cria_fila();
	TF *fila_pronto_suspenso = cria_fila();
	TF *fila_bloqueado_suspenso = cria_fila();

	char str[10]; // Variavel para armazenar o nome do arquivo a ser usado
	printf("Digite o nome do arquivo: ");printf("\n");
	scanf("%s", str);
	fila_entrada = armazena(fila_entrada, str);

	int timer = 0;

	int in = 1;
	do{
		imprime_fila(&fila_entrada);
		printf("\n Press Enter to continue or 0 to quit. ");printf("\n");
		scanf("%d", &in);
	}while(in == 1);

	libera_fila(fila_entrada);
	return(0);
	
}

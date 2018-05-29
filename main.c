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

	Recursos* recursos = cria_recursos();

	char str[10]; // Variavel para armazenar o nome do arquivo a ser usado
	printf("Digite o nome do arquivo: ");printf("\n");
	scanf("%s", str);
	
	fila_entrada = armazena(fila_entrada, str);
	
	while(recursos->momento < 100){
			
			
		recursos->momento++;	
	}
	
	
	
	imprime_fila(fila_entrada);
	
	
	

	libera_fila(fila_entrada);
	return(0);
	
}

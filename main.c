#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){

	TF *fila_entrada = cria_fila();
	TF *fila_pronto_real = cria_fila();
	TF *fila_pronto_usuario = cria_fila();
	TF *fila_bloqueado = cria_fila();
	TF *fila_pronto_suspenso = cria_fila();
	TF *fila_bloqueado_suspenso = cria_fila();

	Recursos* recursos = cria_recursos();

	char str[10]; // Variavel para armazenar o nome do arquivo a ser usado
	printf("Digite o nome do arquivo: text.txt");printf("\n");
	scanf("%s", str);

	fila_entrada = armazena(fila_entrada, str);
	char c = '1';
	int timer = 0;
	while((c = getchar()) != '0'){
		printf("--- TEMPO: %d ---\n", timer);
		//	checar recursos-> momento == tempo de entrada do processo na frente da entrada
		//com a função na_entrada
		//	chamar escalonador de entrada dentro de um while que decrementa uma variável
		//que guardou a  o valor de na_entrada, fazendo um pop da entrada

		//	chamar o escalonador de curto prazo. Ele faz a decisão de qual politica vai usar
		//dependendo das filas de prontos

		//	checar se um processo terminou e sem tem como passar um processor suspenso pra pronto

		//	checar se bloqueados e bloqueados suspensos podem voltar a estarem prontos ou prontos
		//suspensos

		//	a cada troca de estado, printar a mudança

		//	a cada momento, printar o estado dos recursos
		print_recursos(&recursos);
		printf("\nTecle Enter para continuar ou 0 para sair.\n");
		recursos->momento++;
		timer++;
	}



	// imprime_fila(fila_entrada);
	libera_fila(fila_entrada);
	return(0);

}

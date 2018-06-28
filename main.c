#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){
	TF *fila_auxiliar = NULL;
	TF *fila_entrada = cria_fila();
	TF *fila_pronto_real = cria_fila();
	TF *fila_pronto_usuario = cria_fila();
	TF *fila_pronto_suspenso = cria_fila();
	TF *fila_bloqueado = cria_fila();
	TF *fila_bloqueado_suspenso = cria_fila();
	Recursos* recursos = cria_recursos();

	char str[10]; // Variavel para armazenar o nome do arquivo
	printf("Digite o nome do arquivo: ");
	scanf("%s", str);
	fila_entrada = armazena(fila_entrada, str);
	fila_auxiliar = fila_entrada;
    TF *procTempo = cria_fila();
	int timer = 0;
	while((str[0] = getchar()) != '0'){
		printf("--- TEMPO %d ---\n", timer);

    	TF *procTempo = cria_fila();
		// While para checar se o tempo_de_chegada é igual ao timer
		while(fila_auxiliar != NULL){
			if(fila_auxiliar->processo->tempo_de_chegada == timer){
				escalonadordeentrada(fila_pronto_real,
														fila_pronto_usuario,
														fila_pronto_suspenso,
														fila_bloqueado,
														fila_bloqueado_suspenso,
														recursos,
														fila_auxiliar->processo);
				procTempo = ins_proc_ord(procTempo,fila_auxiliar->processo);
			}
			fila_auxiliar = fila_auxiliar->prox;
		}
		escalonadorCurtoReal(procTempo,recursos);
		// Checar recursos->momento == processo->tempo_de_chegada na frente da entrada com a função na_entrada

		// Chamar escalonador de entrada dentro de um while que decrementa uma variável
		//que guardou a  o valor de na_entrada, fazendo um pop da entrada

		//	chamar o escalonador de curto prazo. Ele faz a decisão de qual politica vai usar
		//dependendo das filas de prontos

		//	checar se um processo terminou e sem tem como passar um processor suspenso pra pronto


		//	checar se bloqueados e bloqueados suspensos podem voltar a estarem prontos ou prontos
		//suspensos



		//	a cada troca de estado, printar a mudança
		print_estado(fila_entrada,
								fila_pronto_real,
								fila_pronto_usuario,
								fila_pronto_suspenso,
								fila_bloqueado,
								fila_bloqueado_suspenso);
		//	a cada momento, printar o estado dos recursos
		fila_auxiliar = fila_entrada;
		recursos->momento++;
		if(filas_vazias(fila_entrada, 
						fila_pronto_real,
						fila_pronto_usuario,
						fila_pronto_suspenso,
						fila_bloqueado,
						fila_bloqueado_suspenso)){
							return 0;
						}
		timer++;
	}

	imprime_fila(fila_entrada);
	libera_fila(fila_entrada);
	return(0);
}

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

	int timer = 0;
	while((str[0] = getchar()) != '0'){
		printf("--- TEMPO %d ---\n", timer);
        TF *procTempo = cria_fila();
		// While para checar se o tempo_de_chegada é igual ao timer
		while(fila_auxiliar != NULL){
			if(fila_auxiliar->processo->tempo_de_chegada == timer){
				printf("Processo %d CHEGOU\n", fila_auxiliar->processo->numero);
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

		if (fila_pronto_real->processo->tempo_restante==0 || fila_pronto_usuario->processo->tempo_restante==0){
			if (checa_disponibilidade(recursos, fila_pronto_suspenso->processo)){
				escalonadorMedioVolta (fila_pronto_suspenso, fila_pronto_usuario);
			}
		}


		//	checar se bloqueados e bloqueados suspensos podem voltar a estarem prontos ou prontos
		//suspensos

		// if (checa_disponibilidade(recursos, fila_bloqueado->processo)){
		// 	escalonadorMedioVolta(fila_bloqueado, fila_pronto_usuario);
		// }
		// if (checa_disponibilidade(recursos, fila_bloqueado_suspenso->processo)){
		// 	escalonadorMedioVolta(fila_bloqueado_suspenso, fila_pronto_suspenso);
		// }





		//	a cada troca de estado, printar a mudança
		// print_estado(fila_entrada,
		// 						fila_pronto_real,
		// 						fila_pronto_usuario,
		// 						fila_pronto_suspenso,
		// 						fila_bloqueado,
		// 						fila_bloqueado_suspenso);
		//	a cada momento, printar o estado dos recursos
		//print_recursos(&recursos);
		//printf("\nTecle Enter para continuar ou 0 para sair.\n");
		fila_auxiliar = fila_entrada;
		recursos->momento++;
		timer++;
	}

	imprime_fila(fila_entrada);
	libera_fila(fila_entrada);
	return(0);
}

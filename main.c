#include <stdio.h>
#include <stdlib.h>
#include "so.h"

int main(){
	Processo *processo = NULL;
	TF *fila = cria_fila();
	//int batata;
	int x;
	FILE *file;
	file = fopen("text.txt","r");
	while (!feof(file)){
	processo = cria_processo(0,0,0,0,0,0,0,0);	
	fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d ", 
		&processo->tempo_de_chegada, 
		&processo->prioridade, 
		&processo->tempo_de_processador,
		&processo->memoria,
		&processo->impressoras,
		&processo->scanners,
		&processo->modens,
		&processo->cds);
	/*fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d,",&batata);
	printf("%d\n", batata);
	fscanf(file,"%d",&batata);
	printf ("%d\n", batata);
	*/
	//fila =ins_proc_ord(fila,processo);
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", 
		processo->tempo_de_chegada, 
		processo->prioridade, 
		processo->tempo_de_processador,
		processo->memoria,
		processo->impressoras,
		processo->scanners,
		processo->modens,
		processo->cds);
	

	free(processo);
	/*if(!fscanf(file,"%d",&batata)){
		printf("achei erro\n");
		break;
	}*/
	x++;
	printf("\t%d\n",x);
	}
	imprime_fila(fila);
	//libera_fila(fila);

	/*
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", 
		processo->tempo_de_chegada, 
		processo->prioridade, 
		processo->tempo_de_processador,
		processo->memoria,
		processo->impressoras,
		processo->scanners,
		processo->modens,
		processo->cds);
	

	*/
	fclose(file);
	system("pause");
	return(0);
}
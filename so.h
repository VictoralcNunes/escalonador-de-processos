#include <stdio.h>
#include <stdlib.h>
#ifndef SO_H
#define SO_H
typedef struct Processo{
    int tempo_de_chegada;
    int prioridade;
    int tempo_de_processador;
    int memoria;
    int impressoras;
    int scanners;
    int modens;
    int cds;
}Processo;

typedef struct TipoFila{
    Processo *processo;
    struct TipoFila *prox;
}TF;

Processo* cria_processo(int tc, int p, int tp, int mem, int i, int sc, int mod, int cds);
void mata_processo(Processo *processo);
TF* cria_fila();
TF* cria_elem(Processo *processo);
TF* ins_proc_ord(TF *fila, Processo *processo);
void imprime_fila(TF *fila);
void libera_fila(TF *fila);

#endif

#include <stdio.h>
#include <stdlib.h>
#ifndef SO_H
#define SO_H

typedef struct Processo{
    int numero;
    int tempo_de_chegada;
    int prioridade;
    int tempo_de_processador;
    int memoria;
    int impressoras;
    int scanners;
    int modens;
    int cds;
    int nomeEst;
    int tempo_restante;
}Processo;

typedef struct TipoFila{
    Processo *processo;
    struct TipoFila *prox;
}TF;

typedef struct NoTempo{
    int index;
    Processo *processo;
    int impressoras; //2
    int scanners;//1
    int modens;//2
    int cd;//1
    int cpu;//3 cpu usuário
    int cpur;//1 cpu tempo real
    int memoria;
    struct NoTempo *prox;
}NoTempo;

Processo* cria_processo(int tc, int p, int tp, int mem, int i, int sc, int mod, int cds);
void mata_processo(Processo *processo);
TF* cria_fila();
TF* cria_elemento(Processo *processo);
TF* ins_proc_ord(TF *fila, Processo *processo);
void imprime_fila(TF **fila);
void libera_fila(TF *fila);

void escalonadordeentrada(TF* tfr, TF* tu, Processo* proc);
Processo* entrada(TF* te);
Processo* copia_processo(Processo* proc);
TF *armazena(TF *fila, char *str);

#endif

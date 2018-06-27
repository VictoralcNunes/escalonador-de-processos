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
    int tempo_restante;
    int cpuAloc;
}Processo;
typedef struct Recursos{
    int momento;
    int memoria;
    int cpu1;
    int cpu2;
    int cpu3;
    int cpu4;
    int impressoras;
    int scanners;
    int modens;
    int cds;
}Recursos;
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
void imprime_fila(TF *fila);
void libera_fila(TF *fila);

*Processo removerProcesso(TF *entrada,int processoID)
void escalonadordeentrada(TF* tfr, TF* tu, TF* susp, TF* bloq, TF* bloqs, Recursos* rec, Processo* proc);
Processo* entrada(TF* fe, int tempo);
Processo* pop_processo(TF* fila);
TF *armazena(TF *fila, char *str);
int na_entrada(TF* fila, int tempo);
void escalonadorMedio(TF *origem, TF *fim);
void escalonadorMedioVolta(TF *origem, TF *fim);
void escalonadorCurtoReal(TF *pronto, Recursos *pc);
void escalonadorCurtoFeedback(TF *pronto,Recursos *pc);
int alocarProc(Processo *proc,Recursos *pc);
void alocar(Processo *proc,Recursos *pc);
void Exec(TF *fila,Recursos *pc);
Recursos* cria_recursos();
int checa_disponibilidade(Recursos* recursos, Processo* p);
//PEDRO
void print_processo(Processo *);
void print_recursos(Recursos **);
void print_estado(TF*, TF*, TF*, TF*, TF*, TF*);

#endif

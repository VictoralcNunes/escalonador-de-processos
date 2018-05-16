#include <stdio.h>
#include <stdlib.h>

typedef struct Processo{
    int tempo_de_chegada;
    int prioridade;
    int tempo_de_processador;
    int memoria;
    int impressoras;
    int scanners;
    int modems;
    int cds;
}Processo;

typedef struct TipoFila{
    Processo* processo;
    struct TipoFila* prox;
}TF;

Processo* cria_processo(int tc, int p, int tp, int mem, int i, int sc, int mod, int cds){
    Processo* processo = (Processo*)malloc(sizeof(Processo));
    processo->tempo_de_chegada = tc;
    processo->prioridade = p;
    processo->tempo_de_processador = tp;
    processo->memoria = mem;
    processo->impressoras = i;
    processo->scanners = sc;
    processo->modems = mod;
    processo->cds = cds;
    return processo;
}

void mata_processo(Processo* p){
    free(p);
    return;
}

TF* cria_fila(){
    return NULL;
}

TF* cria_elem(Processo* p){
    TF* novo = (TF*)malloc(sizeof(TF));
    novo->prox = NULL;
    novo->processo = p;
    return novo;
}

TF* ins_proc_ord(TF* f, Processo* p){
    if(!f){
        return cria_elem(p);
    }
    else{
        TF* g;
        TF* novo = cria_elem(p);
        if(g->processo->tempo_de_chegada > p->tempo_de_chegada 
        || g->processo->tempo_de_chegada == p->tempo_de_chegada && g->processo->prioridade > p->prioridade){
            novo->prox = f;
            return novo;
        }else{
            TF* frente = g->prox;
            while(g->processo->tempo_de_chegada > p->tempo_de_chegada){
                if(!frente){
                    g->prox = novo;
                    return f;
                }
                g = g->prox;
                frente = g->prox;
            }
            g->prox = novo;
            return f;
        }
    }
}

void imprime_fila(TF* f){
    if(!f){
        printf("fim\n");
    }else{
        printf("%d -> ", f->processo->tempo_de_chegada);
        imprime_fila(f->prox);
    }
}
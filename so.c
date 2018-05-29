#include <stdio.h>
#include <stdlib.h>
#include "so.h"

Processo* cria_processo(int tc, int p, int tp, int mem, int i, int sc, int mod, int cds){
    Processo* processo = (Processo*)malloc(sizeof(Processo));
    processo->tempo_de_chegada = tc;
    processo->prioridade = p;
    processo->tempo_de_processador = tp;
    processo->memoria = mem;
    processo->impressoras = i;
    processo->scanners = sc;
    processo->modens = mod;
    processo->cds = cds;
    processo->tempo_restante = 0;
    return processo;
}
Processo* pop_processo(TF* fila){
    if(!fila) return NULL;
    TF* aux = fila, *aux2;
    aux2 = fila->prox;
    Processo* proc = fila->processo;
    Processo* copia = cria_processo(proc->tempo_de_chegada,
                                    proc->prioridade, 
                                    proc->tempo_de_processador,
                                    proc->memoria,
                                    proc->impressoras,
                                    proc->scanners,
                                    proc->modens,
                                    proc->cds);
    copia->numero = proc->numero;
    copia->tempo_restante = proc->tempo_restante;
    fila = aux2;
    free(aux);
    return copia;
}

void mata_processo(Processo *processo){
    free(processo);
    return;
}

TF* cria_fila(){
    return NULL;
}

TF* cria_elemento(Processo* processo){
    TF* novo = (TF*)malloc(sizeof(TF));
    novo->prox = NULL;
    novo->processo = processo;
    return novo;
}

TF* ins_proc_ord(TF* fila, Processo* processo){
    if(!fila){ //se a fila está vazia
        return cria_elemento(processo);
    }
    else{
        TF* g = fila;
        TF* novo = cria_elemento(processo);

        if(g->processo->tempo_de_chegada > processo->tempo_de_chegada
        || g->processo->tempo_de_chegada == processo->tempo_de_chegada
            && g->processo->prioridade > processo->prioridade){ // se o processo deve ser o primeiro da fila
            novo->prox = fila;
            return novo;
        }else{
            TF* frente = g->prox;
            while(frente){
                if(frente->processo->tempo_de_chegada > processo->tempo_de_chegada
                || (frente->processo->tempo_de_chegada == processo->tempo_de_chegada
                && frente->processo->prioridade > processo->prioridade)){ // se o processo está no meio da fila
                    g->prox = novo;
                    novo->prox = frente;
                    return fila;
                }
                g = g->prox;
                frente = g->prox;
            }
            g->prox = novo; // se o processo é o último
            return fila;
        }
    }
}

void imprime_fila(TF **fila){
    if((*fila) == NULL){
        printf("Fim\n");
    }else{
        printf("Processo %d \n", (*fila)->processo->numero);
        printf("Tempo de Chegada: %d \n", (*fila)->processo->tempo_de_chegada);
        printf("Prioridade: %d \n", (*fila)->processo->prioridade);
        printf("Tempo de Processador: %d \n", (*fila)->processo->tempo_de_processador);
        printf("Memória: %d \n", (*fila)->processo->memoria);
        printf("Impressoras: %d \n", (*fila)->processo->impressoras);
        printf("Scanners: %d \n", (*fila)->processo->scanners);
        printf("Modens: %d \n", (*fila)->processo->modens);
        printf("CD's: %d \n", (*fila)->processo->cds);
        printf("------------------------------------------------\n");
        (*fila) = (*fila)->prox;
        imprime_fila(&(*fila));
    }
}
void libera_fila(TF *fila){
    if (!fila){
        TF *proxNo, *atual;
        atual = fila->prox;

        while (!atual){
            proxNo = atual->prox;
            free(atual);
            atual = proxNo;
        }
    }
}

TF *armazena(TF *fila, char *str){
    int numproc = 0;
    Processo *processo = NULL;

    FILE *file;
    file = fopen(str,"r");
    while (!feof(file)){
        processo = cria_processo(0,0,0,0,0,0,0,0);
        processo->numero = numproc;
        fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d ",
            &processo->tempo_de_chegada,
            &processo->prioridade,
            &processo->tempo_de_processador,
            &processo->memoria,
            &processo->impressoras,
            &processo->scanners,
            &processo->modens,
            &processo->cds);
        processo->tempo_restante = processo->tempo_de_processador;
        fila = ins_proc_ord(fila, processo);
        numproc++;
    }
    fclose(file);
    return(fila);
}

void escalonadordeentrada(TF* tfr, TF* tu, Processo* proc){
    if(!proc->prioridade){
        tfr = ins_proc_ord(tfr, proc);
    }
    else{
        tu = ins_proc_ord(tu, proc);
    }
}


int na_entrada(TF* fila, int tempo){//retorna a quantidade de jobs que entraram no tempo indicado
    if(!fila){
        return 0;
    }
    int qtd = 0;
    if(fila->processo->tempo_de_chegada == tempo){
        qtd++;
        return qtd += na_entrada(fila->prox, tempo);
    }
    else return 0;
}
// Processo* entrada(TF* te){
//     if(!te) return NULL;

//     Processo *entra = copia_processo(te->processo);
//     //colocar pop em te
// }


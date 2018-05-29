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
    processo->nomeEst = 0;
    processo->tempo_restante = 0;
    return processo;
}
Processo* copia_processo(Processo* proc){
    if(!proc) return NULL;
    Processo* copia = cria_processo(proc->tempo_de_chegada,
                                    proc->prioridade, 
                                    proc->tempo_de_processador,
                                    proc->memoria,
                                    proc->impressoras,
                                    proc->scanners,
                                    proc->modens,
                                    proc->cds);
    copia->numero = proc->numero;
    copia->nomeEst = proc->nomeEst;
    copia->tempo_restante = proc->tempo_restante;
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

void imprime_fila(TF* f){
    if(!f){
        printf("fim\n");
    }else{
        printf("Processo %d -> ", f->processo->numero);
        imprime_fila(f->prox);
    }
}
void libera_fila(TF *f){
    if (!f){
        TF *proxNo, *atual;
        atual = f->prox;

        while (!atual){
            proxNo = atual->prox;
            free(atual);
            atual = proxNo;
        }
    }
}

TF *armazena(TF *fila, FILE *file){
    int numproc =0;
    Processo *processo = NULL;
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
        fila = ins_proc_ord(fila,processo);
        // printf("Processo %d: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", 
        //  processo->numero,
        //  processo->tempo_de_chegada, 
        //  processo->prioridade, 
        //  processo->tempo_de_processador,
        //  processo->memoria,
        //  processo->impressoras,
        //  processo->scanners,
        //  processo->modens,
        //  processo->cds);
        // //free(processo);
        numproc++;
    }
    fclose(file);
    return(fila);
}

void escalonadordeentrada(TF* tfr, TF* tu, Processo *proc){
    if(!proc->prioridade){
        tfr = ins_proc_ord(tfr, proc);
    }
    else{
        tu = ins_proc_ord(tu, proc);
    }
}

Processo* entrada(TF* te){
    if(!te) return NULL;

    Processo *entra = copia_processo(te->processo);
    //colocar pop em te
}


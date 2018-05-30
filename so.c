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

void imprime_fila(TF *fila){
    if((fila) == NULL){
        printf("Fim\n");
    }else{
        TF* p = fila;
        printf("Processo %d \n", p->processo->numero);
        printf("Tempo de Chegada: %d \n", p->processo->tempo_de_chegada);
        printf("Prioridade: %d \n", p->processo->prioridade);
        printf("Tempo de Processador: %d \n", p->processo->tempo_de_processador);
        printf("Memória: %d \n", p->processo->memoria);
        printf("Impressoras: %d \n", p->processo->impressoras);
        printf("Scanners: %d \n", p->processo->scanners);
        printf("Modens: %d \n", p->processo->modens);
        printf("CD's: %d \n", p->processo->cds);

        printf("------------------------------------------------\n");
        p = p->prox;
        imprime_fila(p);
    }
}

void libera_fila(TF *fila){
    if(!fila) return;
    else{
        free(fila);
        libera_fila(fila->prox);
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

void escalonadordeentrada(TF* tfr, TF* tu, TF* susp, TF* bloq, TF* bloqs, Recursos* rec, Processo* proc){
    //escalona os processos que chegam para as filas de prontos
    if(checa_disponibilidade(rec, proc)){
        if(!proc->prioridade){
            tfr = ins_proc_ord(tfr, proc);
            printf("Processo %d na fila de processos prontos tempo real", proc->nome);
        }
        else{
            tu = ins_proc_ord(tu, proc);
            //acho que os processos em tu devem entrar diferente já que ele usa feedback...
            printf("Processo %d na fila de processos prontos de usuário", proc->nome);
        }
        rec->memoria -= proc->memoria;
    }
    else{
        if(!bloq && !tu){
            susp = ins_proc_ord(susp, proc);
            printf("Processo %d na fila de processos prontos suspensos", proc->nome);
        }
        else{
            if(!proc->prioridade){
                if(bloq){
                    //escalonador medio bloq->bloqs
                }
                if(tu){
                    //escalonador medio tu->susp
                }  
                escalonadordeentrada(tfr, tu, susp, bloq, bloqs, rec, proc);
            }
            else{
                susp = ins_proc_ord(susp, proc);
                printf("Processo %d na fila de processos prontos suspensos", proc->nome);
            }
        }
    }

    return;
}


int na_entrada(TF* fila, int tempo){
    //retorna a quantidade de jobs que entraram no tempo indicado
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
Processo* entrada(TF* fe, int tempo){
    if(!fe) return NULL;
    Processo *entra = pop_processo(fe);
    return entra;
}
//Gabriel
void escalonadorCurtoReal(TF *pronto, Recursos *pc){
    if(!pronto){
        //checando para ver se tem algo errado
        printf("Fila vazia.\n Checar inconsistencia\n");
        return;
    }
    /*int menor = pronto->processo->tempo_de_chegada;
    TF *aux1 = pronto;
    // procurando o menor tempo de chegada
    while (aux1){
       if (aux1->processo->tempo_de_chegada>menor){
            menor = aux1->processo->tempo_de_chegada;
            aux1=aux1->prox;
       }
    }
    // acessando o processo sem alterar nossa fila
    // escolha arbitraria pq FIFO não tem critério de desempate explicito
    TF *aux2 = pronto;
    while (aux2->processo->tempo_de_chegada!=menor){
        aux2 = aux2->prox;
    }
    if((aux2->processo->memoria)>(pc->memoria)){
        printf("Deu erro\n");
        return;
    }
    */

    printf("Executa processo %d\n", pronto->processo->numero);
    pc->cpu1--;
    pc->memoria= (pc->memoria) - (pronto->processo->memoria);
    pronto->processo->tempo_restante--;
    if((pronto->processo->tempo_restante)==0){
        printf("Processo %d terminado. Tempo da maquina: %d", pronto->processo->numero, pc->momento);
        pop_processo(pronto);
        
    }

}


// AMANCO

Recursos* cria_recursos(){
    Recursos* novo = (Recursos*)malloc(sizeof(Recursos));
    novo->momento = 0;
    novo->memoria = 8192;
    novo->cpu1 = 1;
    novo->cpu2 = 1;
    novo->cpu3 = 1;
    novo->cpu4 = 1;
    novo->impressoras = 2;
    novo->scanners = 1;
    novo->modens = 1;
    novo->cds = 2;
    return novo;
}

int checa_disponibilidade(Recursos* recursos, Processo* p){
    if(recursos->memoria >= p->memoria &&
        recursos->impressoras >= p->impressoras &&
        recursos->scanners >= p->scanners &&
        recursos->cds >= p->cds &&
        recursos->modens >= p->modens){
            return 1;
    }
    return 0;
}

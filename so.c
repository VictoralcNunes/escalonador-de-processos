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
            //printf("Processo %d na fila de processos prontos tempo real\n", proc->numero);
        }
        else{
            tu = ins_proc_ord(tu, proc);
            //acho que os processos em tu devem entrar diferente já que ele usa feedback...
            //printf("Processo %d na fila de processos prontos de usuário\n", proc->numero);
        }
        rec->memoria -= proc->memoria;
    }
    else{
        if(!bloq && !tu){
            susp = ins_proc_ord(susp, proc);
            //printf("Processo %d na fila de processos prontos suspensos\n", proc->numero);
        }
        else{
            if(!proc->prioridade){
                if(bloq){
                    //escalonador medio bloq->bloqs
                    escalonadorMedio(bloq,bloqs);
                }
                if(tu){
                    //escalonador medio tu->susp
                    escalonadorMedio(tu,susp);
                }
                escalonadordeentrada(tfr, tu, susp, bloq, bloqs, rec, proc);
            }
            else{
                susp = ins_proc_ord(susp, proc);
                //printf("Processo %d na fila de processos prontos suspensos\n", proc->numero);
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
void escalonadorMedio(TF *origem, TF *fim){
    int maiorPrioridade = origem->processo->prioridade;
    TF* aux;
    aux = origem;
    while (aux){
        if(aux->processo->prioridade>maiorPrioridade) maiorPrioridade = aux->processo->prioridade;
        aux = aux->prox;
    }
    aux = origem;
    while(aux->processo->prioridade!=maiorPrioridade){
            aux = aux->prox;
    }
    fim = ins_proc_ord(fim,pop_processo(aux));
    //ins_proc_ord(fim,pop_processo(aux));
    // TF *transferidor = pop_processo(aux);

    //fim = ins_proc_ord(fim,transferidor->processo);
}
void escalonadorMedioVolta(TF *origem, TF *fim){
    printf("entrei nesse método\n");
    if(origem==NULL||fim==NULL) return;
<<<<<<< HEAD
=======

>>>>>>> e43608f1354cfbb39804c63799cc8911acb1b39e
    int menorPrioridade = origem->processo->prioridade;
    TF* aux;
    aux = origem;
    while (aux){
      printf("%d\n",menorPrioridade);
    }
    while (aux!=NULL){
        if(aux->processo->prioridade<menorPrioridade) menorPrioridade = aux->processo->prioridade;
        aux = aux->prox;
    }
    aux = origem;
    while(aux->processo->prioridade!=menorPrioridade){
            aux = aux->prox;
    }
    printf("%d\n",menorPrioridade);
    ins_proc_ord(fim,pop_processo(aux));
    //ins_proc_ord(fim,pop_processo(aux));
    // TF *transferidor = pop_processo(aux);

    //fim = ins_proc_ord(fim,transferidor->processo);
}
void escalonadorCurtoReal(TF *pronto, Recursos *pc){
    /*if(!pronto){
        //checando para ver se tem algo errado
        printf("Fila vazia.\n Checar inconsistencia\n");
        return;
    }*/
    int numCPU;
    if(pc->cpu1+pc->cpu2+pc->cpu3+pc->cpu4==0){
        printf("Não existe CPU disponível\n");
        //caso seja obrigatorio liberar esse espaço de memoria para usar o cpu criaremos um metodo que retorna o CPU liberado
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
    if(pc->cpu1==1){pc->cpu1--;numCPU =1;}
    else{
<<<<<<< HEAD
    if(pc->cpu2==1){pc->cpu2--;numCPU =2;}
    else{
    if(pc->cpu3==1){pc->cpu3--;numCPU =3;}

    }

    if(pc->cpu4==1){pc->cpu4--;numCPU =4;}

    }
=======
    	if(pc->cpu2==1){pc->cpu2--;numCPU =2;}
    	else{
    		if(pc->cpu3==1){pc->cpu3--;numCPU =3;}
    		else{
    			if(pc->cpu4==1){pc->cpu4--;numCPU =4;}
    		}
		}    
	}
>>>>>>> 003873b58686d96c0cf3ddbdd5533f61b5a4ad90
    pc->memoria= (pc->memoria) - (pronto->processo->memoria);
    pronto->processo->tempo_de_processador--;
    if(numCPU==1) pc->cpu1++;
    if(numCPU ==2)pc ->cpu2++;
    if(numCPU==3) pc ->cpu3++;
    if(numCPU==4) pc->cpu4++;
    if((pronto->processo->tempo_de_processador)==0){
        printf("Processo %d terminou de executar em: %d", pronto->processo->numero, pc->momento);

        pop_processo(pronto);

    }

	}
void escalonadorCurtoFeedback(TF *pronto,Recursos *pc){
    int menorPrioridade = pronto->processo->prioridade;
    TF *aux= pronto;
    while (aux!=NULL){
        if(aux->processo->prioridade<menorPrioridade){
            menorPrioridade = aux->processo->prioridade;
        }
        aux = aux->prox;
    }
    TF *prioritarios = cria_fila();
    aux = pronto;
    while(aux!=NULL){
        if(aux->processo->prioridade==menorPrioridade){
            prioritarios = ins_proc_ord(prioritarios,aux->processo);
        }
        aux = aux->prox;
    }
    if(prioritarios->prox==NULL){
        //Método para ver se aquele recurso está sendo usado
        if(alocarProc(prioritarios->processo,pc)){
            printf("O processo %d está sendo executado\n", prioritarios->processo->numero);
            prioritarios->processo->tempo_restante--;
                if(prioritarios->processo->tempo_restante==0){
                    printf("Processo %d terminado\n", prioritarios->processo->numero);
                    pop_processo(prioritarios);
                }
        }
    return;
    }

    int menorTempo = prioritarios->processo->tempo_restante;
    aux = prioritarios;
    while(aux!=NULL){
        if(aux->processo->tempo_restante<menorTempo){
            menorTempo = aux->processo->tempo_restante;
        }
        aux = aux->prox;
    }
    aux = prioritarios;
    while(aux->processo->tempo_restante!=menorTempo){
        aux= aux->prox;
    }
    if(alocarProc(aux->processo,pc)){
            printf("O processo %d está sendo executado\n", aux->processo->numero);
            aux->processo->tempo_restante--;
                if(aux->processo->tempo_restante==0){
                    printf("Processo %d terminado\n", aux->processo->numero);
                    //pop_processo(prioritarios);
                }
        }

    return ;
}
int alocarProc(Processo *proc,Recursos *pc){
    if(pc->cpu1+pc->cpu2+pc->cpu3+pc->cpu4==0){
        printf("Não tem CPU disponível\n");
        return(0);
    }
    if(pc->cpu1==1)pc->cpu1--;
    if(pc->cpu2==1)pc->cpu2--;
    if(pc->cpu3==1)pc->cpu3--;
    if(pc->cpu4==1)pc->cpu4--;
    if(proc->impressoras==1){
        if(pc->impressoras==0){
        //processo sem recurso disponivel
            printf("Recurso Indisponível\n");
            return(1);
        }
        //processo tinha recurso disponivel
        pc->impressoras--;
        return 1;
    }
    if(proc->scanners==1){
        if(pc->scanners==0){
        //processo sem recurso disponivel
            printf("Recurso Indisponível\n");
            return(0);
        }
        //processo tinha recurso disponivel
        pc->scanners--;
        return(1);
    }
    if(proc->modens==1){
        if(pc->modens==0){
        //processo sem recurso disponivel
            printf("Recurso Indisponível\n");
            return(0);
        }
        //processo tinha recurso disponivel
        pc->modens--;
        return(1);
    }
    if(proc->cds==1){
        if(pc->cds==0){
        //processo sem recurso disponivel
            printf("Recurso Indisponível\n");
            return(1);
        }
        //processo tinha recurso disponivel
        pc->cds--;
        return(1);
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
    return(novo);
}
int checa_disponibilidade(Recursos* recursos, Processo* p){
    if(p==NULL) return (0);
    if(recursos->memoria >= p->memoria &&
        recursos->impressoras >= p->impressoras &&
        recursos->scanners >= p->scanners &&
        recursos->cds >= p->cds &&
        recursos->modens >= p->modens){
            return(1);
    }
    return(0);
}

// PEDRO
void print_processo(Processo *processo){
  if(processo){
    printf("\n");
    printf("|-------------------------|\n");
    printf("| Processo %d              |\n", processo->numero);
    printf("|-------------------------|\n");
    printf("| Tempo de Chegada: %d     |\n", processo->tempo_de_chegada);
    printf("| Prioridade: %d           |\n", processo->prioridade);
    printf("| Tempo de Processador: %d |\n", processo->tempo_de_processador);
    printf("| Memória: %d            |\n", processo->memoria);
    printf("| Impressoras: %d          |\n", processo->impressoras);
    printf("| Scanners: %d             |\n", processo->scanners);
    printf("| Modens: %d               |\n", processo->modens);
    printf("| CD's: %d                 |\n", processo->cds);
    printf("|-------------------------|\n");
  }
}
void print_recursos(Recursos **recurso){
  printf("\n");
  printf("|--- RECURSOS ---|\n");
  printf("| Memória: %d  |\n", (*recurso)->memoria);
  printf("| CPU1: %d        |\n", (*recurso)->cpu1);
  printf("| CPU2: %d        |\n", (*recurso)->cpu2);
  printf("| CPU3: %d        |\n", (*recurso)->cpu3);
  printf("| CPU4: %d        |\n", (*recurso)->cpu4);
  printf("| Impressoras: %d |\n", (*recurso)->impressoras);
  printf("| Scanners: %d    |\n", (*recurso)->scanners);
  printf("| Modens: %d      |\n", (*recurso)->modens);
  printf("| CD's: %d        |\n", (*recurso)->cds);
  printf("|----------------|\n");
}
void print_estado(TF* fe,TF* fpr,TF *fpu,TF* fps,TF* fb,TF* fbs){
  if(fe != NULL){ // fila_entrada
    printf("\nFila de Entrada: Processo");
    while(fe != NULL){
      printf(" %d ", fe->processo->numero);
      fe = fe->prox;
    }
  }if(fpr != NULL){ // fila_pronto_real
    printf("\nFila Pronto Real: Processo");
    while(fpr != NULL){
      printf(" %d ", fpr->processo->numero);
      fpr = fpr->prox;
    }
  }if(fpu != NULL){ // fila_pronto_usuario
    printf("\nFila Pronto Usuario: Processo");
    while(fpu != NULL){
      printf(" %d ", fpu->processo->numero);
      fpu = fpu->prox;
    }
  }if(fps != NULL){ // fila_pronto_suspenso
    printf("\nFila Pronto Suspenso: Processo");
    while(fps != NULL){
      printf(" %d ", fps->processo->numero);
      fps = fps->prox;
    }
  }if(fb != NULL){ // fila_bloqueado
    printf("\nFila Bloqueado: Processo");
    while(fb != NULL){
      printf(" %d ", fb->processo->numero);
      fb = fb->prox;
    }
  }if(fbs != NULL){ // fila_bloqueado_suspenso
    printf("\nFila Bloqueado Suspenso: Processo");
    while(fe != NULL){
      printf(" %d ", fbs->processo->numero);
      fbs = fbs->prox;
    }
  }
}

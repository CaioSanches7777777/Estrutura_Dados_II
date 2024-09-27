#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1

struct NO{
    int valor;
    int cor;
    struct NO *esq, *dir, *pai;
};

typedef struct NO NO;

NO *criarNo(int valor){
    NO *novoNo = (NO *)malloc(sizeof(NO));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    novoNo->esq = novoNo->dir = novoNo->pai = NULL;
    return novoNo;
}

void rotacaoEsq(NO **raiz, NO *no){
    NO *aux = no->dir;
    no->dir = aux->esq;
    if (aux->esq != NULL){
        aux->esq->pai = no;
    }
    aux->pai = no->pai;
    if (no->pai == NULL){
        *raiz = aux;
    }else if (no == no->pai->esq){
        no->pai->esq = aux;
    }else{
        no->pai->dir = aux;
    }
    aux->esq = no;
    no->pai = aux;
}

void rotacaoDir(NO **raiz, NO *no){
    NO *aux = no->esq;
    no->esq = aux->dir;
    if (aux->dir != NULL){
        aux->dir->pai = no;
    }
    aux->pai = no->pai;
    if (no->pai == NULL){
        *raiz = aux;
    }else if (no == no->pai->dir){
        no->pai->dir = aux;
    }else{
        no->pai->esq = aux;
    }
    aux->dir = no;
    no->pai = aux;
}

void corrigirViolacao(NO **raiz, NO *subárvore){
    while (subárvore != *raiz && subárvore->pai->cor == VERMELHO){
        if (subárvore->pai == subárvore->pai->pai->esq){
            NO *aux = subárvore->pai->pai->dir;
            if (aux != NULL && aux->cor == VERMELHO){
                subárvore->pai->cor = PRETO;
                aux->cor = PRETO;
                subárvore->pai->pai->cor = VERMELHO;
                subárvore = subárvore->pai->pai;
            }else{
                if (subárvore == subárvore->pai->dir){
                    subárvore = subárvore->pai;
                    rotacaoEsq(raiz, subárvore);
                }
                subárvore->pai->cor = PRETO;
                subárvore->pai->pai->cor = VERMELHO;
                rotacaoDir(raiz, subárvore->pai->pai);
            }
        }else{
            NO *aux = subárvore->pai->pai->esq;
            if (aux != NULL && aux->cor == VERMELHO){
                subárvore->pai->cor = PRETO;
                aux->cor = PRETO;
                subárvore->pai->pai->cor = VERMELHO;
                subárvore = subárvore->pai->pai;
            }else{
                if (subárvore == subárvore->pai->esq){
                    subárvore = subárvore->pai;
                    rotacaoDir(raiz, subárvore);
                }
                subárvore->pai->cor = PRETO;
                subárvore->pai->pai->cor = VERMELHO;
                rotacaoEsq(raiz, subárvore->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void inserir(NO **raiz, int valor){
    NO *subárvore = criarNo(valor);
    NO *aux = NULL;
    NO *no = *raiz;

    while (no != NULL){
        aux = no;
        if (subárvore->valor < no->valor){
            no = no->esq;
        }else{
            no = no->dir;
        }
    }
    subárvore->pai = aux;
    if (aux == NULL){
        *raiz = subárvore;
    }else if (subárvore->valor < aux->valor){
        aux->esq = subárvore;
    }else{
        aux->dir = subárvore;
    }
    corrigirViolacao(raiz, subárvore);
}

void printPreO(struct NO* raiz){
  if(raiz != NULL){
    printf("%i ",raiz->valor);
    printPreO(raiz->esq);
    printPreO(raiz->dir);
  }
}
void printEmO(struct NO* raiz){
  if(raiz != NULL){
    printEmO(raiz->esq);
    printf("%i ",raiz->valor);
    printEmO(raiz->dir);
  }
}
void printPosO(struct NO* raiz){
  if(raiz != NULL){
    printPosO(raiz->esq);
    printPosO(raiz->dir);
    printf("%i ",raiz->valor);
  }
}
void printOrdem(struct NO* raiz){
  printf("\n--------------------------------------\nPré-ordem:\n");
  printPreO(raiz);
  printf("\n--------------------------------------\nEm ordem:\n");
  printEmO(raiz);
  printf("\n--------------------------------------\nPós-ordem:\n");
  printPosO(raiz);
  printf("\n--------------------------------------\n\n");
}

void imprimeGrafoEmOrdem(struct NO* raiz, int nivel_NO){  // EmOrdem
  int i;
  //printf("\n%i",nivel);

  if(raiz == NULL){
    return;
  }

  if(raiz != NULL){

    //if((*raiz)->dir != NULL && (*raiz)->esq != NULL){}

    if((*raiz).dir != NULL){
      //printf("\t\n/\r");
      printf("\t");
      imprimeGrafoEmOrdem((*raiz).dir,nivel_NO+1);
      printf("\n");

      for(i=0;i<nivel_NO+2;i++){ // não funciona (n sei pq)
        printf("\t");
      }
      printf("\b/\n");
    }

    printf("\r%d\t",nivel_NO); // tem que printar esse "\r" pra voltar para o inicio da linha antes de dar o parágrafo que põe o nó na posição certa
    for(i=0;i<nivel_NO;i++){ 
      printf("\t");
    }
    if((*raiz).cor == 0){
        printf("(%dr)",(*raiz).valor);
    }else if((*raiz).cor == 1){
        printf("[%db]",(*raiz).valor);
    }

    if((*raiz).esq != NULL){
      //printf("\t\n|");
      printf("\n");

      for(i=0;i<nivel_NO+2;i++){ // não funciona (n sei pq)
        printf("\t");
      }
      printf("\b\\\n");

      imprimeGrafoEmOrdem((*raiz).esq,nivel_NO+1);
    }

  }
}



int main(){
    struct NO *raiz = NULL;
    int i,N=10, dados[10]={12, 31, 20, 17, 11, 8, 3, 24, 15, 33};
    
    for (i = 0; i < 10; i++){
        inserir(&raiz, dados[i]);
    }
    printf("\n");
    printOrdem(raiz);
    imprimeGrafoEmOrdem(raiz, 0);

    return 0;
}




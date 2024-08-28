#include <stdio.h>
#include <stdlib.h>

struct NO{
  int info;
  struct NO *esq;
  struct NO *dir;
};


struct NO* criaNO(int dado){
  struct NO* novoNO = (struct NO*) malloc(sizeof(struct NO));
  if(novoNO == NULL){
    return 0;
  }

  novoNO->info = dado;
  novoNO->esq = NULL;
  novoNO->dir = NULL;
  
  return novoNO;
}

struct NO* insere(struct NO* raiz, int dado){
  if(raiz == NULL){//se a raiz não existir
    raiz = criaNO(dado);
  }else{
     if(dado <= raiz->info){
       raiz->esq = insere(raiz->esq, dado);
     }else{
       raiz->dir = insere(raiz->dir, dado);
     }
  }
  return raiz;
}

void printPreO(struct NO* raiz){
  if(raiz != NULL){
    printf("%i ",raiz->info);
    printPreO(raiz->esq);
    printPreO(raiz->dir);
  }
}
void printEmO(struct NO* raiz){
  if(raiz != NULL){
    printEmO(raiz->esq);
    printf("%i ",raiz->info);
    printEmO(raiz->dir);
  }
}
void printPosO(struct NO* raiz){
  if(raiz != NULL){
    printPosO(raiz->esq);
    printPosO(raiz->dir);
    printf("%i ",raiz->info);
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

    if((*raiz).esq != NULL){
      //printf("\t\n/\r");
      printf("\t");
      imprimeGrafoEmOrdem((*raiz).esq,nivel_NO+1);
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
    printf("%d",(*raiz).info);

    if((*raiz).dir != NULL){
      //printf("\t\n|");
      printf("\n");

      for(i=0;i<nivel_NO+2;i++){ // não funciona (n sei pq)
        printf("\t");
      }
      printf("\b\\\n");
    
      imprimeGrafoEmOrdem((*raiz).dir,nivel_NO+1);
    }

  }
}

struct NO* MinDir(struct NO* raiz){
    struct NO* atual = raiz;
    while (atual->esq != NULL)
    {
        atual = atual->esq;
    }
    return atual;
}

struct NO* MaiEsq(struct NO* raiz){
    struct NO* atual = raiz;
    while (atual->esq != NULL)
    {
        atual = atual->dir;
    }
    return atual;
}

struct NO* excluir(struct NO* raiz, int valor){
  
  if(valor < raiz->info){
    raiz->esq = excluir(raiz->esq,valor);
    
  }else if(valor > raiz->info){
    raiz->dir = excluir(raiz->dir, valor);
  }else{
    if(raiz->esq == NULL){
      struct NO* temp = raiz->dir;
      free(raiz);
      return temp;
    }else if(raiz->dir == NULL){
      struct NO* temp = raiz->esq;
      free(raiz);
      return temp;
    }
    struct NO* temp = MinDir(raiz->dir);
    raiz->info = temp->info;
    raiz->dir = excluir(raiz->dir, temp->info);
  }
  
  return raiz;
}

int main(){
  int i,N=10, dados[10]={5,2,3,7,9,6,1,8,4,10};
  //int i,N=11, dados[11]={12,10,15,6,11,14,20,1,8,13,16};
  /*
                       5
                    /     \
                  2         7
                /   \     /   \
               1     3   6     9
                      \      /   \
                       4    8     10
  */

  struct NO *raiz = NULL;
  for(i=0;i<N;i++){
    raiz = insere(raiz, dados[i]);
  }
  printOrdem(raiz);
  imprimeGrafoEmOrdem(raiz,0);
  
  excluir(raiz, 3);
  printf("\n\n\n\n\n\n\n\n");
  imprimeGrafoEmOrdem(raiz,0);
  printf("\n\n\n\n\n\n\n\n");
  printOrdem(raiz);
  
  return 0;
}

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
    printPreO(raiz->esq);
    printf("%i ",raiz->info);
    printPreO(raiz->dir);
  }
}
void printPosO(struct NO* raiz){
  if(raiz != NULL){
    printPreO(raiz->esq);
    printPreO(raiz->dir);
    printf("%i ",raiz->info);
  }
}
void printOrdem(struct NO* raiz){
  printf("\n--------------------------------------\n");
  printPreO(raiz);
  printf("\n--------------------------------------\n");
  printEmO(raiz);
  printf("\n--------------------------------------\n");
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

int main(){
  int i,N=10, dados[10]={5,2,3,7,9,6,1,8,4,10};
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
  
  return 0;
}

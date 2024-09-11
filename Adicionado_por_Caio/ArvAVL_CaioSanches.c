#include <stdio.h>
#include <stdlib.h>

struct NO{
  int info;
  struct NO *esq;
  struct NO *dir;
  int alt;
};


struct NO* criaNO(int info){
  struct NO* novoNO = (struct NO*) malloc(sizeof(struct NO));
  if(novoNO == NULL){
    return 0;
  }

  novoNO->info = info;
  novoNO->esq = NULL;
  novoNO->dir = NULL;
  novoNO->alt = 0;    //

  return novoNO;
}

int altura(struct NO *no){
  if (no == NULL)
    return -1;      
  return no->alt; 
}

int fatorBalanceamento(struct NO *no){
  if (no == NULL)
    return 0; 
  return altura(no->esq) - altura(no->dir);
}

struct NO* rotacaoDir(struct NO *no){
  struct NO *novaRaiz = no->esq;       
  struct NO *subArvore = novaRaiz->dir; 

  novaRaiz->dir = no;   
  no->esq = subArvore; 


  if (altura(no->esq) > altura(no->dir)) 
    no->alt = 1 + altura(no->esq);      
  else
    no->alt = 1 + altura(no->dir); 
  if (altura(novaRaiz->esq) > altura(novaRaiz->dir)) 
    novaRaiz->alt = 1 + altura(novaRaiz->esq);      
  else
    novaRaiz->alt = 1 + altura(novaRaiz->dir); 

  return novaRaiz; 
}

struct NO* rotacaoEsq(struct NO *no){
  struct NO *novaRaiz = no->dir;         
  struct NO *subArvore = novaRaiz->esq; 

  novaRaiz->esq = no; 
  no->dir = subArvore; 

  if (altura(no->esq) > altura(no->dir)) 
    no->alt = 1 + altura(no->esq);      
  else
    no->alt = 1 + altura(no->dir); 
  if (altura(novaRaiz->esq) > altura(novaRaiz->dir)) 
    novaRaiz->alt = 1 + altura(novaRaiz->esq);      
  else
    novaRaiz->alt = 1 + altura(novaRaiz->dir); 

  return novaRaiz; 
}

struct NO* balanceamento(struct NO *raiz, int info){
  if (raiz == NULL){
    return raiz;
  }
  if (altura(raiz->esq) > altura(raiz->dir)){
    raiz->alt = 1 + altura(raiz->esq); 
  }else{
    raiz->alt = 1 + altura(raiz->dir); 
  }
  int balanceamento = fatorBalanceamento(raiz); 

  if (balanceamento > 1 && info < raiz->esq->info) 
    return rotacaoDir(raiz);                      

  if (balanceamento < -1 && info > raiz->dir->info) 
    return rotacaoEsq(raiz);                     

  if (balanceamento > 1 && info > raiz->esq->info){
    raiz->esq = rotacaoEsq(raiz->esq); 
    return rotacaoDir(raiz);              
  }

  if (balanceamento < -1 && info < raiz->dir->info){
    raiz->dir = rotacaoDir(raiz->dir); 
    return rotacaoEsq(raiz);                  
  }

  return raiz; 
}

struct NO* insere(struct NO* raiz, int info){
  if(raiz == NULL){//se a raiz não existir
    raiz = criaNO(info);
  }else{
     if(info <= raiz->info){
       raiz->esq = insere(raiz->esq, info);
     }else{
       raiz->dir = insere(raiz->dir, info);
     }
  }
  return balanceamento(raiz, info);
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
    printf("%d",(*raiz).info);

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

struct NO* encontrarMinimo(struct NO* no){
  struct NO *atual = no;

  while (atual && atual->esq != NULL)
    atual = atual->esq;
  return atual;
}

struct NO* encontrarMaximo(struct NO* no) {
  if (no == NULL)
    return NULL;

  while (no->dir != NULL) {
    no = no->dir;
  }
  return no;
}

struct NO* excluir(struct NO *raiz, int valor) {
  if (raiz == NULL){
    return raiz;
  }

  if (valor < raiz->info){
    raiz->esq = excluir(raiz->esq, valor); 
  }else if (valor > raiz->info){
    raiz->dir = excluir(raiz->dir, valor); 
  }else{
    if (raiz->esq == NULL){
      struct NO *temp = raiz->dir; 
      free(raiz);                        
      return temp;                        
    }else if (raiz->dir == NULL){
      struct NO *temp = raiz->esq; 
      free(raiz);                         
      return temp;                        
    }

    if (altura(raiz->esq) >= altura(raiz->dir)) {

      struct NO *temp = encontrarMaximo(raiz->esq); 
      raiz->info = temp->info;                              
      raiz->esq = excluir(raiz->esq, temp->info); 
    }else{   
      struct NO *temp = encontrarMinimo(raiz->dir); 
      raiz->info = temp->info;  
      raiz->dir = excluir(raiz->dir, temp->info);   
    }
  }
  return balanceamento(raiz, valor);
}

int main(){
  //int i,N=5, dados[5]={50,70,60,40,30};
  int i,N=21, dados[21]={50,1,64,12,18,66,38,95,58,59,70,68,39,62,7,60,43,16,67,34,35};

  struct NO *raiz = NULL;
  for(i=0;i<N;i++){
    raiz = insere(raiz, dados[i]);
  }
  printOrdem(raiz);
  imprimeGrafoEmOrdem(raiz,0);
  printf("\n\n-----------------------\n\n");
  
  excluir(raiz, 50);
  //excluir(raiz, 95);
  excluir(raiz, 70);
  excluir(raiz, 60);
  excluir(raiz, 35);


  imprimeGrafoEmOrdem(raiz,0);
  printf("\n\n-----------------------\n\n");

  return 0;
}

/*
struct NO *encontrarMinimo(struct NO *no){
  struct NO *atual = no;

  while (atual && atual->esq != NULL)
    atual = atual->esq;
  return atual;
}

struct NO* encontrarMaximo(struct NO* no) {
  if (no == NULL)
    return NULL;

  while (no->dir != NULL) {
    no = no->dir;
  }
  return no;
}

struct NO *excluir(struct NO *raiz, int valor) {
  if (raiz == NULL){
    return raiz;
  }

  if (valor < raiz->info){
    raiz->esq = excluir(raiz->esq, valor); 
  }else if (valor > raiz->info){
    raiz->dir = excluir(raiz->dir, valor); 
  }else{
    if (raiz->esq == NULL){
      struct NO *temp = raiz->dir; 
      free(raiz);                        
      return temp;                        
    }else if (raiz->dir == NULL){
      struct NO *temp = raiz->esq; 
      free(raiz);                         
      return temp;                        
    }

    if (altura(raiz->esq) >= altura(raiz->dir)) {

      struct NO *temp = encontrarMaximo(raiz->esq); 
      raiz->info = temp->info;                              
      raiz->esq = excluir(raiz->esq, temp->info); 
    }else{   
      struct NO *temp = encontrarMinimo(raiz->dir); 
      raiz->info = temp->info;  
      raiz->dir = excluir(raiz->dir, temp->info);   
    }
  }
  return balanceamento(raiz, valor);
}
*/

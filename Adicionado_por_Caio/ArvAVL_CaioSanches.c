#include <stdio.h>
#include <stdlib.h>

struct NO {
  int valor;
  int alt;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *AVL;

struct NO* criaNO(int info){
  struct NO* novoNO = (struct NO*) malloc(sizeof(struct NO));
  if(novoNO == NULL){
    return 0;
  }

  novoNO->valor = info;
  novoNO->esq = NULL;
  novoNO->dir = NULL;
  novoNO->alt = 0;    //alterado para AVL

  return novoNO;
}


struct NO *maiorDir(struct NO *no) {
  if (no == NULL){
    return no;
  }
  struct NO *aux;

  if (no->dir != NULL){
    return maiorDir(no->dir);
  }else {
    aux = no;

    if (no->esq != NULL){
      no = no->esq;
    }else{
      no = NULL;
    }
  }

  return aux;
}

int altNO(struct NO *no) {
  if (no == NULL){
    return -1;
  }else{
    return no->alt;
  }
}

int fatBalanc(struct NO *no) {
  return (altNO(no->esq) - altNO(no->dir)); 
}

int maior(int num1, int num2) {
  if (num1 > num2){
    return num1;
  }else{
    return num2;
  }
}

struct NO *rotacaoR(struct NO *no) {
  struct NO *aux;

  aux = no->esq;
  no->esq = aux->dir;
  aux->dir = no;

  no->alt = maior(altNO(no->esq), altNO(no->dir)) + 1;
  aux->alt = maior(altNO(aux->esq), no->alt) + 1;

  return aux;
}

struct NO *rotacaoL(struct NO *no) {
  struct NO *aux;

  aux = no->dir;
  no->dir = aux->esq;
  aux->esq = no;

  no->alt = maior(altNO(no->esq), altNO(no->dir)) + 1;
  aux->alt = maior(no->alt, altNO(aux->dir)) + 1;

  return aux;
}

/*
struct NO* rotacaoR(struct NO *no){  //alterado para AVL
  struct NO *novaRaiz = no->esq;       
  struct NO *subArvore = novaRaiz->dir; 

  novaRaiz->dir = no;   
  no->esq = subArvore; 


  if (altNO(no->esq) > altNO(no->dir)){
    no->alt = 1 + altNO(no->esq);      
  }else{
    no->alt = 1 + altNO(no->dir); 
  }if (altNO(novaRaiz->esq) > altNO(novaRaiz->dir)){ 
    novaRaiz->alt = 1 + altNO(novaRaiz->esq);      
  }else{
    novaRaiz->alt = 1 + altNO(novaRaiz->dir); 
  }
  return novaRaiz; 
}

struct NO* rotacaoL(struct NO *no){  
  struct NO *novaRaiz = no->dir;         
  struct NO *subArvore = novaRaiz->esq; 

  novaRaiz->esq = no; 
  no->dir = subArvore; 

  if (altNO(no->esq) > altNO(no->dir)){ //
    no->alt = 1 + altNO(no->esq);      
  }else{
    no->alt = 1 + altNO(no->dir); 
  }if (altNO(novaRaiz->esq) > altNO(novaRaiz->dir)){ 
    novaRaiz->alt = 1 + altNO(novaRaiz->esq);      
  }else{
    novaRaiz->alt = 1 + altNO(novaRaiz->dir); 
  }
  return novaRaiz; 
}
*/

struct NO* balanceamento(struct NO *raiz, int info){  //criado para AVL
  if (raiz == NULL){
    return raiz;
  }
  if (altNO(raiz->esq) > altNO(raiz->dir)){
    raiz->alt = 1 + altNO(raiz->esq); 
  }else{
    raiz->alt = 1 + altNO(raiz->dir); 
  }
  int balanceamento = fatBalanc(raiz); 

  if (balanceamento > 1 && info < raiz->esq->valor){
    return rotacaoR(raiz);                      

  }if (balanceamento < -1 && info > raiz->dir->valor){ 
    return rotacaoL(raiz);                     
  
  }if (balanceamento > 1 && info > raiz->esq->valor){
    raiz->esq = rotacaoL(raiz->esq); 
    return rotacaoR(raiz);              
  }
  if (balanceamento < -1 && info < raiz->dir->valor){
    raiz->dir = rotacaoR(raiz->dir); 
    return rotacaoL(raiz);                  
  }

  return raiz; 
}

struct NO* insere(struct NO* raiz, int info){
  if(raiz == NULL){//se a raiz não existir
    raiz = criaNO(info);
  }else{
     if(info <= raiz->valor){
       raiz->esq = insere(raiz->esq, info);
     }else{
       raiz->dir = insere(raiz->dir, info);
     }
  }
  return balanceamento(raiz, info);  //alterado para AVL
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
    printf("%d",(*raiz).valor);

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

struct NO* excluir(struct NO *raiz, int info) {
  if (raiz == NULL){
    return raiz;
  }

  if (info < raiz->valor){
    raiz->esq = excluir(raiz->esq, info); 
  }else if (info > raiz->valor){
    raiz->dir = excluir(raiz->dir, info); 
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

    if (altNO(raiz->esq) >= altNO(raiz->dir)) {

      struct NO *temp = encontrarMaximo(raiz->esq); 
      raiz->valor = temp->valor;                              
      raiz->esq = excluir(raiz->esq, temp->valor); 
    }else{   
      struct NO *temp = encontrarMinimo(raiz->dir); 
      raiz->valor = temp->valor;  
      raiz->dir = excluir(raiz->dir, temp->valor);   
    }
  }
  return balanceamento(raiz, info);
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
  excluir(raiz, 95);
  excluir(raiz, 70);
  excluir(raiz, 60);
  excluir(raiz, 35);


  imprimeGrafoEmOrdem(raiz,0);
  printf("\n\n-----------------------\n\n");

  return 0;
}

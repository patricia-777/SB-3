//(IMPLEMENTACAO DO GITHUB)
#include <stdio.h>
#include <stdlib.h>


struct no{
	int8_t numero[81];
	struct no *prox;
};
typedef struct no no;


//funcoes de manipulacao de pilha
void inicializaPilha(no *);
int verificaPilhaVazia(no *);
no* alocaNo();
void mostraPilha(no *);
void liberaPilha(no *);
void push(no *, int8_t *);
int8_t* pop(no *);


//funcoes para notacao pos-fixa
int prioridade(char , char );
void posFixada(int8_t * , no *, no *);
void zerandoVetor(int8_t *);
void serparandoElementosExpressao(char *, no *, no *);
#include <stdio.h>
#include <stdlib.h>


struct no{
	char numero[81];
	struct no *prox;
};
typedef struct no no;



void inicializaPilha(no *);
int verificaPilhaVazia(no *);
no* alocaNo(char );
void mostraPilha(no *);
void liberaPilha(no *);
void push(no *, char );
char pop(no *);



int Prioridade(char c, char t);
void posFixa(char expr[], no *p);
//Codificação calculadora numeros de 256bits
//Grupo 6

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "calculadora.h"

int tam;

int main(int argc, char const *argv[])
{
	char expressao[200];

	if (argc == 1)
	{
		printf("Escreva a expressao: \n");
		scanf("%s", expressao);

		printf("%s\n", expressao);
	}
	else
	{
		printf("%s\n", argv[1]);
	}
	


	no *pilha = (no*) malloc(sizeof(no));

	inicializaPilha(pilha);

	posFixa(expressao, PILHA);

	return 0;

}



void posFixa(char expr[], no *p)
{
	int i = 0;
	char c,t;
 
	push(p, '(');
 
	do{
		c = expr[i];
		i++;

	    if(c >= 'a' && c <= 'z'){
	      printf("%c", c);
	    }
	    else if(c == '('){
	    	push(p, '(');
	    }
	    else if(c == ')' || c == '\0'){
	    	
	    	do{
	        	t = pop(p);
	        	
	        	if(t != '(')
	          		printf("%c", t);
	      	}while(t != '(');
	    }
	    else if(c == '+' || c == '-' || 
	            c == '*' || c == '/' ||
	            c == '^' )
	    {
	      	while(1){
	    	    t = pop(p);
	        	if(Prioridade(c,t)){
	          		push(p, t);
	          		push(p, c);
	          		break;
	        	}
	        	else{
	          		printf("%c", t);
	        	}
	      	}
	    }
  	}while(c != '\0');
  	
  	printf("\n");
  	
  	libera(p);

}

int Prioridade(char c, char t){
  int pc,pt;
 
  if(c == '^')
    pc = 4;
  else if(c == '*' || c == '/')
    pc = 2;
  else if(c == '+' || c == '-')
    pc = 1;
  else if(c == '(')
    pc = 4;
 
  if(t == '^')
    pt = 3;
  else if(t == '*' || t == '/')
    pt = 2;
  else if(t == '+' || t == '-')
    pt = 1;
  else if(t == '(')
    pt = 0;
 
  return (pc > pt);
}


//funcoes para gerenciamento de pilha

void inicializaPilha(no *pilha)
{
	pilha->prox = NULL;
	tam=0;
}

int verificaPilhaVazia(no *pilha)
{
	if(pilha->prox == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

no* alocaNo(char numero)
{
	no *novo=(no *) malloc(sizeof(no));
	
	if(!novo)
	{
		printf("Nao alocou\n");
	}else{
		novo->numero = numero;
		// strcpy(novo->numero, numero); 
		// printf("%c\n", novo->numero);
 	}
 	
 	return novo;
}


void mostraPilha(no *pilha)
{
	int count;

	if(vazia(pilha))
	{
		printf("pilha vazia!\n\n");
	}
	else
	{
		no *tmp;
		
		tmp = pilha->prox;
		
		printf("Pilha:");
		
		while( tmp != NULL)
		{
			printf("%c", tmp->numero);
			tmp = tmp->prox;
		}
	}

}


void liberaPilha(no *pilha)
{
	if(!vazia(pilha))
	{
		no *proxNo, *atual;

		atual = pilha->prox;

		while(atual != NULL)
		{
			proxNo = atual->prox;

			free(atual);
			
			atual = proxNode;
		}
	}
}


void push(no *pilha, char numero)
{
	no *novo=aloca(numero);

	// strcpy(novo->numero, numero);
	novo->numero = numero;
	novo->prox = NULL;

	if(vazia(pilha))
	{
		pilha->prox=novo;
	}
	else{
		no *aux = pilha->prox;

		while(aux->prox != NULL)
		{
			aux = aux->prox;
		}
			
			aux->prox = novo;
	}
	
	tam++;
}

char pop(no *pilha)
{
	if(pilha->prox == NULL)
	{
		printf("PILHA ja vazia\n\n");
		return NULL;
	}else
	{
		no *ultimo = pilha->prox, *penultimo = pilha;

		while(ultimo->prox != NULL)
		{
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		tam--;

		return ultimo->numero;
	}
}

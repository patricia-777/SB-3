//Codificação calculadora numeros de 256bits (IMPLEMENTACAO DO GITHUB)
//Grupo 6

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "calculadora.h"
#include "Soma.c"

int tam;

int main(int argc, char const *argv[])
{
	char expressao[200];

	//pegando expressao do usuário
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
	

	//inicializando duas pilhas, um auxiliar (pilha) e final com a expressao pos-fixada (pilhaPOSFIXA)
	no *pilha = (no*) malloc(sizeof(no));
	no *pilhaPOSFIXA = (no*) malloc(sizeof(no));

	inicializaPilha(pilha);
	inicializaPilha(pilhaPOSFIXA);

	//pegando cada elemento da expressao e trabalhando colocando na forma posfixada, dentro da pilha
	serparandoElementosExpressao(expressao, pilha, pilhaPOSFIXA);


	//liberando pilha final
	liberaPilha(pilhaPOSFIXA);

	return 0;

}

void serparandoElementosExpressao(char expr[], no *pilha, no *pilhaFinal)
{
	int8_t elementos[81];
	int8_t caracter;
	int indiceExp, indicePalavra = 0;
	int8_t final[81];

	//marcando o final da expressao
	zerandoVetor(final);
	final[0] = '\0';

	//percorrendo a expressao agrupando os elementos
	for (indiceExp = 0; indiceExp < strlen(expr); indiceExp++)
	{
		caracter = expr[indiceExp];

		//agrupando cada algarismo ate formar o numero
		if (caracter >= '0' && caracter<= '9')
		{
			elementos[indicePalavra] = (int8_t)caracter;
			indicePalavra++;

			//sei que o numero acabou quando o proximo elemento é um caracter de operacao
			if (!(expr[indiceExp+1] >= '0' && expr[indiceExp+1]<= '9'))
			{
				// printf("proximo operacao\n");
				elementos[indicePalavra] = '\0';
				indicePalavra=0;
				posFixada(elementos, pilha, pilhaFinal);
				zerandoVetor(elementos);
			}
		}
		//pegando o caracter de operacao
		else
		{
			elementos[indicePalavra] = (int8_t)caracter;
			elementos[indicePalavra+1] = '\0';
			posFixada(elementos, pilha, pilhaFinal);
			zerandoVetor(elementos);
		}
	}

	//finalizando analise da expressao
	posFixada(final, pilha, pilhaFinal);

	//mostrando a pilha pos fixada
	mostraPilha(pilhaFinal);

	//liberando pilha
	liberaPilha(pilha);
}

//zerando o vetor, inicializando ele (funcao auxiliar)
void zerandoVetor(int8_t vetor[])
{
	int i;

	for (i = 0; i < strlen((char *) vetor); i++)
	{
		vetor[i]=0;
	}

	vetor[i-1] = '\0';
}


//funcao que colcoa na ordem pos fixada
void posFixada(int8_t expr[], no *pilha, no *pilhaFinal)
{
	int i = 0;
	int8_t *caracterPilha;
 

    if(expr[0] >= '0' && expr[0] <= '9')
    {
    	// printf("é numero\n");
    	push(pilhaFinal, expr);
    	// printf("%s", expr);
    }
    else if(expr[0] == '(')
    {
    	// printf("é parenteses\n");
    	push(pilha, expr);
    }
    else if(expr[0] == ')' || expr[0] == '\0'){
    	
    	// printf("final\n");

    	do{
        	caracterPilha = pop(pilha);
        	
        	if(caracterPilha[0] != '(')
        	{
        		// printf("abre parensetes\n");
        		push(pilhaFinal, caracterPilha);
          		// printf("%s", caracterPilha);
        	}

      	}while(caracterPilha[0] != '(');
    }
    else if(expr[0] == '+' || expr[0] == '-' || expr[0] == '*' || expr[0] == '/' || expr[0] == '^' )
    {
    	// printf("operacao\n");
      	while(1)
      	{
    	    caracterPilha = pop(pilha);

        	if(prioridade(expr[0],caracterPilha[0]))
        	{
          		push(pilha, caracterPilha);
          		push(pilha, expr);
          		break;
        	}
        	else{
        		push(pilhaFinal, caracterPilha);
          		// printf("%s", caracterPilha);
        	}
      	}
    }
}

//funcao que decide a prioridade dos caracteres (auxiliar)
int prioridade(char caracter, char caracterPilha){

	int prioridadeCaracter,prioridadePilha;
 
 	if(caracter == '*' || caracter == '/'){
		prioridadeCaracter = 2;
	}
	else if(caracter == '+' || caracter == '-'){
		prioridadeCaracter = 1;
	}
	else if(caracter == '('){
		prioridadeCaracter = 4;
	}


	if(caracterPilha == '*' || caracterPilha == '/'){
		prioridadePilha = 2;
	}
	else if(caracterPilha == '+' || caracterPilha == '-'){
		prioridadePilha = 1;
	}
	else if(caracterPilha == '('){
		prioridadePilha = 0;
	}

	return (prioridadeCaracter > prioridadePilha);
}


//funcoes para gerenciamento de pilha que guarda cada elemento do tipo: int8_t vetor[81]

void inicializaPilha(no *pilha)
{
	int8_t parenteses[81];
	zerandoVetor(parenteses);
	parenteses[0] = '(';
	parenteses[1] = '\0';

	pilha->prox = NULL;
	tam=0;

	push(pilha, parenteses);
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

no* alocaNo()
{
	no *novo=(no *) malloc(sizeof(no));
	
	if(!novo)
	{
		printf("Nao alocou\n");
		return NULL;
	}else{
 		return novo;
 	}	
}


void mostraPilha(no *pilha)
{
	no *aux;

	if(verificaPilhaVazia(pilha))
	{
		printf("pilha vazia!\n\n");
	}
	else
	{
		aux = pilha->prox;
		
		printf("Pilha:");
		
		while( aux != NULL)
		{
			printf("%s ", aux->numero);
			aux = aux->prox;
		}

		printf("\n");
	}

}


void liberaPilha(no *pilha)
{
	if(!verificaPilhaVazia(pilha))
	{
		no *proxNo, *atual;

		atual = pilha->prox;

		while(atual != NULL)
		{
			proxNo = atual->prox;

			free(atual);
			
			atual = proxNo	;
		}
	}
}


void push(no *pilha, int8_t numero[])
{
	no *novo;

	novo = alocaNo();

	strcpy((char *)novo->numero ,(char *)numero);
	// novo->numero = numero;
	novo->prox = NULL;

	if(verificaPilhaVazia(pilha))
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

int8_t* pop(no *pilha)
{
	no *ultimo = pilha->prox, *penultimo = pilha;

	if(pilha->prox == NULL)
	{
		printf("PILHA ja vazia\n\n");
		return NULL;
	}else
	{
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

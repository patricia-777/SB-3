//Codificação calculadora numeros de 256bits (IMPLEMENTACAO DO GITHUB)
//Grupo 6

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "calculadora.h"
#include "soma.h"

int tam;

int main(int argc, char const *argv[])
{
	char expressao[200];
	char *resultado;

	printf("###########################################\n\n");

	printf("BEM VIND@ A NOSSA CALCULADORA ORÁCULO!!!\n\n");
	
	//pegando expressao do usuário
	if (argc == 1)
	{
		printf("Escreva a expressao que deseja saber o resultado: ");
		scanf("%s", expressao);

		printf("\nVocê pediu o resultado para:  %s\n", expressao);
	}
	else
	{
		// printf("%s\n", argv[1]);
		strcpy(expressao, argv[1]);

		printf("Você pediu o resultado para:  %s\n", argv[1]);
	}
	
	//inicializando duas pilhas, um auxiliar (pilha) e final com a expressao pos-fixada (pilhaPOSFIXA)
	no *pilha = (no*) malloc(sizeof(no));
	no *pilhaPOSFIXA = (no*) malloc(sizeof(no));

	inicializaPilha(pilha);
	inicializaPilha(pilhaPOSFIXA);

	//pegando cada elemento da expressao e trabalhando colocando na forma posfixada, dentro da pilha
	serparandoElementosExpressao(expressao, pilha, pilhaPOSFIXA);

	//mostrando a pilha pos fixada
	// mostraPilha(pilhaPOSFIXA);

	resultado = gerencia(pilhaPOSFIXA);

	printf("E nós te revelamos:  %s\n\n", resultado);

	printf("VOLTE SEMPRE!!\n");

	printf("###########################################\n\n");

	//liberando pilha final
	liberaPilha(pilhaPOSFIXA);

	return 0;

}

char* gerencia(no *pilha)
{
	no *aux1, *aux2;

	if (pilha != NULL)
	{
		aux1 = pop(pilha);

		if (!strcmp((char *)aux1->numero, "+"))
		{
			return soma(gerencia(pilha), gerencia(pilha));
		}
		// else if (!strcmp((char *)aux1->numero, "-"))
		// {
		// 	aux2 = pop(pilha);
		// 	return subtracao(gerencia(aux2), gerencia(pilha));
		// }
		// else if (!strcmp((char *)aux1->numero, "*"))
		// {
		// 	aux2 = pop(pilha);
		// 	return  multiplicacao(gerencia(aux2), gerencia(pilha));
		// }
		// else if (!strcmp((char *)aux1->numero, "/"))
		// {
		// 	aux2 = pop(pilha);
		// 	 return divisao(gerencia(aux2), gerencia(pilha));
		// }
		else 
		{
			
			return (char *)aux1->numero;
		}

	}
	else{
		return NULL;
	}
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
	no *caracterPilha;
 

    if(expr[0] >= '0' && expr[0] <= '9')
    {
    	push(pilhaFinal, expr);
    }
    else if(expr[0] == '(')
    {
    	push(pilha, expr);
    }
    else if(expr[0] == ')' || expr[0] == '\0'){

    	do{
        	caracterPilha = pop(pilha);
        	
        	if(caracterPilha->numero[0] != '(')
        	{
        		push(pilhaFinal, caracterPilha->numero);
        	}

      	}while(caracterPilha->numero[0] != '(');
    }
    else if(expr[0] == '+' || expr[0] == '-' || expr[0] == '*' || expr[0] == '/' || expr[0] == '^' )
    {
      	while(1)
      	{
    	    caracterPilha = pop(pilha);

        	if(prioridade(expr[0],caracterPilha->numero[0]))
        	{
          		push(pilha, caracterPilha->numero);
          		push(pilha, expr);
          		break;
        	}
        	else{
        		push(pilhaFinal, caracterPilha->numero);
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

no* pop(no *pilha)
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

		return ultimo;
	}
}

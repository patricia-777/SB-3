//
//  Soma.c
//  C 3
//
//  Created by Richard Roberto on 5/16/16.
//  Copyright © 2016 Richard Roberto. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char * soma(char * elemento1, char * elemento2);
/*
int main()
{
    char elemento1[30];
    char elemento2[30];
    
    printf("Escreva o elemento 1: ");
    scanf("%s", elemento1);
    printf("Escreva o elemento 2: ");
    scanf("%s", elemento2);
    
    soma(elemento1,elemento2);
    return 0;
}
*/
char * soma(char * elemento1, char * elemento2)
{
    /* Os dois operandos serão convertidos em long e salvos em um array de long para poder realizar-se a operação de soma. */
    
    /* O número de elementos de cada entrada é importate para saber o número de posições que terão os arrays. */
    int tamanho_elemento1, tamanho_elemento2, tamanho;
    tamanho_elemento1 = (int)strlen(elemento1);
    tamanho_elemento2 = (int)strlen(elemento2);
    
    /* Para realizar as operações, os dois arrays terão o tamanho da maior entrada. */
    if(tamanho_elemento1 > tamanho_elemento2) tamanho = tamanho_elemento1;
    else tamanho = tamanho_elemento2;
    
    long *elem1 = malloc(tamanho*sizeof(long));
    long *elem2 = malloc(tamanho*sizeof(long));
    
    for(int i = 0; i < tamanho; i++)
    {
        elem1[i] = 0;
        elem2[i] = 0;
    }
    
    /* Essa parte do código cria o array para o primeiro elemento. */
    long resto1 = tamanho_elemento1%9;
    if(resto1 == 0)
    {
        for(int i = (tamanho_elemento1/9); i >= 0; i--)
        {
            long temp = 0;
            for(int j = 8; j >= 0; j--)
            {
                char t;
                if(i == 0)
                {
                    temp = 0;
                    break;
                }
                else t = elemento1[i*9 - j - 1];
                temp = temp * 10 + (t - 48);
            }
            elem1[tamanho_elemento1/9 - i] = temp;
        }
    }
    else
    {
        for(int i = (tamanho_elemento1/9); i >= 0; i--)
        {
            long temp = 0;
            for(int j = 8; j >= 0; j--)
            {
                char t;
                if(i == 0)
                {
                    for(int k = 0; k < resto1; k++)
                    {
                        t = elemento1[k];
                        temp = temp*10 + (t-48);
                    }
                    break;
                }
                else t = elemento1[i*9 - j + resto1 - 1];
                temp = temp * 10 + (t - 48);
            }
            elem1[tamanho_elemento1/9 - i] = temp;
        }
    }
    
    /* Array para o elemento 2. */
    long resto2 = tamanho_elemento2%9;
    if(resto2 == 0)
    {
        for(int i = (tamanho_elemento2/9); i >= 0; i--)
        {
            long temp = 0;
            for(int j = 8; j >= 0; j--)
            {
                char t;
                if(i == 0)
                {
                    temp = 0;
                    break;
                }
                else t = elemento2[i*9 - j - 1];
                temp = temp * 10 + (t - 48);
            }
            elem2[tamanho_elemento2/9 - i] = temp;
        }
    }
    else
    {
        for(int i = (tamanho_elemento2/9); i >= 0; i--)
        {
            long temp = 0;
            for(int j = 8; j >= 0; j--)
            {
                char t;
                if(i == 0)
                {
                    for(int k = 0; k < resto2; k++)
                    {
                        t = elemento2[k];
                        temp = temp*10 + (t-48);
                    }
                    break;
                }
                else t = elemento2[i*9 - j + resto2 - 1];
                temp = temp * 10 + (t - 48);
            }
            elem2[tamanho_elemento2/9 - i] = temp;
        }
    }
    /*
     for(int i = 0; i < tamanho/9+1; i++)
     {
     printf("elem1: %ld\telem2: %ld\n",elem1[i],elem2[i]);
     }
     */
    /* Para somar, soma-se elemento a elemento dos arrays com as entradas convertidas em long. */
    long carry = 0;
    long * resultado = malloc((tamanho)*sizeof(long));
    for(int i = 0; i < tamanho/9+1; i++)//é necessário saber se há carry da soma de cada
    {
        long temp = elem1[i] + elem2[i] + carry;
        /* É necessário levar em consideração o carry out da soma. */
        if((temp/1000000000)>0)
        {
            carry = 1;
            resultado[i] = temp-1000000000;
        }
        else
        {
            carry = 0;
            resultado[i] = temp;
        }
        //printf("resultado: %ld\n", resultado[i]);
    }
    
    char * retorno = malloc(32);
    sprintf(retorno,"%ld",carry);
    for( int i = tamanho/9; i >= 0; i--)
    {
        char* temp = malloc(10);
        sprintf(temp,"%09ld",resultado[i]);
        strcat(retorno,temp);
    }
    
    printf("retorno: %s\n", retorno);
    return retorno;
    
}
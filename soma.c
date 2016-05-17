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

void soma()
{
    /* Os dois operandos serão convertidos em long e salvos em um array de long para poder realizar-se a operação de soma. */
    char * elemento1, * elemento2;
    elemento1 = "1";
    elemento2 = "1234567";
    
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
    long resto1 = tamanho_elemento1%3;
    switch(resto1)
    {
        case 0:
            for(int i = (tamanho_elemento1/3); i >= 0; i--)
            {
                long temp1 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t1;
                    if(i == 0)
                    {
                        temp1 = 0;
                        break;
                    }
                    else t1 = elemento1[i*3 - j - 1];
                    temp1 = temp1 * 10 + (t1 - 48);
                }
                elem1[tamanho_elemento1/3 - i] = temp1;
            }
            break;
        case 1:
            for(int i = (tamanho_elemento1/3); i >= 0; i--)
            {
                long temp1 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t1;
                    if(i == 0)
                    {
                        t1 = elemento1[0];
                        temp1 = t1 - 48;
                        break;
                    }
                    else t1 = elemento1[i*3 - j];
                    temp1 = temp1 * 10 + (t1 - 48);
                }
                elem1[tamanho_elemento1/3 - i] = temp1;
            }
            break;
        case 2:
            for(int i = (tamanho_elemento1/3); i >= 0; i--)
            {
                long temp1 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t1;
                    if(i == 0)
                    {
                        t1 = elemento1[0];
                        temp1 = t1 - 48;
                        t1 = elemento1[1];
                        temp1 = 10*temp1 + (t1-48);
                        break;
                    }
                    else t1 = elemento1[i*3 - j + 1];
                    temp1 = temp1 * 10 + (t1 - 48);
                }
                elem1[tamanho_elemento1/3 - i] = temp1;
            }
            break;
    }
    /* Array para o elemento 2. */
    long resto2 = tamanho_elemento2%3;
    switch(resto2)
    {
        case 0:
            for(int i = (tamanho_elemento2/3); i >= 0; i--)
            {
                long temp2 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t2;
                    if(i == 0)
                    {
                        temp2 = 0;
                        break;
                    }
                    else t2 = elemento2[i*3 - j - 1];
                    temp2 = temp2 * 10 + (t2 - 48);
                }
                elem2[tamanho_elemento2/3 - i] = temp2;
            }
            break;
        case 1:
            for(int i = (tamanho_elemento2/3); i >= 0; i--)
            {
                long temp2 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t2;
                    if(i == 0)
                    {
                        t2 = elemento2[0];
                        temp2 = t2 - 48;
                        break;
                    }
                    else t2 = elemento2[i*3 - j];
                    temp2 = temp2 * 10 + (t2 - 48);
                }
                elem2[tamanho_elemento2/3 - i] = temp2;
            }
            break;
        case 2:
            for(int i = (tamanho_elemento2/3); i >= 0; i--)
            {
                long temp2 = 0;
                for(int j = 2; j >= 0; j--)
                {
                    char t2;
                    if(i == 0)
                    {
                        t2 = elemento2[0];
                        temp2 = t2 - 48;
                        t2 = elemento2[1];
                        temp2 = 10 * temp2 + (t2-48);
                        break;
                    }
                    else t2 = elemento2[i*3 - j + 1];
                    temp2 = temp2 * 10 + (t2 - 48);
                }
                elem2[tamanho_elemento2/3 - i] = temp2;
            }
            break;
    }
    
    for(int i = 0; i < tamanho/3+1; i++)
    {
        printf("elem1: %ld\telem2: %ld\n",elem1[i],elem2[i]);
    }
    /* Para somar, soma-se elemento a elemento dos arrays com as entradas convertidas em long. */
    long carry = 0;
    long * resultado = malloc((tamanho)*sizeof(long));
    for(int i = 0; i < tamanho/3+1; i++)//é necessário saber se há carry da soma de cada
    {
        long temp = elem1[i] + elem2[i] + carry;
        /* É necessário levar em consideração o carry out da soma. */
        if((temp/1000)>0)
        {
            carry = 1;
            resultado[i] = temp-1000;
        }
        else
        {
            carry = 0;
            resultado[i] = temp;
        }
        printf("resultado: %ld\n", resultado[i]);
    }
    
    char * retorno = malloc(32);
    sprintf(retorno,"%ld",carry);
    printf("retorno: %s\n", retorno);
    for( int i = 2; i >= 0; i--)
    {
        char* temp = malloc(4);
        sprintf(temp,"%03ld",resultado[i]);
        strcat(retorno,temp);
    }
    
    printf("retorno: %s\n", retorno);
    
}
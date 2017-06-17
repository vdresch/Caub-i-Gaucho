//
//  main.c
//  Caubói Gaúcho
//
//  Copyright © 2017 Caubói Gaúcho. All rights reserved.
//

#include <stdio.h>

#define Tamanho 15
#define NTerminais 15

#define Tamanho2 3
#define NVariaveis 15


void le_gramatica(char terminais[NTerminais][Tamanho], char variaveis[NVariaveis][Tamanho2], char *inicial)
{
    FILE* f;
    
    int i = 0;
    int j = 0;
    int var;
    char c;
    
    f = fopen("sample.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    else
    {
        while((c = fgetc(f)) != 13)
        {
            ;
        }
        while((c = fgetc(f)) == '[')
        {
            c = fgetc(f);
            while((c = fgetc(f)) != ' ' && c != 127)
            {
                terminais[i][j] = c;
                j++;
//                printf(" %c %i ", c, c);
            }
            j = 0;
            i++;
            while((c = fgetc(f)) != 13)
            {
                ;
            }
        }
        j = 0;
        i = 0;
        while((c = fgetc(f)) != 13)
        {
            ;
        }
        while((c = fgetc(f)) == '[')
        {
            c = fgetc(f);
            while((c = fgetc(f)) != ' ')
            {
                variaveis[i][j] = c;
                j++;
            }
            j = 0;
            i++;
            while((c = fgetc(f)) != 13)
            {
                ;
            }
        }
        while((c = fgetc(f)) != 13)
        {
                ;
        }
        c = fgetc(f);
        c = fgetc(f);
        c = fgetc(f);
        *inicial = c;
        
        fclose(f);
        return;
    }
}


int main(int argc, const char * argv[])
{
    
    char Terminais[NTerminais][Tamanho];
    char Variaveis[NVariaveis][Tamanho2];
    char Inicial;
    int i, j, k = 0;
    
    for(i = 0; i< NTerminais; i++)
    {
        for(j = 0; j<Tamanho; j++)
        {
            Terminais[i][j] = '\0';
        }
    }
    for(i = 0; i< NVariaveis; i++)
    {
        for(j = 0; j<Tamanho2; j++)
        {
            Variaveis[i][j] = '\0';
        }
    }
    
    
    le_gramatica(Terminais, Variaveis, &Inicial);
    
    return 0;
}

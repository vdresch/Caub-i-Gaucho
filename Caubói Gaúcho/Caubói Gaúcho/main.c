//
//  main.c
//  Caubói Gaúcho
//
//  Copyright © 2017 Caubói Gaúcho. All rights reserved.
//

#include <stdio.h>

#define Tamanho 15
#define NTerminais 15


void le_gramatica(char terminais[Tamanho][NTerminais])
{
    FILE* f;
    
    int i = 0;
    int j = 0;
    char c;
    
    f = fopen("sample.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    else
    {
        while((c = fgetc(f)) != 10)
        {
            ;
        }
        while((c = fgetc(f)) != '[')
        {
            c = fgetc(f);
            while((c = fgetc(f)) != ' ')
            {
                terminais[i][j] = c;
                i++;
            }
            i = 0;
            j++;
            while((c = fgetc(f)) != 10)
            {
                ;
            }
        }
        fclose(f);
        return;
    }
}


int main(int argc, const char * argv[])
{
    
     char Terminais[Tamanho][NTerminais];
    
    
    
    
    return 0;
}

//
//  main.c
//  Caubói Gaúcho
//
//  Copyright © 2017 Caubói Gaúcho. All rights reserved.
//

#include <stdio.h>

#define Tamanho 30
#define MaxTerminais 60

#define Tamanho2 30
#define MaxVariaveis 60

#define arquivo "sample.txt"

int NVariaveis = 0;
int NTerminais = 0;

// Lê o do arquivo de texto e guarda os terminais e variáveis em suas respectivas matrizes. Também guarda a variável inicial
void le_gramatica(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], char inicial[Tamanho2])
{
    FILE* f;

    int i = 0;
    int j = 0;
    int var;
    char c;

    f = fopen(arquivo, "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    else
    {
        printf("\nArquivo carregado com sucesso\n\n");

        if((c = fgetc(f)) != '<')  // Verifica primeira linha
        {
            printf("\nErro de sintaxe! Linha 1\n");
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }

        // Percorre todos os terminais
        while((c = fgetc(f)) == '[')
        {
            if(c=fgetc(f)!= ' ') // Pula primeiro espaço  -> [ terminal ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (terminal)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                terminais[i][j] = c;
                j++;
//                printf("%c", c);
            }
            terminais[i][j-1] = '\0';   // Elimina o espaço que foi colocado ao fim do terminal
            NTerminais++;
            j = 0;
            i++;
            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
        }
        j = 0;
        i = 0;

        if(c != 'V')  // Verifica linha Variaveis
        {
            printf("\n%c\nErro de sintaxe! \"Variaveis\" faltando\n",c);
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }

//        printf("\n");

        // Percorre todas as variáveis
        while((c = fgetc(f)) == '[')
        {
            if(c=fgetc(f)!= ' ') // Pula primeiro espaço  -> [ terminal ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (variável)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                variaveis[i][j] = c;
                j++;
//                printf("%c", c);
            }
            variaveis[i][j-1] = '\0';   // Elimina o espaço que foi colocado ao fim da variável
            NVariaveis++;
            j = 0;
            i++;
            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
        }

        if(c != 'I')  // Verifica linha Variaveis
        {
            printf("\n%c\nErro de sintaxe! \"Inicial\" faltando\n",c);
            exit(0);
        }

        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
                ;
        }

        // Variável inicial
        if((c = fgetc(f)) != '[')  // Verifica '[' na linha da variável inicial
        {
            printf("\n%c\nErro de sintaxe! \'[\' faltando\n",c);
            exit(0);
        }
        if((c = fgetc(f)) != ' ')  // Verifica ' ' na linha da variável inicial
        {
            printf("\n%c\nErro de sintaxe! \' \' faltando\n",c);
            exit(0);
        }
        i = 0;
        while((c = fgetc(f)) != ']' && c != 127)
        {
            inicial[i] = c;
            i++;
//            printf("%c", c);
        }
        inicial[i-1] = '\0';   // Elimina o espaço que foi colocado ao fim da variável inicial


        return;
    }
}

// Imprime todos os terminais na matriz de terminais
void imprime_terminais(char Terminais[MaxTerminais][Tamanho])
{
    int i=0;
    int j=0;
    if(Terminais[i][j] != '\0')
    {
        printf("\n-----------------------------");
        printf("\nTerminais");
        printf("\n-----------------------------\n");
        for(i = 0; i< MaxTerminais; i++)
        {
            for(j = 0; j<Tamanho; j++)
            {
                if(Terminais[i][j] != '\0')
                    printf("%c", Terminais[i][j]);
            }
            if(Terminais[i][j] != '\0')
                printf("\n");
        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha terminais.\n");
}

//Imprime todas as variáveis na matriz de variáveis
void imprime_variaveis(char Variaveis[MaxVariaveis][Tamanho2], char inicial[Tamanho2])
{
    int i=0;
    int j=0;
    if(Variaveis[i][j] != '\0')
    {
        printf("\n-----------------------------");
        printf("\nVariaveis");
        printf("\n-----------------------------\n");
        printf("Variavel Inicial: \n");
        for(i = 0; i<Tamanho; i++)
        {
            if(inicial[i] != '\0')
                printf("%c", inicial[i]);
        }
        printf("\n\nRestante:\n");
        for(i = 0; i< MaxVariaveis; i++)
        {
            for(j = 0; j<Tamanho2; j++)
            {
                if(Variaveis[i][j] != '\0')
                    printf("%c", Variaveis[i][j]);
            }
            if(Variaveis[i][j] != '\0')
                printf("\n");
        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha variaveis.\n");
}

// Inicializa as matrizes de terminais e de variáveis com o caractere '\0'
void inicializa_matrizes(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], char inicial[Tamanho2])
{
    int i, j = 0;

    for(i = 0; i< MaxTerminais; i++)
    {
        for(j = 0; j<Tamanho; j++)
        {
            terminais[i][j] = '\0';
        }
    }
    for(i = 0; i< MaxVariaveis; i++)
    {
        for(j = 0; j<Tamanho2; j++)
        {
            variaveis[i][j] = '\0';
        }
    }
    for(i = 0; i<Tamanho2; i++)
    {
        inicial[i] = '\0';
    }

    printf("\nMatrizes inicializadas\n");
}

int main(int argc, const char * argv[])
{
    char Terminais[MaxTerminais][Tamanho];
    char Variaveis[MaxVariaveis][Tamanho2];
    char Inicial[Tamanho2];

    inicializa_matrizes(Terminais, Variaveis, Inicial);

    le_gramatica(Terminais, Variaveis, Inicial);

    imprime_terminais(Terminais);
    imprime_variaveis(Variaveis, Inicial);

    printf("NVariaveis: %i\nNTerminais: %i\n", NVariaveis, NTerminais);

    return 0;
}

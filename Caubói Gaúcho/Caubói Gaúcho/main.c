//
//  main.c
//  Caubói Gaúcho
//
//  Copyright © 2017 Caubói Gaúcho. All rights reserved.
//


//bibliotecas

#include <stdio.h>
#include <string.h>


//Constantes

#define Tamanho 30
#define MaxTerminais 60

#define Tamanho2 30
#define MaxVariaveis 60

#define NVarRegra 30
#define NRegras 60

#define arquivo "sample.txt"


//variaveis

int NVariaveis = 0;
int NTerminais = 0;


//estruturas

struct REGRA
{
    int variavel;           //posição no array variaveis da variavel da esquerda
    int nTermos;           //numero de termos a direita
    int proxVar[NVarRegra][2];  //termos a direita. primeiro [] diz qual termo do array olhar. segundo [] diz se é pra olhar no vetor de variaveis ou terminais
    float peso;
};






// Lê o do arquivo de texto e guarda os terminais e variáveis em suas respectivas matrizes. Também guarda a variável inicial
void le_gramatica(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], int *inicial, struct REGRA regras[NRegras])
{
    FILE* f;
    
    int i = 0;
    int j = 0;
    int k = 0;
    char var[Tamanho2], var2[Tamanho2];
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
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ terminal ]
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
            var[i] = c;
            i++;
            //            printf("%c", c);
        }
        if(var[i-1] == ' ')
            var[i-1] = '\0';
        
        //testa se var é igual a uma variavel. se sim, atribui a posição ao simbolo inicial
    
        for(i=0; i<MaxVariaveis; i++)
        {
            if(!strcmp(var, variaveis[i]))
            {
                *inicial = i;
            }
        }
        
        j=0;
        
        //Regras(sob construção)
        
        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }
        while((c = fgetc(f)) != 13) // Vai para a próxima linha
        {
            ;
        }
        i = 0;
        
        strcpy(var2, "");
        
        while((c = fgetc(f)) == '[')
        {
            //carrega posicao da variavel
            c = fgetc(f);
            while((c = fgetc(f)) != ']' && c != 127)
            {
                var2[i] = c;
                i++;
            }
            if(var2[i-1] == ' ')
                var2[i-1] = '\0';
            for(i=0; i<MaxVariaveis; i++)
            {
                //strcpy(var, variaveis[i]);
                if(!strcmp(var2, variaveis[i]))
                {
                    regras[j].variavel = i;
                }
                
            }
            //carrega variaveis
            
            while((c = fgetc(f)) != ';')
            {
                if(c == '[')
                {
                    i=0;
                    c = fgetc(f);
                    while((c = fgetc(f)) != ']' && c != 127)
                    {
                        var2[i] = c;
                        i++;
                    }
                    if(var2[i-1] == ' ')
                        var2[i-1] = '\0';
                    for(i=0; i<MaxVariaveis; i++)
                    {
                       // strcpy(var, variaveis[i]);
                        if(strcmp(var2, variaveis[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 1;
                            regras[j].nTermos++;
                        }
                        
                    }
                    for(i=0; i<MaxTerminais; i++)
                    {
                       // strcpy(var, terminais[i]);
                        if(strcmp(var2, terminais[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 2;
                            regras[j].nTermos++;
                        }
                        
                    }
                    for(i=0;i<Tamanho2;i++)
                    {
                        var2[i] = 0;
                    }
                    i=0;
                    k++;
                }
            }
            
            //pega peso
            c = fgetc(f);
            if(c == '\t')
                c = fgetc(f);
            regras[j].peso += (c - 48);
            c = fgetc(f);
            if(c == '.')
            {
                c = fgetc(f);
                regras[j].peso += (c - 48)*0.1;
                c = fgetc(f);
                if(c != ' ' && c != '\t' && c != '\r')
                    regras[j].peso += (c - 48)*0.01;
            }
            
            
            
            while((c = fgetc(f)) != 13) // Vai para a próxima linha
            {
                ;
            }
            j++;
            i = 0;
            k=0;
        }
        
        
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
void imprime_variaveis(char Variaveis[MaxVariaveis][Tamanho2], int inicial)
{
    int i=0;
    int j=0;
    if(Variaveis[i][j] != '\0')
    {
        printf("\n-----------------------------");
        printf("\nVariaveis");
        printf("\n-----------------------------\n");
        printf("Variavel Inicial: \n");
        for(i=0; i<Tamanho2; i++)
        {
            printf("%c", Variaveis[inicial][i]);
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
void inicializa_matrizes(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], struct REGRA regras[NRegras])
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
    for(i = 0; i< NRegras; i++)
    {
        regras[i].variavel = 0;
        regras[i].nTermos = 0;
        regras[i].peso = 0;
        for(j=0; j<NVarRegra; j++)
        {
            regras[i].proxVar[j][0] = -1;
            regras[i].proxVar[j][1] = -1;
        }
    }
    
    printf("\nMatrizes inicializadas\n");
}


//main

int main(int argc, const char * argv[])
{
    char Terminais[MaxTerminais][Tamanho];
    char Variaveis[MaxVariaveis][Tamanho2];
    struct REGRA Regras[NRegras];
    int Inicial = 0;
    
    inicializa_matrizes(Terminais, Variaveis, Regras);
    
    le_gramatica(Terminais, Variaveis, &Inicial, Regras);
    
    imprime_terminais(Terminais);
    imprime_variaveis(Variaveis, Inicial);
    
    printf("NVariaveis: %i\nNTerminais: %i\n", NVariaveis, NTerminais);
    
    return 0;
}

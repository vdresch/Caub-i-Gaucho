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

#define Tamanho 200
#define MaxTerminais 30

#define Tamanho2 70
#define MaxVariaveis 50

#define NVarRegra 10
#define MaxRegras 60

#define arquivo "gramatica2.txt"


//variaveis

int NVariaveis = 0;
int NTerminais = 0;
int NRegras = 0;


//estruturas

struct REGRA
{
    int marcador;           // Posição do marcador utilizado pelo parser
    int variavel;           //posição no array variaveis da variavel da esquerda
    int nTermos;           //numero de termos a direita
    int proxVar[NVarRegra][2];  //termos a direita. primeiro [] diz qual termo do array olhar. segundo [] diz se é pra olhar no vetor de variaveis ou terminais
    float peso;
    int ID;                // Número de identificação para fácil diferenciação entre regras
};






// Lê o do arquivo de texto e guarda os terminais e variáveis em suas respectivas matrizes. Também guarda a variável inicial
void le_gramatica(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], int *inicial, struct REGRA regras[MaxRegras])
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
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ terminal ]
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
            var[i-1] = '\0';  // Elimina o espaço que foi colocado ao fim da variável

        //testa se var é igual a uma variavel. se sim, atribui a posição ao simbolo inicial
        int inicialEvariavel = 0;
        for(i=0; i<MaxVariaveis; i++)
        {
            if(!strcmp(var, variaveis[i]))
            {
                *inicial = i;
                inicialEvariavel = 1;
            }
        }
        if(!inicialEvariavel)   // Se a variável inicial não estiver na matriz de variáveis, retorna erro
        {
            printf("\nErro! Variavel inicial nao foi declarada como variavel.\n",c);
            exit(0);
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
            if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ variável ]
            {
                printf("\nErro de sintaxe! Espaco faltando\n");
                exit(0);
            }

            // Pega a palavra até o próximo ']' (parte esquerda da regra)
            while((c = fgetc(f)) != ']' && c != 127)
            {
                var2[i] = c;
                i++;
            }
            if(var2[i-1] == ' ')
                var2[i-1] = '\0';   // Elimina o espaço que foi colocado ao fim do terminal

            // Encontra a posição da variável da regra na matriz de variáveis
            int varExiste = 0;
            for(i=0; i<MaxVariaveis; i++)
            {
                //strcpy(var, variaveis[i]);
                if(!strcmp(var2, variaveis[i]))
                {
                    regras[j].variavel = i;
                    varExiste = 1;
                }
            }
            if(!varExiste)    // Se a variável da regra não existe, retorna erro
            {
                printf("\nErro! A variavel \"");
                int k = 0;
                for(;k<strlen(var2);k++)
                {
                    if(var2[k]!='\0')
                        printf("%c",var2[k]);
                }
                printf("\" foi declarada nas regras mas nao nas variaveis.\n");
                exit(0);
            }

            //carrega variaveis
            while((c = fgetc(f)) != ';')
            {
                if(c == '[')    // Parte direita da regra encontrada
                {
                    i=0;
                    if((c=fgetc(f))!= ' ') // Pula primeiro espaço  -> [ ? ]
                    {
                        printf("\nErro de sintaxe! Espaco faltando\n");
                        exit(0);
                    }

                    // Pega a palavra até o próximo ']' (parte direita da regra)
                    while((c = fgetc(f)) != ']' && c != 127)
                    {
                        var2[i] = c;
                        i++;
                    }
                    if(var2[i-1] == ' ')
                        var2[i-1] = '\0';

                    // Procura parte direita na lista de variáveis
                    int varExiste = 0;
                    int terExiste = 0;
                    for(i=0; i<MaxVariaveis; i++)
                    {
                       // strcpy(var, variaveis[i]);
                        if(strcmp(var2, variaveis[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 1;
                            regras[j].nTermos++;
                            varExiste = 1;
                        }
                    }

                    // Procura parte direita na lista de terminais
                    for(i=0; i<MaxTerminais; i++)
                    {
                       // strcpy(var, terminais[i]);
                        if(strcmp(var2, terminais[i]) == 0)
                        {
                            regras[j].proxVar[k][0] = i;
                            regras[j].proxVar[k][1] = 2;
                            regras[j].nTermos++;
                            terExiste = 1;
                        }
                    }

                    if(terExiste && varExiste)  // Se encontrou a var2 na lista de terminais E na de variáveis
                    {
                        printf("\nErro! \"");
                        int k = 0;
                        for(;k<strlen(var2);k++)
                        {
                            if(var2[k]!='\0')
                                printf("%c",var2[k]);
                        }
                        printf("\" declarado como variavel e terminal.\n");
                        exit(0);
                    }
                    else if(!terExiste && !varExiste)   // Se não encontrou var2 na lista de variáveis OU na de terminais
                    {
                        printf("\nErro! \"");
                        int k = 0;
                        for(;k<strlen(var2);k++)
                        {
                            if(var2[k]!='\0')
                                printf("%c",var2[k]);
                        }
                        printf("\" foi declarado somente nas regras.\n");
                        exit(0);
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
            //else if((c = fgetc(f)) == ' ')
            //    while((c = fgetc(f)) == ' ')
            //        ;
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

            regras[j].ID = NRegras;

            NRegras ++;



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

//Imprime todas as regras na matriz de regras
void imprime_regras(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], struct REGRA regras[MaxRegras])
{
    int i=0;
    int j=0;
    if(regras[0].proxVar[0][0] != -1)
    {
        printf("\n-----------------------------");
        printf("\nRegras");
        printf("\n-----------------------------\n");
        for(i = 0; i< NRegras; i++)
        {
            if(regras[i].proxVar[0][1] != -1)
            {
                printf("[ ");
                int k = 0;
                // Imprime lado esquerdo da regra
                for(;k<strlen(variaveis[regras[i].variavel]);k++)
                {
                    if(variaveis[regras[i].variavel][k]!='\0')
                        printf("%c",variaveis[regras[i].variavel][k]);
                }
                printf(" ] ->");

                // Imprime lado direito da regra
                for(j=0; j<regras[i].nTermos; j++)
                {
                    int k = 0;
                    printf(" [ ");
                    //printf("\n\n\n_%c_\n\n\n", );
                    if(regras[i].proxVar[j][1]==1)
                    {
                        for(;k<Tamanho2;k++)
                        {
                            if(variaveis[regras[i].proxVar[j][0]][k]!='\0')
                                printf("%c",variaveis[regras[i].proxVar[j][0]][k]);
                        }
                    }
                    else if(regras[i].proxVar[j][1]==2)
                    {
                        for(;k<Tamanho;k++)
                        {
                            if(terminais[regras[i].proxVar[j][0]][k]!='\0')
                                printf("%c",terminais[regras[i].proxVar[j][0]][k]);
                        }
                    }
                    printf(" ]");
                }

                // Imprime peso da regra
                printf(" ;%.2f", regras[i].peso);

                // Imprime marcador
                printf("  Marcador: %i", regras[i].marcador);
                printf("\n");

                // Imprime ID
                printf("  ID: %i", regras[i].ID);
                printf("\n");
            }

        }
        printf("-----------------------------\n\n");
    }
    else
        printf("\nNao ha regras.\n");
}

// Inicializa as matrizes de terminais e de variáveis com o caractere '\0'
void inicializa_matrizes(char terminais[MaxTerminais][Tamanho], char variaveis[MaxVariaveis][Tamanho2], struct REGRA regras[MaxRegras], struct REGRA D0[MaxRegras])
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
    for(i = 0; i< MaxRegras; i++)
    {
        regras[i].marcador = 0;
        regras[i].variavel = -1;
        regras[i].nTermos = 0;
        regras[i].peso = 0;
        regras[i].ID = -1;
        //D0
        D0[i].marcador = 0;
        D0[i].variavel = -1;
        D0[i].nTermos = 0;
        D0[i].peso = 0;
        D0[i].ID = -1;
        for(j=0; j<NVarRegra; j++)
        {
            regras[i].proxVar[j][0] = -1;
            regras[i].proxVar[j][1] = -1;
            //D0
            D0[i].proxVar[j][0] = -1;
            D0[i].proxVar[j][1] = -1;
        }
    }

    printf("\nMatrizes inicializadas\n");
}

// Função que gera D0
int gera_D0(int var, struct REGRA regras[MaxRegras], struct REGRA regras_out[MaxRegras], int k)
{
    printf("\n\nIniciando D0 com var=%i e k=%i", var, k);
    int k_buff = k;
    int i,j;
    //----------------------------------------
    // Adiciona as regras da atual inicial ao vetor de saída
    //----------------------------------------
    for(i=0; i<MaxRegras; i++)  // Percorre vetor de regras
    {
        if(regras[i].proxVar[0][0]==-1) // Se a regra não existe, está no fim do vetor
            break;
        if(regras[i].variavel == var)    // Se for regra da variável atual
        {
            printf("\n\nRegra encontrada!");
            // Verifica se a regra já está no vetor
            int estaNoVetor = 0;
            for(j=0; j<MaxRegras; j++)  // Percorre o vetor de regras
            {
                if(regras[i].ID==regras_out[j].ID)    // Se a regra já está no vetor de saída
                {
                    estaNoVetor = 1;
                    printf("\nRegra ja esta no vetor!");
                    printf("\nregras[i].id:%i\nregras_out[j].id: %i", regras[i].ID, regras_out[j].ID);
                }
            }
            if(!estaNoVetor)   // Se a regra não está no vetor, a adciona
            {
                regras_out[k] = regras[i];  // Adiciona a regra ao vetor de saída
                k++;
            }
        }
    }
    //----------------------------------------

    for(i=0; i<k; i++)  // Percorre regras_out
    {
        if(regras_out[i].marcador!=-1 && regras_out[i].proxVar[regras_out[i].marcador][1]==1 && k!=k_buff)   // Se a regra existe e o valor indicado pelo marcador é uma regra e foi adicionado algo ao vetor de saída
        {
            printf("\nMarcador: %i\nproxVar: %i, %i",regras_out[i].marcador, regras_out[i].proxVar[regras_out[i].marcador][0], regras_out[i].proxVar[regras_out[i].marcador][1]);
            gera_D0(regras_out[i].proxVar[regras_out[i].marcador][0], regras, regras_out, k); // Para cada regra que existe, busca a variável apontada pelo marcador
        }
        else
            break;
    }
    return k;
}


//main
int main(int argc, const char * argv[])
{
    char Terminais[MaxTerminais][Tamanho];
    char Variaveis[MaxVariaveis][Tamanho2];
    struct REGRA Regras[MaxRegras];
    struct REGRA D0[MaxRegras];
    int Inicial = 0;

    // Inicialização
    inicializa_matrizes(Terminais, Variaveis, Regras, D0);

    // Leitura do arquivo da gramática
    le_gramatica(Terminais, Variaveis, &Inicial, Regras);

    // Geração de D0
    D0[0]=Regras[Inicial];
    gera_D0(Inicial, Regras, D0, 1);

    imprime_regras(Terminais, Variaveis, Regras);
    imprime_terminais(Terminais);
    imprime_variaveis(Variaveis, Inicial);

    printf("\n-----------------------------");
    printf("\nD0");
    imprime_regras(Terminais, Variaveis, D0);


    printf("NVariaveis: %i\nNTerminais: %i\nNRegras: %i\n", NVariaveis, NTerminais, NRegras);

    return 0;
}
